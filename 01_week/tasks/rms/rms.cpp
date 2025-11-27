#include <cstddef>
#include <stdexcept>


double CalculateRMS(double values[], size_t size) {
    double sum = 0.0;
    
    if(size == 0) return 0.0;
    
    for(size_t i = 0; i < size; i++){
        sum += values[i]*values[i];
    }
    
    return std::sqrt(sum / size);
}
