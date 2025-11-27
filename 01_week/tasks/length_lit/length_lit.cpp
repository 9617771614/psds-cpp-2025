constexpr double operator"" _ft_to_m(long double x) {
    return x / 100 * 12 * 2.54; // преобразование фт в метры 
}

constexpr double operator"" _ft_to_cm(long double x) {
    return x * 2.54 * 12; // преобразование фт в см 
}

constexpr double operator"" _ft_to_in(long double x) {
    return x * 12; // преобразование фт в дюймы 
}


//Дюймы
constexpr double operator"" _in_to_m(long double x) {
    return x / 100 * 2.54; //  
}

constexpr double operator"" _in_to_cm(long double x) {
    return x * 2.54; // 
}

constexpr double operator"" _in_to_ft(long double x) {
    return x / 12; // 
}


//Метры
constexpr double operator"" _m_to_ft(long double x) {
    return x / 100 * 2.54 * 12; //  
}

constexpr double operator"" _m_to_cm(long double x) {
    return x * 100; // 
}

constexpr double operator"" _m_to_in(long double x) {
    return x / 100 * 2.54; // 
}


//см
constexpr double operator"" _cm_to_ft(long double x) {
    return x / 12 / 2.54; //  
}

constexpr double operator"" _cm_to_m(long double x) {
    return x / 100; // 
}

constexpr double operator"" _cm_to_in(long double x) {
    return x * 2.54; // 
}


