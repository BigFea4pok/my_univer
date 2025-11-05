#include <iostream>
#include <cmath> 

double sin_taylor(double x, int N) {
    const double PI = acos(-1.0);// создаем константу пи
    x = fmod(x, 2 * PI); // остаток от деления x на 2pi
    if (x > PI) x -= 2 * PI; 
    if (x < PI)  x += 2 * PI;

    double sign = x;  // для того чтоб менять знак 
    double sum = sign;
    for (int i = 1; i < N; i++) {
        sign = -sign * (x * x) / ((2*i) * (2*i + 1));
        sum += sign;
    }
    return sum;
}

int main() {
    double x;
    int N;

    // x (в радианах) и N (число членов ряда)
    std::cout << "Radians: ";
    std::cin >> x;
    std::cout << "Number of members in the series: ";
    std::cin >> N;

    double my_sin = sin_taylor(x, N);
    double std_sin  = sin(x);

    std::cout << "\nsin_taylor = " << my_sin << "\n";
    std::cout << "std::sin = " << std_sin << "\n";
    std::cout << "Difference between func = " << fabs(my_sin - std_sin) << "\n";

    return 0;
}


