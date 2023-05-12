extern "C" {
    int sum_c(int a, int b) {
        return a + b;
    }
} 

int sum_cpp(int a, int b) {
    return a + b;
}

float sum_cpp_f(float a, float b) {
    return a + b;
}

class TSummer {
public:
    TSummer(int a);
    int SumA(int b);
    int SumB(int b) { return a + b; } // Обратите внимание, этой функции нет в символах [1]
    template <typename T>
    int SumC(T b) { return a + b; } // И уж тем более этой [1]
public:
    int a;
};

TSummer::TSummer(int a_arg): a(a_arg) {}
int TSummer::SumA(int b) { return a + b; } 