#include <stdio.h>

char* get_str(int len){
    if (len <= 0){
        char *str = new char[1];
        str[0] = '\0';
        return str;
    }

    char* str = new char[len + 1];

    // очистка от прошлого ввода
    int ch = getchar();
    if (ch != '\n' && ch != EOF){
        ungetc(ch, stdin);
    }

    if (fgets(str, len + 1, stdin) != NULL) {
        int i = 0;
        int truncated = 0;

        /* Идём по буферу, пока не встретим '\0' или '\n' */
        while (str[i] != '\0' && str[i] != '\n') {
            i++;
        }

        if (str[i] == '\n') {
            /* Заменяем финальный перевод строки на '\0' */
        str[i] = '\0';
        } else {
            /* Нет '\n' — возможно ввод был длиннее буфера.
               Очистим остаток в stdin до конца строки. */
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { /* пусто */ }
            truncated = 1;
        }

        printf("Результат: \"%s\"%s\n", str, truncated ? " (ввод был длиннее буфера, обрезано)" : "");
    }

    return str;
}

char* concatenate(const char *str1, int len1, const char *str2, int len2){
    
    char *conc_str = new char[len1 + len2 + 1];
    for (int i = 0; i < (len1); ++i){
        conc_str[i] = str1[i];
    }
    for (int i = len1, j = 0; i < (len1 + len2); ++i, ++j){
        conc_str[i] = str2[j];
    }
    conc_str[len1 + len2] = '\0';

    return conc_str;
}

int main() {
    printf("Введите длину строку №1: ");
    int len1; scanf("%d", &len1);
    char *str1 = get_str(len1);
    printf("%s", str1);

    printf("Введите длину строку №2: ");
    int len2; scanf("%d", &len2);
    char *str2 = get_str(len2);
    printf("%s", str2);

    // На случай, если строка оказалась меньше заданной длины
    // len1 = get_real_len(str1);
    // len2 = get_real_len(str2);

    char *conc = concatenate(str1, len1, str2, len2);
    printf("Concatenated - \"%s\"\n", conc);

    delete[] str1;
    delete[] str2;
    delete[] conc;

    return 0;
}