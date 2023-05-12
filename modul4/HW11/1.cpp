#include "interfaces.h"
#include <dlfcn.h>

std::string path_to_lib(const std::string& name)
{
    std::string ans = getenv("CLASSPATH");
    ans.push_back('/');
    for (size_t i = 0; i < name.size() - 1; ++i) {
        if (name[i] == ':' && name[i + 1] == ':') {
            ans.push_back('/');
            ++i;
        } else {
            ans.push_back(name[i]);
        }
    }
    ans.push_back(name.back());
    ans.append(".so");
    return ans;
}

std::string get_symbol(const std::string& name)
{
    std::string ans = "_ZN";
    size_t off = 0;
    if (name.rfind("std::") == 0) {
        off = 5;
        ans.append("St");
    }
    int sz = 0;
    for (size_t i = off; i < name.size() - 1; ++i) {
        if (name[i] == ':' && name[i + 1] == ':') {
            ans.append(std::to_string(sz));
            for (int j = sz; j > 0; --j) {
                ans.push_back(name[i - j]);
            }
            ++i;
            sz = 0;
        } else {
            ++sz;
        }
    }
    ans.append(std::to_string(sz + 1));
    for (int j = sz + 1; j > 0; --j) {
        ans.push_back(name[name.size() - j]);
    }
    ans.append("C1Ev");
    return ans;
}

struct ClassImpl {
    void* ptrToConstructor;
};

AbstractClass::AbstractClass() : pImpl(new ClassImpl())
{
}

AbstractClass::~AbstractClass()
{
    delete pImpl;
}

void* AbstractClass::newInstanceWithSize(size_t sizeofClass)
{
    char* storage = new char[sizeofClass];
    void (*constructor)(void*) =
        reinterpret_cast<void (*)(void*)>(pImpl->ptrToConstructor);
    constructor(storage);
    return storage;
}

struct ClassLoaderImpl {
    ClassLoaderError lastError;
};

ClassLoader::ClassLoader() : pImpl(new ClassLoaderImpl)
{
}

AbstractClass* ClassLoader::loadClass(const std::string& fullyQualifiedName)
{
    std::string path = std::move(path_to_lib(fullyQualifiedName));

    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        pImpl->lastError = ClassLoaderError::LibraryLoadError;
        return nullptr;
    }
    std::string symbol = std::move(get_symbol(fullyQualifiedName));
    void* constructorPtr = dlsym(handle, symbol.c_str());
    if (!constructorPtr) {
        pImpl->lastError = ClassLoaderError::NoClassInLibrary;
        return nullptr;
    }
    AbstractClass* ans = new AbstractClass;
    (ans->pImpl)->ptrToConstructor = constructorPtr;
    return ans;
}

ClassLoaderError ClassLoader::lastError() const
{
    return pImpl->lastError;
}

ClassLoader::~ClassLoader()
{
    delete pImpl;
}
