constexpr double operator"" _ft_to_m(long double x) {
    return x * 0.3048; // преобразование фт в метры 
}

constexpr double operator"" _ft_to_cm(long double x) {
    return x * 30.48; // преобразование фт в см 
}

constexpr double operator"" _ft_to_in(long double x) {
    return x * 12; // преобразование фт в дюймы 
}


//Дюймы
constexpr double operator"" _in_to_m(long double x) {
    return x * 0.0254; //  
}

constexpr double operator"" _in_to_cm(long double x) {
    return x * 2.54; // 
}

constexpr double operator"" _in_to_ft(long double x) {
    return x / 12; // 
}


//Дюймы
constexpr double operator"" _in_to_m(long double x) {
    return x * 0.0254; //  
}

constexpr double operator"" _in_to_cm(long double x) {
    return x * 2.54; // 
}

constexpr double operator"" _in_to_ft(long double x) {
    return x / 12; // 
}
