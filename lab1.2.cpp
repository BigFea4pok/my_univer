#include<iostream>

int main() {

    const int lenght_up = 3;
    const int lenght_down = 3;
    float array[lenght_up][lenght_down] {};

    std::cout << "Enter nine float numbers:" << '\n';
    for(int i=0; i<lenght_up; ++i){
        for(int j=0; j<lenght_down; ++j){
            std::cin >> array[i][j];
        }
    }
    std::cout << '\n';

    int total_elements = lenght_up*lenght_down;
    float tmp = 0.0f;
    for(int move_var=1; move_var<total_elements; ++move_var){
        for(int i=0; i<lenght_up; ++i){
            for(int j=1; j<lenght_down; ++j){
                if(array[i][j-1] > array[i][j]){
                    tmp = array[i][j-1];
                    array[i][j-1] = array[i][j];
                    array[i][j] = tmp;    
                }
            }

            if(i < lenght_up-1){ 
                if(array[i][lenght_down-1] > array[i+1][0]){
                    tmp = array[i][lenght_down-1];
                    array[i][lenght_down-1] = array[i+1][0];
                    array[i+1][0] = tmp;   
                }
            }
        }
    }


    for(int i=0; i<lenght_up; ++i){
        for(int j=0; j<lenght_down; ++j){
            std::cout << array[i][j] << " ";
        }
    }
    std::cout << '\n';



}