#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10

struct UserRec {
    int present;
    unsigned char index;
    char *surname;
    char *name;
    char *patronymic;
    int has_age;
    unsigned char age;
    int has_sex;
    char sex;
    int has_usage;
    unsigned short usage;
};

void init_user(UserRec *u) {
    u->present = 0;
    u->index = 0;
    u->surname = NULL;
    u->name = NULL;
    u->patronymic = NULL;
    u->has_age = 0;
    u->age = 0;
    u->has_sex = 0;
    u->sex = 0;
    u->has_usage = 0;
    u->usage = 0;
}

void free_user(UserRec *u) {
    if (u->surname) { delete[] u->surname; u->surname = NULL; }
    if (u->name)    { delete[] u->name;    u->name = NULL; }
    if (u->patronymic) { delete[] u->patronymic; u->patronymic = NULL; }
    init_user(u);
}

int read_byte(FILE *f) {
    int c = fgetc(f);
    if (c == EOF) return -1;
    return c & 0xFF;
}

// Печать примера лэйаута (информативно)
void print_file_layout_example() {
    puts("Пример лэйаута файла (hex, байт за байтом) для двух пользователей:");
    puts("02                <- число пользователей = 2");
    puts("01 26             <- блок 1: индекс=1, длина оставшихся данных = 0x26 (38)");
    puts("... далее поля: ID, length, data ...");
    puts("(см. условие лабораторной для полного примера)\n");
}

// Парсер файла: читает бинарный файл filename и заполняет массив users, возвращает число прочитанных пользователей или -1 при ошибке.
int parse_user_file(const char *filename, UserRec users[], int max_users) {
    for (int i = 0; i < max_users; ++i) init_user(&users[i]);

    FILE *f = fopen(filename, "rb");
    if (!f) {
        perror("fopen");
        return -1;
    }

    int c = read_byte(f);
    if (c < 0) { fclose(f); printf("Файл пуст или ошибка чтения\n"); return -1; }
    unsigned char count = (unsigned char)c;

    if (count == 0) {
        fclose(f);
        return 0;
    }

    if (count > (unsigned char)max_users) {
        printf("В файле указано %u пользователей, но будет прочитано максимум %d.\n", count, max_users);
    }

    int users_read = 0;

    for (int user_i = 0; user_i < count && users_read < max_users; ++user_i) {
        int idx = read_byte(f);
        int len = read_byte(f);
        if (idx < 0 || len < 0) {
            printf("Неожиданный конец файла при чтении заголовка блока\n");
            break;
        }
        unsigned char index = (unsigned char)idx;
        unsigned char datalen = (unsigned char)len;

        unsigned char *buf = new unsigned char[datalen];
        size_t got = fread(buf, 1, datalen, f);
        if (got != datalen) {
            printf("Не удалось прочитать ожидаемые %u байт блока (прочитано %zu). Файл возможно повреждён.\n", datalen, got);
            delete[] buf;
            break;
        }

        UserRec u;
        init_user(&u);
        u.present = 1;
        u.index = index;

        int p = 0;
        while (p < datalen) {
            unsigned char id = buf[p++];
            if (p >= datalen) { printf("Ошибка формата: ожидался байт длины после ID, но достигнут конец блока\n"); break; }
            unsigned char dlen = buf[p++];
            if (p + dlen > datalen) {
                printf("Ошибка формата: поле ID=0x%02x заявлено длиной=%u, но в блоке не хватает байт\n", id, dlen);
                break;
            }

            if (id == 0x01) {
                char *s = new char[dlen + 1];
                for (int i = 0; i < dlen; ++i) s[i] = (char)buf[p + i];
                s[dlen] = '\0';
                u.surname = s;
            } else if (id == 0x02) {
                char *s = new char[dlen + 1];
                for (int i = 0; i < dlen; ++i) s[i] = (char)buf[p + i];
                s[dlen] = '\0';
                u.name = s;
            } else if (id == 0x03) {
                char *s = new char[dlen + 1];
                for (int i = 0; i < dlen; ++i) s[i] = (char)buf[p + i];
                s[dlen] = '\0';
                u.patronymic = s;
            } else if (id == 0x04) {
                if (dlen >= 1) {
                    u.age = (unsigned char)buf[p];
                    u.has_age = 1;
                }
            } else if (id == 0x05) {
                if (dlen >= 1) {
                    u.sex = (char)buf[p];
                    u.has_sex = 1;
                }
            } else if (id == 0x06) {
                if (dlen >= 2) {
                    unsigned short val = (unsigned short)buf[p] | ((unsigned short)buf[p+1] << 8);
                    u.usage = val;
                    u.has_usage = 1;
                }
            } else {
                // неизвестный ID — пропускаем
            }

            p += dlen;
        }

        users[users_read] = u;
        users_read++;

        delete[] buf;
    }

    fclose(f);
    return users_read;
}

