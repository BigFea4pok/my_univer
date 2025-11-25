#include <stdio.h>

int main() {

    char buf[5]; // маленький буфер для демонстрации

    printf("Введите строку:\n");
    if (fgets(buf, sizeof buf, stdin) != NULL) {
        int i = 0;
        int truncated = 0;

        /* Идём по буферу, пока не встретим '\0' или '\n' */
        while (buf[i] != '\0' && buf[i] != '\n') {
            i++;
        }

        if (buf[i] == '\n') {
            /* Заменяем финальный перевод строки на '\0' */
            buf[i] = '\0';
        } else {
            /* Нет '\n' — возможно ввод был длиннее буфера.
               Очистим остаток в stdin до конца строки. */
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { /* пусто */ }
            truncated = 1;
        }

        printf("Результат: \"%s\"%s\n", buf, truncated ? " (ввод был длиннее буфера, обрезано)" : "");
    }

    return 0;
}
