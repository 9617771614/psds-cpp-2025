#include <stdexcept>

const int* FindLastElement(const int* begin, const int* end, bool (*predicate)(int))
{   
    if(begin == nullptr)    return end; // Проверка корректности адреса начала массива. 
    if(end == nullptr)      return end; // Проверка корректности адреса конца массива. 
    if(begin >= end)        return end; // Проверка корректности, адрес начала массива должен быть меньше чем адрес конца массива. 
    
 //   const int* result = end;
    const int* ptr = end;     // Инициализируем адрес на проверяемый элемент массива. 
    ptr--;
    
    // Т.к. задача найти последний элемент массива, который удовлетворяя условию, то можно проверять от последнего элемента к первому. Соответственно, как только найден элемент удовлетворяющий условию, выходим, иначе возвращается указатель на последний элемент. 
    while(ptr >= begin){
   //     cout<< "\r\n value = "<< *ptr << " addres ptr = "<< ptr;
        if(predicate(*ptr)) return ptr;
        
        ptr --;
    }
    
    return end;
}
