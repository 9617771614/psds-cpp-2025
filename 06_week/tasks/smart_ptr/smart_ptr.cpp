
/*
Умные указатели

Необходимо реализовать классы SharedPtr и WeakPtr, которые представляют собой аналоги std::shared_ptr и std::weak_ptr. То есть SharedPtr реализует семантику разделяемого владения, а WeakPtr представляет наблюдателя. В качестве объекта владения выступает строка std::string.

Класс SharedPtr предоставляет следующий функционал:

    Все необходимые конструкторы умного указателя с уникальным владением
    Операторы, реализующие поведение указателей
    Метод Get - получить сырой указатель
    Метод Reset - удаляет старый объект и принимает владение новым
    Метод Swap - обменивается владеющими указателями с другим SharedPtr
    Метод UseCount - возвращает количество владельцев
    Оператор bool() - приводит указатель к типу bool

Класс WeakPtr предоставляет следующий функционал:

    Все необходимые конструкторы умного указателя с уникальным владением
    Операторы, реализующие поведение указателей
    Метод Reset - убирает ссылку на владеющий объект
    Метод Swap - обменивается владеющими указателями с другим WeakPtr
    Метод UseCount - возвращает количество владельцев
    Метод Expired - проверяет, истекло ли время жизни исходного объекта
    Метод Lock - создает владеющий указатель SharedPtr на объект, если он ещё жив

Необходимо реализовать:

    Функию MakeShared - принимает строку и возвращает умный указатель SharedPtr. Функция должна поддерживать как копирование, так и перемещение принимаемого объекта.
    Функцию Swap - для обмена умными указателями SharedPtr, и указателями WeakPtr

Примечание

    Запрещено использовать умные указатели STL в реализации
    Одна из задач, где может пригодиться ключевое слово friend, но желательно им не злоупотреблять
    Счетчики допустимо использовать обычные, не атомарные
    Метод UseCount класса WeakPtr возвращает именно владельцев, поскольку именно владение определяет время жизни объекта


*/


#include <string>

// Forward declarations
class SharedPtr;
class WeakPtr;

class SharedPtr {
private:
    std::string* ptr_;      // Указатель
    size_t* sharedPtrCount_;  // Счетчик сильных ссылок
    size_t* weakPtrCount_;    // Счетчик слабых ссылок



public:
    // Все необходимые конструкторы умного указателя с уникальным владением
    SharedPtr() : ptr_(nullptr), sharedPtrCount_(nullptr), weakPtrCount_(nullptr) {}
    explicit SharedPtr(std::string* p) : ptr_(p) {
      if (p != nullptr) {
        sharedPtrCount_ = new size_t(1);
        weakPtrCount_ = new size_t(0);
      } else {
        sharedPtrCount_ = nullptr;
        weakPtrCount_ = nullptr;
      }
    }
    
    SharedPtr(const SharedPtr& data) : ptr_(data.ptr_), sharedPtrCount_(data.sharedPtrCount_), weakPtrCount_(data.weakPtrCount_) {
      if (sharedPtrCount_ != nullptr)  (*sharedPtrCount_)++;
    }

    SharedPtr(SharedPtr&& data) noexcept : ptr_(data.ptr_), sharedPtrCount_(data.sharedPtrCount_), weakPtrCount_(data.weakPtrCount_) {
        data.ptr_ = nullptr;
        data.sharedPtrCount_ = nullptr;
        data.weakPtrCount_ = nullptr;
    }
    
    // Destructor
    ~SharedPtr() {
        Reset();
    }
    
// Операторы, реализующие поведение указателей
    // Присвоение (перемещение)
    SharedPtr& operator=(const SharedPtr& data) {
        if (this != &data) {
            Reset();  // очистка
            // присвоение новых значений 
            ptr_ = data.ptr_;
            
            sharedPtrCount_ = data.sharedPtrCount_;
            weakPtrCount_ = data.weakPtrCount_;
            if (sharedPtrCount_) {
                (*sharedPtrCount_)++;
            }
        }
        return *this;
    }
    

    SharedPtr& operator=(SharedPtr&& data) noexcept {
        if (this != &data) {
            Reset();  // очистка    Метод UseCount - возвращает количество владельцев

            ptr_ = data.ptr_;
            // присвоение новых значений и обнуление data
            sharedPtrCount_ = data.sharedPtrCount_;
            weakPtrCount_ = data.weakPtrCount_;
            data.ptr_ = nullptr;
            data.sharedPtrCount_ = nullptr;
            data.weakPtrCount_ = nullptr;
        }
        return *this;
    }
    
