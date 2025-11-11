#include <iostream>
using namespace std;

char* enter_str(int len){
    if(len <= 0){
        char *str = new char[1];
        str[0] = '\0';
        return str;
    }

    char *str = new char[len + 1];
    cout << "Enter your string: ";
    cin >> str;         // если строка меньше длины cin ставит \0 последним элементом
    str[len] = '\0';    // есть риск переполнения, но строка хотя бы всегда на \0 заканчивается
    cout << "Your string is - \"" << str <<"\"\n\n";

    return str;
}

int get_real_len(const char* str){
    int n = 0;
    while(str[n] != '\0') ++n;
    return n;
}

char* concatenate(const char *str1, int len1, const char *str2, int len2){
    
    char *conc_str = new char[len1 + len2 + 1];
    for(int i = 0; i < (len1); ++i){
        conc_str[i] = str1[i];
    }
    for(int i = len1, j = 0; i < (len1 + len2); ++i, ++j){
        conc_str[i] = str2[j];
    }
    conc_str[len1 + len2] = '\0';

    return conc_str;
}

int main() {
    cout << "Enter length of string №1: ";
    int len1; cin >> len1;
    char *str1 = enter_str(len1);

    cout << "Enter length of string №2: ";
    int len2; cin >> len2;
    char *str2 = enter_str(len2);

    // На случай, если строка оказалась меньше заданной длины
    len1 = get_real_len(str1);
    len2 = get_real_len(str2);

    char *conc = concatenate(str1, len1, str2, len2);
    cout << "Concatenated - \"" << conc << "\"\n";

    delete[] str1;
    delete[] str2;
    delete[] conc;

    return 0;
}