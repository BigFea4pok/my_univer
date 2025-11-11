#include <iostream>

int main() {
    int array[5][5] {};

    for(int i=0; i<5; ++i){
        for(int j=0; j<5; ++j){
            std::cin >> array[i][j];
        }
    }

    int min = array[0][0];
    for(int i=0; i<5; ++i){
        for(int j=0; j<5; ++j){
            if(min > array[i][j]) min = array[i][j];
        }
    }

    for(int i=0; i<5; ++i){
        for(int j=0; j<5; ++j){
            std::cout << array[i][j] << ' ';
        
        }
        std::cout << '\n';
    }

    std::cout << "The min is " << min << '\n';

    return 0;
}