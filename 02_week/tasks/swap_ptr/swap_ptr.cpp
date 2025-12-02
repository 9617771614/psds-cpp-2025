#include <stdexcept>


template<typename T>
void SwapPointers(T*& a, T*& b) noexcept {
    T* temp = a;
    a = b;
    b = temp;
}
