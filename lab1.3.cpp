#include <iostream>

int main(){

    const int row = 5;
    const int column = 5;
    short array[row][column] {};

    for(int i = 0; i<row; ++i){
        for(int j = 0; j<column; ++j){
            std::cin >> array[i][j];
        }
    }

    for(int i = 0; i<row; ++i){
        for(int j = 0; j<column; ++j){
            std::cout << array[i][j] << '\t';
        }
        std::cout << '\n';
    }

    // Сумма
    short sum = 0;
    for(int i = 0; i<row; ++i){
        for(int j = 0; j<column; ++j){
            if(array[i][j] < 10){
                sum += array[i][j];
            }
        }
    }
    std::cout << '\n' << "The sum is = " << sum << '\n';
    
    // Транспонирование. Адресация по верхней части матрицы от диагонали.
    short tmp = 0;
    for(int i = 0; i<row-1; ++i){    // адресация по строкам происходит от 0 до 3
        for(int j = i+1; j<column; ++j){   // адресация по столбцам происходит от 1(минимум) до 4
            tmp = array[i][j];
            array[i][j] = array[j][i];
            array[j][i] = tmp;
        }
    }

    std::cout << '\n';
    for(int i = 0; i<row; ++i){
        for(int j = 0; j<column; ++j){
            std::cout << array[i][j] << '\t';
        }
        std::cout << '\n';
    }

    return 0;
}