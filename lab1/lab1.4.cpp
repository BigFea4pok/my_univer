#include <iostream>
#include <cstdlib>  // для srand и rand

bool is_unique(int num, int arr[], int filled){
    for(int i = 0; i < filled; ++i){
        if(arr[i] == num){
            return false;
        }
    }
    return true;
}

int main() {
    
    // Заполнить одномерный массив размером 200 элементов случайными и неповторяющимися числами в диапазоне 1 – 200.
        // Пример: 4, 34, 66, 123, 73, 1, 200, 195 ...
    const int LEN = 200;
    int arr[LEN];

    srand(12345);
    int filled = 0;
    int tmp = 0;
    
    while(filled < LEN){
        tmp = (rand() % LEN) + 1;
        if(is_unique(tmp, arr, filled)){
            arr[filled] = tmp;
            ++filled;
        }
    }

    std::cout << "Before processing:\n";
    for (int k = 0; k < LEN; ++k) {
        std::cout << arr[k] << '\t';
        if(((k+1) % 10) == 0) std::cout << '\n';
        if(((k+1) % 40) == 0) std::cout << '\n';
    }

    // Перемешать данные в массиве таким образом, чтобы модуль разности любых соседних чисел был не меньше чем 5.
        // Пример: 1, 101, 2, 102, 3, 103, ... 100, 200
        // Да, игнорируем изначальный массив
    filled = 0;
    int search_one = 1, search_two = 101;
    while(filled < LEN){

        for(int i = 0; i < LEN; ++i){
            if(arr[i] == search_one){
                tmp = arr[filled];
                arr[filled] = arr[i];
                arr[i] = tmp;
                ++filled; ++search_one;
                break;
            }
        }

        for(int i = 0; i < LEN; ++i){
            if(arr[i] == search_two){
                tmp = arr[filled];
                arr[filled] = arr[i];
                arr[i] = tmp;
                ++filled; ++search_two;
                break;
            }
        }

    }

    std::cout << "After processing:\n";
    for (int k = 0; k < LEN; ++k) {
        std::cout << arr[k] << '\t';
        if(((k+1) % 10) == 0) std::cout << '\n';
        if(((k+1) % 40) == 0) std::cout << '\n';
    }

    return 0;
}