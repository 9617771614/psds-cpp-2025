#include <stdexcept>


void SwapPtr(int* a, int* b) {
    int *c;
    c = a;
    a = b;
    b = c;
}
