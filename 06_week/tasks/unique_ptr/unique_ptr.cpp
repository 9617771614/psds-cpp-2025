#include <string>


/*Умный указатель уникального владения

Необходимо реализовать класс UniquePtr, который реализует семантику уникального владения строкой std::string. Класс соответствует умному указателю std::unique_ptr.

Класс предоставляет следующий функционал:

    Все необходимые конструкторы умного указателя с уникальным владением
    Операторы, реализующие поведение указателей
    Метод Get - получить сырой указатель
    Метод Release - освобождает владение (возвращает указатель и становится nullptr)
    Метод Reset - удаляет старый объект и принимает владение новым
    Метод Swap - обменивается владеющими указателями с другим UniquePtr
    Оператор bool() - приводит указатель к типу bool

Необходимо реализовать:

    Функию MakeUnique - принимает строку и возвращает умный указатель UniquePtr. Функция должна поддерживать как копирование, так и перемещение принимаемого объекта
    Функцию Swap - для обмена умными указателями UniquePtr

Примечание

    Запрещено использовать умные указатели STL в реализации
*/



class UniquePtr{
private:
  std::string* ptr_;

public:
  // Все необходимые конструкторы умного указателя с уникальным владением
  UniquePtr(): ptr_(nullptr) {}
  UniquePtr(std::string* ptr) : ptr_(ptr){}
  UniquePtr(UniquePtr&& ptrA) noexcept : ptr_(ptrA.ptr_) { ptrA.ptr_ = nullptr;}
  
  
      // Оператор перемещения
  UniquePtr& operator=(UniquePtr&& ptrA) noexcept { 
        if (this != &ptrA) {
          delete ptr_;
          ptr_ = ptrA.ptr_;
          ptrA.ptr_ = nullptr;
      }
      return *this;
  }

    // Деструктор
    ~UniquePtr() { delete ptr_; }
  
  std::string& operator*() const { return *ptr_; }
  std::string* operator->() const { return ptr_; }
  
  // Получить сырой указатель
  std::string* Get() const { return ptr_; }
  
  
  // Метод Release - освобождает владение (возвращает указатель и становится nullptr)
  std::string* Release() { 
    std::string* temp;
    temp = ptr_;
    ptr_ = nullptr;
    return temp;
  }

  
  // Метод Reset - удаляет старый объект и принимает владение новым
  void Reset(std::string* ptr = nullptr) {
      delete ptr_;
      ptr_ = ptr;
  }
  
  
  /*
  // Метод Swap - обменивается владеющими указателями с другим UniquePtr
  void Swap(UniquePtr& ptrA) noexcept {
    std::string* temp = ptrA.ptr_;
    ptrA.ptr_ = this->ptr_;
    this->ptr_ = temp;
  }
  */
    // Обменяться указателями (без использования библиотечных функций)
    void Swap(UniquePtr& other) noexcept {
        std::string* temp = this->ptr_;
        this->ptr_ = other.ptr_;
        other.ptr_ = temp;
    }
  
  // Оператор bool() - приводит указатель к типу bool
  explicit operator bool() const { return ptr_ != nullptr;}
  
  
      // Запрет копирования
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

};


//Необходимо реализовать:

//    Функию MakeUnique - принимает строку и возвращает умный указатель UniquePtr. Функция должна поддерживать как копирование, так и перемещение принимаемого объекта

UniquePtr MakeUnique(const std::string& data);
UniquePtr MakeUnique(std::string&& data);

UniquePtr MakeUnique(const std::string& data) { return UniquePtr(new std::string(data)); }

UniquePtr MakeUnique(std::string&& data) { return UniquePtr(new std::string(std::move(data))); }


//    Функцию Swap - для обмена умными указателями UniquePtr
void Swap(UniquePtr& dataA, UniquePtr& dataB) noexcept;

void Swap(UniquePtr& dataA, UniquePtr& dataB) noexcept {dataA.Swap(dataB); }