    // укозатели
    std::string& operator*() const { return *ptr_; }
    std::string* operator->() const { return ptr_; }
    
    
// Методы
    // Метод Get - получить сырой указатель
    std::string* Get() const { return ptr_; }
    
    // Метод Reset - удаляет объект
    void Reset() { 
      if (sharedPtrCount_ != nullptr) { // Есть, что очищать?
        (*sharedPtrCount_)--;

        if (*sharedPtrCount_ == 0) {
          delete ptr_;
          ptr_ = nullptr;

          if (*weakPtrCount_ == 0) {
            delete sharedPtrCount_;
            delete weakPtrCount_;
          }
        }

        sharedPtrCount_ = nullptr;
        weakPtrCount_ = nullptr;
      }
      ptr_ = nullptr;
    
    
    }
    
    // Метод Reset - удаляет старый объект и принимает владение новым
    void Reset(std::string* p) {
      Reset();  // сброс

      // Присвоение
      if (p) {  // а есть что присвоить?
        ptr_ = p;
        sharedPtrCount_ = new size_t(1);
        weakPtrCount_ = new size_t(0);
      }
    }
    
    // Метод Swap - обменивается владеющими указателями с другим WeakPtr
    void Swap(SharedPtr& data) {
      std::string* tempPtr;
      size_t* temp;

      // Обмен указателями
      tempPtr = data.ptr_;
      data.ptr_ = ptr_;
      ptr_ = tempPtr;


      // Обмен счетчиком слабых ссылок
      temp = data.sharedPtrCount_;
      data.sharedPtrCount_ = sharedPtrCount_;
      sharedPtrCount_ = temp;
      
      // Обмен счетчиком сильных ссылок
      temp = data.weakPtrCount_;
      data.weakPtrCount_ = weakPtrCount_;
      weakPtrCount_ = temp;
    }
    
    // Метод UseCount - возвращает количество владельцев
    size_t UseCount() const {
      if(sharedPtrCount_ != nullptr)  return *sharedPtrCount_;
      return 0;
    }
    
    // Оператор bool() - приводит указатель к типу bool
    operator bool() const { 
      if(ptr_ != nullptr) return true;
      return false;
    }
    
    // Friend classes
    friend class WeakPtr;
    friend void Swap(SharedPtr& lhs, SharedPtr& rhs);
};

class WeakPtr {
private:
    std::string* ptr_;      // Указатель
    size_t* sharedPtrCount_;  // Счетчик сильных ссылок
    size_t* weakPtrCount_;    // Счетчик слабых ссылок

public:
    // Все необходимые конструкторы умного указателя с уникальным владением
    // конструктор по умолчанию
    WeakPtr() : ptr_(nullptr), sharedPtrCount_(nullptr), weakPtrCount_(nullptr) {}
    
    // конструктор от SharedPtr 
    WeakPtr(const SharedPtr& sp) : ptr_(sp.ptr_), sharedPtrCount_(sp.sharedPtrCount_), weakPtrCount_(sp.weakPtrCount_) {
        if (weakPtrCount_) {
            (*weakPtrCount_)++;
        }
    }
    
    // Конструктор копирования
    WeakPtr(const WeakPtr& data) : ptr_(data.ptr_), sharedPtrCount_(data.sharedPtrCount_), weakPtrCount_(data.weakPtrCount_) {
        if (weakPtrCount_) {
            (*weakPtrCount_)++;
        }
    }
    
    // Конструктор перемещения 
    WeakPtr(WeakPtr&& data) noexcept : ptr_(data.ptr_), sharedPtrCount_(data.sharedPtrCount_), weakPtrCount_(data.weakPtrCount_) {
      // Очищаем данные из которых переместили
        data.ptr_ = nullptr;
        data.sharedPtrCount_ = nullptr;
        data.weakPtrCount_ = nullptr;
    }
    
