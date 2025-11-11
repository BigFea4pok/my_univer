#include<iostream>

int main() {
    const int rows = 3;
    const int cols = 3;
    float array[rows][cols] {};

    std::cout << "Enter nine float numbers:" << '\n';
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            std::cin >> array[i][j];
        }
    }

    for(int i=0; i < rows; ++i){
        for(int j=0; j < cols; ++j){
            std::cout << array[i][j] << " ";
        }
    }
    std::cout << '\n';

    const int total_elements = rows * cols;
    float buffer[total_elements] {};
    
    for(int i = 0, k = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j, ++k){
            buffer[k] = array[i][j];
        }
    }

    /* end - это текущая правая граница неотсортированной части массива; после каждого продвижения (наибольший элемент в неотсортированной части движется вперед), 
       элемент на этой позиции окончательно отсортирован и далее не нуждается в обработке. После сортировки total_elements - 1, последний(наименьший) элемент сам 
       встаёт на на нужную(первую) позицию и не нуждается в обработке. */
    float tmp = 0.0f;
    for(int end = total_elements - 1; end > 0; --end){                                               
        for(int i = 0; i < end; ++i){   // В добавок, число end совпадает с необходым количеством (попарных) сравнений для продвижения отдельного элемента в конец неотсорт. части.  
            if(buffer[i] > buffer[i+1]){
                tmp = buffer[i];
                buffer[i] = buffer[i+1];
                buffer[i+1] = tmp;
            }
        }
    }

    for(int i = 0, k = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j, ++k){
            array[i][j] = buffer[k];
        }
    }

    for(int i=0; i < rows; ++i){
        for(int j=0; j < cols; ++j){
            std::cout << array[i][j] << " ";
        }
    }
    std::cout << '\n';

    return 0;
}
    // // Рабочий, возможно более производительный, но плохо читаемый вариант

    // // Внешний for перемещает большие элементы вперед. Т.е. обработка каждого элемента по возрастанию.
    // // Внутренние for-ы индексируют двойной массив

    // for(int move_var = 1; move_var < total_elements; ++move_var){

    //     for(int i = 0; i < rows; ++i){
    //         for(int j = 1; j < cols; ++j){
    //             if(array[i][j-1] > array[i][j]){
    //                 tmp = array[i][j-1];
    //                 array[i][j-1] = array[i][j];
    //                 array[i][j] = tmp;    
    //             }
    //         }

    //         // Обработка за пределы массива
    //         if(i < (rows - 1)){ 
    //             if(array[i][cols-1] > array[i+1][0]){
    //                 tmp = array[i][cols-1];
    //                 array[i][cols-1] = array[i+1][0];
    //                 array[i+1][0] = tmp;   
    //             }
    //         }
    //     }
    // }