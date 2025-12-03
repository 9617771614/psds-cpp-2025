#include <stdexcept>


char* FindLongestSubsequence(const char* begin, const char* end, size_t& count){
    count = 0;
    if(begin == nullptr ) return nullptr ;  // Проверка корректности указателя на начало.
    if(end == nullptr ) return nullptr ;    // Проверка корректности указателя на конец.
    if(begin >= end) return nullptr;     // char имеет размер 1 байт, end должен быть больше чем begin минимум на 1
    // Проерки пройдены. работаем дальше.
    
    const char* ptr = begin;
    const char* resultPtr = begin ;
    const char* beginningSequence = ptr;
    size_t countSequence = 1;
    count = 1;
    while(ptr < end)    // пока адрес анализируемой переменной меньше адреса последней переменной.
    {
        if(*ptr == *(ptr+1)){               // Сравнение текущего символа с последующим, если совпали надо произвести учет.
            if(countSequence == 1){         // Если счётчик совпадений =0 (предыдущая пара различалась), запоминаем начало последовательности и счетчик делаем равным 2м т.к. совпали два числа.
                beginningSequence = ptr;
                countSequence = 2;
//                cout << "\r\n new ptr "<< beginningSequence; 
            }
            else   countSequence++;         // Не первое совпадение, просто увеличиваем счетчик совпадений. 
        }
        else    // Не совпало 
        {
            if(countSequence != 1)  // счетчик совпадений != 0, значит нализируем.
            {
                if(countSequence > count)   // счетчик совпадений больше предыдущего значения. Запоминаем новую последовательность
                {
                    resultPtr = beginningSequence;
                    count = countSequence;
                }
                // если счетчики совпали, сохраняем начала предыдущей совпавшей полсдеовательности.
            }
            
            countSequence = 1;  // "обнуляем" (записываем 1) счетчик совпадений.
        }
        
        ptr++;
    }
    
    
    
    return resultPtr;   // вывод результата.
}
