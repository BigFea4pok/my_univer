#include <iostream>
#include <cstdlib>  // для srand и rand
using namespace std; 

// в чем отличие указателя от ссылки и их использование в параметрах?

void fill_arr(int *p_arr, int length, short mode){
    switch(mode){
        case 0: 
            for(int i = 0; i < length; ++i){
                cout << "Add the element with index " << i << " to the array: ";
                cin >> p_arr[i];
            }
            break;
        case 1:
            cout << "The array will be filled with random numbers\n";
            for(int i = 0; i < length; ++i){
                p_arr[i] = rand();
            }
            break;
        default: 
            cout << "\nIncorrect input. The values of the array will be incorrect." <<
                "\nPlease restart the program and enter 0 or 1.\n";
            break;
    }
}

int min_plus_max(int *p_arr, int length){
    int min = p_arr[0];
    int max = p_arr[0];

    for(int i = 1; i < length; ++i){
        if(min > p_arr[i]) min = p_arr[i];
        if(max < p_arr[i]) max = p_arr[i];
    }

    cout << min + max << " is sum of the min(" << min << ") and max(" << max << ") values in the array\n";
    return min + max;
}

void even_odd_sort(int *p_arr, int length){
    int *odd = new int[length] {};
    int *even = new int[length] {};
    int odd_counter = 0, even_counter = 0;

    for(int i = 0; i < length; ++i){
        if((p_arr[i] % 2) == 0){
            even[even_counter] = p_arr[i];
            ++even_counter;
        } else {
            odd[odd_counter] = p_arr[i];
            ++odd_counter;
        }
    }

    for(int i = 0; i < odd_counter; ++i){
        p_arr[i] = odd[i];
    }
    for(int i = odd_counter, j = 0; i < (odd_counter + even_counter); ++i, ++j){
        p_arr[i] = even[j];
    }

    delete[] odd;
    delete[] even;

    cout << "The array has been sorted\n";
}

void print_arr(int *p_arr, int length){
    cout << "\nNow, the array looks like this: \n";
    for(int i = 0; i < length; ++i){
        cout << p_arr[i] << ' ';
        if((i % 10) == 9) cout << '\n';
    }
    cout << '\n';
}

int main(){
    // Объявление динамического массива
    int length = 0;
    cout << "Length of array = ";
    cin >> length;

    if (length <= 0) {
        cout << "The array doesn't have elements";
        return 0;
    }

    int *p_arr = new int[length] {};

    // вспомнить про нулевые указатели

    // 1.a
    cout << "\n1.a\n";

    srand(2938746);
    short mode = 0;
    cout << "Please enter 0 or 1: ";
    cin >> mode;

    fill_arr(p_arr, length, mode);
    print_arr(p_arr, length);


    // 1.b
    cout << "\n1.b\n";
    
    min_plus_max(p_arr, length);

    // 1.3
    cout << "\n1.c\n";
    
    even_odd_sort(p_arr, length);
    print_arr(p_arr, length);

    // освобождаем динамическую память
    delete[] p_arr;

    return 0;
}