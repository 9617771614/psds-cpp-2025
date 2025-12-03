#include <stdexcept>


template<typename T>
void SwapPtr(T*& a, T*& b) noexcept {
    T* temp = a;
    a = b;
    b = temp;
}
