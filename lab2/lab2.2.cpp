#include <iostream>
using namespace std;

void cyclic_shift(int *p_arr, int length, int shift, bool shift_direction){
    
    int *tmp_arr = new int[length] {};

    // нормализация сдвига
    shift %= length;
    if (shift < 0) shift += length;

    if(shift_direction){
        for(int i = 0; i < length; ++i){
            tmp_arr[(i + shift) % length] = p_arr[i];
        }
        cout << "\nThe shift to the right has been completed.\n";
    } else {
        for (int i = 0; i < length; ++i){
            tmp_arr[(i - shift + length) % length] = p_arr[i];
        }
        cout << "\nThe shift to the left has been completed.\n";   
    }

    for(int i = 0; i < length; ++i){
        p_arr[i] = tmp_arr[i];
    }

    delete[] tmp_arr;
}

void fill_arr(int *p_arr, int length){
    for(int i = 0; i < length; ++i){
        cout << "Add the element with index " << i << " to the array: ";
        cin >> p_arr[i];
    }
}

void print_arr(int *p_arr, int length){
    cout << "\nNow, the array looks like this: \n";
    for(int i = 0; i < length; ++i){
        cout << p_arr[i] << ' ';
        if((i % 10) == 9) cout << '\n';
    }
}

int main(){
    
    int length = 0;
    cout << "Length of array = ";
    cin >> length;

    if (length <= 0) {
        cout << "The array doesn't have elements";
        return 0;
    }

    int *p_arr = new int[length] {};
    fill_arr(p_arr, length);
    print_arr(p_arr, length);

    int n = 0;
    cout << "\nEnter the shift of array: ";
    cin >> n;
    cyclic_shift(p_arr, length, n, true);
    print_arr(p_arr, length);
    cyclic_shift(p_arr, length, n, false);
    print_arr(p_arr, length);
    cyclic_shift(p_arr, length, n, false);
    print_arr(p_arr, length);

    delete[] p_arr;

    return 0;
}