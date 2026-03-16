#include <cstddef>
void* memmove(void* dest, void* src, std::size_t n) {
    // 1. nullptr特殊情况
    if(dest == nullptr || src == nullptr) return nullptr;

    // 2. 强转为字符类型
    char* d = (char*)dest;
    const char* s = (const char*)src;

    // 3. [ds]/[d][s]的形式 / [s][d]的形式
    if(d < s || d >= s + n) {
        while(n--) *(d++) = *(s++);
        return dest;
    }

    // 4. [sd]的形式，从前往后拷贝，可能会覆盖掉s的后半段
    d += n -1;
    s += n - 1;
    while(n--) {
        *d-- = *s--;
    }
    return dest;
}
