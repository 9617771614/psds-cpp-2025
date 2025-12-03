#include <stdexcept>

using FuncTypeTest = double (*)(double, double);

double ApplyOperations(double a, double b, FuncTypeTest operations[], size_t size) {
    if (size == 0) {    //  Если нулевой размер массива функций то -ошибка возвращаем 0
        return 0.0;
    }
    // выход за пределы массива функций не контролируем. 
    
    double total_sum = 0.0;    // результат всех операций.
    
    for (size_t i = 0; i < size; ++i) {    // если более одной операции, проходим все.
        if(operations[i] == nullptr)  return 0.0;  //  Если указатель на nullptr -ошибка возвращаем 0
        total_sum += operations[i](a, b);    // учет результата операции
    }
    
    return total_sum;    // возвращаем результат    
}
