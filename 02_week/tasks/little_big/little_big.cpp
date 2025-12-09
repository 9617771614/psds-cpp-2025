#include <stdexcept>



void PrintingFunc(unsigned char* ptr, size_t size,  bool orientation)
{
    char tempL, tempR;
//    size_t i = 0; 
    char buf[size * 2];

    for(size_t i = 0; i < size; i++)
    {
//        std::cout << "\r\n i = "<< i<< " *ptr = " <<*ptr;
        tempR = *ptr & 0x0F;
        tempL = (*ptr >> 4) & 0x0F;
        ptr++;
        
        
        if(tempR < 10)   buf[i*2] = tempR + 48;
        else            buf[i*2] = tempR - 10 + 'A';
        if(tempL < 10)   buf[i*2+1] = tempL + 48;
        else            buf[i*2+1] = tempL - 10 + 'A';
        
    }
 //   std::cout << "\r\n buf = " << buf;
    
    
    std::cout << "0x";
    
    for(size_t i = 0; i < size * 2; i+=2)
    {
        if(!orientation)
        {
            std::cout << buf[i];
            std::cout << buf[i+1]; 
        }
        else
        {
            std::cout << buf[size*2 - 1 - i];
            std::cout << buf[size*2 - 2 - i]; 
        }

    }
    
    
    std::cout << "\n";
    
}


void PrintMemory(int num, bool orientation) {
    
    unsigned char* ptr = reinterpret_cast<unsigned char*>(&num);
    PrintingFunc(ptr, sizeof(num), orientation);


    // на лекции узнал про "reinterpret_cast"
    // size_t count = 0;
    // const size_t sizeInt = sizeof(int );
    
//    size_t temp = 0;

    
    // cout<< "\r\n sizeInt = "<< sizeInt << " num = "<<num;
    // cout<< "\r\n str = ";
    // for(size_t i = 0; i < (sizeInt * 2); i++)
    // {
    //     temp = num;
    //     temp = temp & (0x0F << (i*4));
    //     temp = temp >> (i*4);

        
    //     if(temp > 0x0F) buf[i] = '0';    // защита
    //     else if(temp < 10)   buf[i] = static_cast<char>(temp + 48);
    //     else            buf[i] = static_cast<char>(temp - 10) + 'A';
        
    // }
    

 //   std::cout << "0x";
    
    // for(size_t i = 0; i < sizeInt * 2; i+=2)
    // {
    //     if(!orientation)
    //     {
    //         std::cout << buf[i];
    //         std::cout << buf[i+1]; 
    //     }
    //     else
    //     {
    //         std::cout << buf[8 - 1 - i];
    //         std::cout << buf[8 - 2 - i]; 
    //     }

    // }
    

//    std::cout << "\n";
}

void PrintMemory(double num, bool orientation) {
    unsigned char* ptr = reinterpret_cast<unsigned char*>(&num);
    PrintingFunc(ptr, sizeof(num), orientation);
}

void PrintMemory(int value)
{
    PrintMemory(value, false);
}

void PrintMemory(double value)
{
    PrintMemory(value, false);
}