    // Диструктор 
    ~WeakPtr() {
        Reset();
    }
    
  
    WeakPtr& operator=(const WeakPtr& data) {
        if (this != &data) {  // текущий равен ? 
        // нет -присваивание.
            Reset();  // очистка
            ptr_ = data.ptr_;
            sharedPtrCount_ = data.sharedPtrCount_;
            weakPtrCount_ = data.weakPtrCount_;
            if (weakPtrCount_)  (*weakPtrCount_)++;
        }
        return *this;
    }
    

    WeakPtr& operator=(WeakPtr&& data) noexcept {
    // аналогично как выше, но + очистка data
        if (this != &data) {
            Reset();
            ptr_ = data.ptr_;
            sharedPtrCount_ = data.sharedPtrCount_;
            weakPtrCount_ = data.weakPtrCount_;
            // очистка data
            data.ptr_ = nullptr;
            data.sharedPtrCount_ = nullptr;
            data.weakPtrCount_ = nullptr;
        }
        return *this;
    }
    
    
    WeakPtr& operator=(const SharedPtr& sp) {
    // аналогично как выше
        Reset();
        ptr_ = sp.ptr_;
        sharedPtrCount_ = sp.sharedPtrCount_;
        weakPtrCount_ = sp.weakPtrCount_;
        if (weakPtrCount_) {
            (*weakPtrCount_)++;
        }
        return *this;
    }
    
    
// Методы 
    // Метод Reset - убирает ссылку на владеющий объект
    void Reset() {
      if (weakPtrCount_ != nullptr) {
        (*weakPtrCount_ )--;
        
        if ((*sharedPtrCount_ == 0) && (*weakPtrCount_ == 0)) {
          delete sharedPtrCount_;
          delete weakPtrCount_;
        }
        
        // очистка this
        weakPtrCount_ = nullptr;
        sharedPtrCount_ = nullptr;
        ptr_ = nullptr;
      }
    }
    
    // Метод Swap - обменивается владеющими указателями с другим WeakPtr
    void Swap(WeakPtr& data) {
      std::string* tempPtr;
      size_t* temp;

      // Обмен указателями
      tempPtr = data.ptr_;
      data.ptr_ = ptr_;
      ptr_ = tempPtr;


      // Обмен счетчиком слабых ссылок
      temp = data.sharedPtrCount_;
      data.sharedPtrCount_ = sharedPtrCount_;
      sharedPtrCount_ = temp;
      
      // Обмен счетчиком сильных ссылок
      temp = data.weakPtrCount_;
      data.weakPtrCount_ = weakPtrCount_;
      weakPtrCount_ = temp;
    }
    
    
    // Метод UseCount - возвращает количество владельцев
    size_t UseCount() const {
      if(sharedPtrCount_ != nullptr)  return *sharedPtrCount_;
      return 0;
    }
    
    // Метод Expired - проверяет, истекло ли время жизни исходного объекта
    bool Expired() const {
      if(sharedPtrCount_ == nullptr)  return true;  // указатель на nullptr значит истекло время жизни
      if(*sharedPtrCount_ != 0)  return false;      // счетчик не 0 значит не истекло время жизни
      return true;                                  // счетчик = 0 значит истекло время жизни
    }
    
    // Метод Lock - создает владеющий указатель SharedPtr на объект, если он ещё жив
    SharedPtr Lock() const {
      if (!Expired()) {
        SharedPtr sp;
        sp.ptr_ = ptr_;
        sp.sharedPtrCount_ = sharedPtrCount_;
        sp.weakPtrCount_ = weakPtrCount_;
        if (sp.sharedPtrCount_ != nullptr) {
            (*sp.sharedPtrCount_)++;
        }
        return sp;
      }
      return SharedPtr();
    }
    
    // Friend functions
    friend void Swap(WeakPtr& lhs, WeakPtr& rhs);
};




// Функия MakeShared - принимает строку и возвращает умный указатель SharedPtr. Функция должна поддерживать как копирование, так и перемещение принимаемого объекта.
SharedPtr MakeShared(const std::string& str) {
    return SharedPtr(new std::string(str));
}

SharedPtr MakeShared(std::string&& str) {
    return SharedPtr(new std::string(std::move(str)));
}

// Функция Swap - для обмена умными указателями SharedPtr, и указателями WeakPtr
void Swap(SharedPtr& dataA, SharedPtr& dataB) {
    dataA.Swap(dataB);
}

void Swap(WeakPtr& dataA, WeakPtr& dataB) {
    dataA.Swap(dataB);
}
