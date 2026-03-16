#include <cstddef>
void* memcpy(void* dest, const void* src, std::size_t n) {
    if(dest == nullptr || src == nullptr) return nullptr;
    char* d = (char*)dest;
    const char* s = (const char*)src;

    while(n--) {
        *d++ = *s++;
    }
    return dest;
}