void print_user(const UserRec *u, int pos) {
    if (!u || !u->present) {
        printf("Пользователь с порядковым номером %d отсутствует.\n", pos);
        return;
    }
    printf("---- Пользователь #%d (внутренний индекс = %u) ----\n", pos, (unsigned int)u->index);
    if (u->surname) printf("Фамилия : %s\n", u->surname); else printf("Фамилия : [нет данных]\n");
    if (u->name)    printf("Имя     : %s\n", u->name);      else printf("Имя     : [нет данных]\n");
    if (u->patronymic) printf("Отчество: %s\n", u->patronymic); else printf("Отчество: [нет данных]\n");
    if (u->has_age) printf("Возраст : %u\n", (unsigned int)u->age); else printf("Возраст : [нет данных]\n");
    if (u->has_sex) printf("Пол     : %c\n", u->sex); else printf("Пол     : [нет данных]\n");
    if (u->has_usage) printf("Использований услуги: %u\n", (unsigned int)u->usage); else printf("Использований: [нет данных]\n");
    printf("-------------------------------------------\n");
}

void print_all_users(const UserRec users[], int n) {
    if (n <= 0) { puts("В файле нет пользователей."); return; }
    for (int i = 0; i < n; ++i) {
        print_user(&users[i], i);
    }
}

int main(int argc, char *argv[]) {
    const char *default_path = "./UserData-LR-5.bin";
    const char *filename = default_path;
    if (argc > 1) filename = argv[1];

    printf("=== ЛР №5 — Чтение файла пользователей ===\n\n");
    print_file_layout_example();
    printf("Открываем файл: %s\n", filename);

    UserRec users[MAX_USERS];
    for (int i = 0; i < MAX_USERS; ++i) init_user(&users[i]);

    int user_count = parse_user_file(filename, users, MAX_USERS);
    if (user_count < 0) {
        printf("Ошибка при разборе файла '%s'. Убедитесь, что файл существует и формат корректен.\n", filename);
        return 1;
    }
    printf("В файле прочитано %d пользователей (максимум %d)\n\n", user_count, MAX_USERS);

    printf("Команды:\n");
    printf("  a или A  — распечатать всех пользователей\n");
    printf("  0..9     — распечатать пользователя с указанным порядковым номером (0 — первый)\n");
    printf("  e или E  — выход\n");
    printf("Ввод команды: ");

    int ch;
    while ( (ch = getchar()) != EOF ) {
        if (ch == '\n') { putchar('>'); continue; }
        if (ch == 'a' || ch == 'A') {
            print_all_users(users, user_count);
        } else if (ch >= '0' && ch <= '9') {
            int idx = ch - '0';
            if (idx < user_count) {
                print_user(&users[idx], idx);
            } else {
                printf("Пользователя с индексом %d нет (в файле только %d пользователей).\n", idx, user_count);
            }
        } else if (ch == 'e' || ch == 'E') {
            printf("Выход из программы.\n");
            break;
        } else {
            // игнорируем
        }
        int cc;
        while ((cc = getchar()) != '\n' && cc != EOF) { /* пропускаем */ }
        printf("Ввод команды: ");
    }

    for (int i = 0; i < MAX_USERS; ++i) free_user(&users[i]);

    return 0;
}
