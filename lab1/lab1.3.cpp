#include <iostream>

int main(){

    const int rows = 5;
    const int cols = 5;
    short arr[rows][cols] {};

    std::cout << "Enter 25 short numbers:" << '\n';
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            std::cin >> arr[i][j];
        }
    }

    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            std::cout << arr[i][j] << '\t';
        }
        std::cout << '\n';
    }

    // Сумма
    int sum = 0;
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            if(arr[i][j] < 10) sum += arr[i][j];
        }
    }
    std::cout << '\n' << "The sum is = " << sum << '\n';
    
    // Транспонирование. Адресация по верхней (верхне-правой) части матрицы от диагонали.
    short tmp = 0;
    for(int i = 0; i < rows-1; ++i){    // адресация по строкам происходит от 0 до 3
        for(int j = i+1; j < cols; ++j){   // адресация по столбцам происходит от 1(минимум) до 4
            tmp = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = tmp;
        }
    }

    std::cout << '\n';
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            std::cout << arr[i][j] << '\t';
        }
        std::cout << '\n';
    }

    return 0;
}