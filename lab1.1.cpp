#include <iostream>
#include <cstdlib>

int main() {

    // int array[5][5] {};
    // for(int i=0; i<5; ++i){
    //     for(int j=0; j<5; ++j){
    //         std::cin >> array[i][j];
    //     }
    // }

    // int min = array[0][0];
    // for(int i=0; i<5; ++i){
    //     for(int j=0; j<5; ++j){
    //         if(min > array[i][j]) min = array[i][j];
    //     }
    // }

    // for(int x : array)
    //     std::cout << x << ' ';

    // std::cout << '\n' << "The min is " << min << '\n';

    srand(123123);
    int arr[5][5] {};

    for(int i = 0, j = 0; i < 5; ++j){
        // if(j == 5) j = 0; 
        std::cout << "Element " << i << ' ' << j << ' ' << arr[i][j] << ' ';
    }

    for(int i = 0, j = 0; i < 2; ++j){
        if(j == 2){
            j = 0; 
            ++i;
        }
        std::cin >> arr[i][j];
        // arr[i][j] = rand();
    }

    for(int i = 0, j = 0; i < 2; ++j){
        if(j == 2){
            j = 0; 
            ++i;
        }
        std::cout << arr[i][j] << ' ';
    }

    return 0;
}