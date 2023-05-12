#include <iostream>
#include <string>

std::string path_to_lib(const std::string& name) {
    std::string ans = getenv("HOME");
    ans.push_back('/');
    for (size_t i = 0; i < name.size(); ++i) {
        if (name[i] == ':' && i + 1 < name.size() && name[i + 1] == ':') {
            ans.push_back('/');
            ++i;
        }
        else {
            ans.push_back(name[i]);
        }
    }
    return std::move(ans);
}

template <class T>
class Class {};

class mher {
public:
    mher() {}    
};
int aa() {
    mher p;
    return 1;
}
int main() {
    std::string aaa("some::package::ClassInPackage");
    //std::cout << path_to_lib(aaa) << '\n';
    std::string x = "abc" + std::to_string(4) + "aaa";
    std:: cout << x << '\n';
}