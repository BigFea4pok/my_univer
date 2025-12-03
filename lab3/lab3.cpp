#include <stdio.h>
#include <string.h> // для memcmp/memcpy/memset в части 2

 // 2) my_strlen
int my_strlen(const char *s) {
    if (!s) return 0;   // указатель s может быть пустым(nullptr), это защита.
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

// 1) concat_strings
// Cоединяет s1 и s2, возвращает новый буфер
// Если lenX <= 0 — длина вычисляется через my_strlen
char* concat_strings(const char *s1, int len1, const char *s2, int len2) {
    if (!s1) s1 = "";   // если строки пусты (нет значений), присвоим ""
    if (!s2) s2 = "";
    int l1 = (len1 > 0) ? len1 : my_strlen(s1);     // пользователь мог указать некорректно или вообще не указать len
    int l2 = (len2 > 0) ? len2 : my_strlen(s2);
    // выделяем память на l1 + l2 + 1
    char *res = new char[l1 + l2 + 1];
    // копируем вручную
    for (int i = 0; i < l1; ++i) res[i] = s1[i];
    for (int j = 0; j < l2; ++j) res[l1 + j] = s2[j];
    res[l1 + l2] = '\0';
    return res;
}

// 4) compare_strings
// возвращает 1 если строки полностью совпадают (и длины совпадают), иначе 0
int compare_strings(const char *a, const char *b) {
    if (a == nullptr && b == nullptr) return 1;   // обе строки пустные, но совпадают. Полное совпадение - 1
    if (a == nullptr || b == nullptr) return 0;   // одна строка пустая, другая нет. Не совпадение - 0
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {  // проверяем, чтобы обе строки продолжались
        if (a[i] != b[i]) return 0;     // Обе строки продолжились. Проверяем, чтобы текущие символы совпадали.
        ++i;
    }
    // Одна из строк закончилась. Но был ++i. Теперь надо проверить если обе строки закончились на \0
    return (a[i] == '\0' && b[i] == '\0') ? 1 : 0;
}

// 3) replace_substring_inplace
// Функция делает все замены (все неперекрывающиеся вхождения слева направо) и возвращает число замен.
// Если итоговая длина > pStr_len-1 (нет места), функция НЕ меняет pStr и возвращает -1.
int replace_substring_inplace(char *pStr, int pStr_len,
                              const char *pSub1, int len1,
                              const char *pSub2, int len2) {
    if (!pStr || !pSub1 || !pSub2 || pStr_len <= 0) return -1;
    int orig_len = my_strlen(pStr);
    int s1 = (len1 > 0) ? len1 : my_strlen(pSub1);
    int s2 = (len2 > 0) ? len2 : my_strlen(pSub2);

    if (s1 == 0) return 0; // защита: не ищем пустую подстроку

    // 1) Подсчёт количества неперекрывающихся вхождений pSub1 в pStr
        /* Пример: pStr="aaaa", pSub1="aa": неперекрывающие вхождения будут в 
        позициях 0 и 2 — match_counter=2.*/

    int match_counter = 0;
    for (int i = 0; i <= orig_len - s1; ) {     // - s1, потому что если подстрока pSub1 будет самом в конце pStrб то pSub1 начнется с orig_len - s1
        bool match = true;
        for (int k = 0; k < s1; ++k) {
            if (pStr[i + k] != pSub1[k]) { match = false; break; }
        }
        if (match) { ++match_counter; i += s1; } // неперекрывающимся способом.
        else ++i;
    }
    if (match_counter == 0) return 0; // ничего не найдено, ничего не делаем

    // 2) Проверка нового размера
    long new_len = (long)orig_len + (long)match_counter * (long)(s2 - s1);
    if (new_len > (long)(pStr_len - 1)) {
        // не помещается — не изменяем pStr, возвращаем ошибку
        return -1;
    }

    // 3) Собираем новую строку во временный буфер 
    char *tmp = new char[pStr_len];

    int ri = 0;
    for (int i = 0; i < orig_len; ) {
        bool match = false;
        if (i <= orig_len - s1) {
            match = true;
            for (int k = 0; k < s1; ++k) {
                if (pStr[i + k] != pSub1[k]) { match = false; break; }
            }
        } else {
            match = false;
        }
        if (match) {
            // вставляем pSub2
            for (int k = 0; k < s2; ++k) tmp[ri++] = pSub2[k];
            i += s1;
        } else {
            tmp[ri++] = pStr[i++];
        }
    }
    tmp[ri] = '\0';

    // 4) Копируем результат обратно в pStr и очищаем tmp
    for (int i = 0; i <= ri; ++i) pStr[i] = tmp[i];
    delete[] tmp;
    return match_counter;
}

// работа с памятью 1
void reverse_blocks_inplace(int *arr, int arr_len, int block_len) {
    // Проверки входных параметров
    if (arr == nullptr) return;            // нет массива — нечего делать
    if (arr_len <= 0) return;           // некорректная длина
    if (block_len <= 0) return;         // некорректный размер блока

    // Сколько полных блоков помещается в массив
    int full_blocks = arr_len / block_len;
    if (full_blocks <= 1) return;       // нечего инвертировать

    // Выделяем временный буфер для одного блока
    int *temp = new int[block_len];

    // Меняем блоки попарно: i-й с (N-1-i)-м
    for (int i = 0; i < full_blocks / 2; ++i) {
        int left_idx = i * block_len;                         // индекс первого элемента левого блока
        int right_idx = (full_blocks - 1 - i) * block_len;    // индекс первого элемента правого блока

        // temp = left_block
        memcpy(temp, &arr[left_idx], (size_t)block_len * sizeof(int));
        // left_block = right_block
        memcpy(&arr[left_idx], &arr[right_idx], (size_t)block_len * sizeof(int));
        // right_block = temp (старый left)
        memcpy(&arr[right_idx], temp, (size_t)block_len * sizeof(int));
    }

    // Освобождаем временный буфер
    delete[] temp;
}

// работа с памятью 2
int count_block_occurrences(const int *arr, int arr_len, const int *block, int block_len) {
    if (arr == nullptr || block == nullptr) return 0;
    if (arr_len <= 0 || block_len <= 0) return 0;
    if (block_len > arr_len) return 0;

    int count = 0;
    size_t bytes = (size_t)block_len * sizeof(int); // число байт для сравнения

    // Проходим по всем возможным стартовым индексам, допускаем перекрытия
    for (int i = 0; i <= arr_len - block_len; ++i) {
        // сравниваем блок arr[i..i+block_len-1] с block[0..block_len-1]
        if (memcmp(&arr[i], block, bytes) == 0) {
            ++count;
        }
    }
    return count;
}



// ---------------------------
// Тестовый хелпер
// ---------------------------
static int tests_total = 0;
static int tests_passed = 0;

void report_bool(const char *name, bool ok) {
    ++tests_total;
    if (ok) {
        ++tests_passed;
        printf("[PASS] %s\n", name);
    } else {
        printf("[FAIL] %s\n", name);
    }
}

void report_int_eq(const char *name, int expected, int actual) {
    char buf[200];
    bool ok = (expected == actual);
    if (!ok) snprintf(buf, sizeof(buf), "%s (expected=%d, actual=%d)", name, expected, actual);
    report_bool(ok ? name : buf, ok);
}

void report_str_eq(const char *name, const char *expected, const char *actual) {
    bool ok;
    if (expected == nullptr && actual == nullptr) ok = true;
    else if (expected == nullptr || actual == nullptr) ok = false;
    else ok = (strcmp(expected, actual) == 0);
    char buf[300];
    if (!ok) {
        snprintf(buf, sizeof(buf), "%s (expected=\"%s\", actual=\"%s\")", name, expected ? expected : "NULL", actual ? actual : "NULL");
    }
    report_bool(ok ? name : buf, ok);
}

bool arrays_equal(const int *a, const int *b, int n) {
    for (int i = 0; i < n; ++i) if (a[i] != b[i]) return false;
    return true;
}

void report_array_eq(const char *name, const int *expected, const int *actual, int n) {
    bool ok = arrays_equal(expected, actual, n);
    if (ok) report_bool(name, true);
    else {
        char buf[400];
        char ea[200] = {0}, aa[200] = {0};
        char tmp[32];
        for (int i = 0; i < n; ++i) { snprintf(tmp, sizeof(tmp), "%d ", expected[i]); strncat(ea, tmp, sizeof(ea)-strlen(ea)-1); }
        for (int i = 0; i < n; ++i) { snprintf(tmp, sizeof(tmp), "%d ", actual[i]); strncat(aa, tmp, sizeof(aa)-strlen(aa)-1); }
        snprintf(buf, sizeof(buf), "%s (expected=[%s], actual=[%s])", name, ea, aa);
        report_bool(buf, false);
    }
}

// ---------------------------
// Тесты
// ---------------------------
int main(void) {
    puts("=== Запуск тестов ===");

    // --- my_strlen ---
    report_int_eq("my_strlen(NULL) == 0", 0, my_strlen(NULL));
    report_int_eq("my_strlen(\"\") == 0", 0, my_strlen(""));

    // --- concat_strings ---
    char *joined = concat_strings("Hello", -1, " world", -1);
    report_str_eq("concat_strings basic", "Hello world", joined);
    delete[] joined;

    char *joined2 = concat_strings("ABCDE", 3, "XYZ", 2); // ожидаем "ABCXY"
    report_str_eq("concat_strings with lengths", "ABCXY", joined2);
    delete[] joined2;

    // --- compare_strings ---
    report_int_eq("compare_strings(NULL, NULL) == 1", 1, compare_strings(nullptr, nullptr));
    report_int_eq("compare_strings(\"abc\",\"abc\") == 1", 1, compare_strings("abc","abc"));
    report_int_eq("compare_strings(\"abc\",\"ab\") == 0", 0, compare_strings("abc","ab"));
    report_int_eq("compare_strings(NULL, \"a\") == 0", 0, compare_strings(nullptr,"a"));

    // --- replace_substring_inplace: базовый успешный пример ---
    char buf1[100];
    snprintf(buf1, sizeof(buf1), "foo bar foo");
    int r1 = replace_substring_inplace(buf1, (int)sizeof(buf1), "foo", -1, "baz", -1);
    report_int_eq("replace_substring_inplace count (foo->baz)", 2, r1);
    report_str_eq("replace_substring_inplace result (foo->baz)", "baz bar baz", buf1);

    // --- replace_substring_inplace: маленький буфер -->
    char small[8];
    snprintf(small, sizeof(small), "aaa_b");
    int r2 = replace_substring_inplace(small, (int)sizeof(small), "a", 1, "LONG", 4);
    report_int_eq("replace_substring_inplace small buffer returns -1", -1, r2);
    report_str_eq("small buffer unchanged", "aaa_b", small);

    // --- replace_substring_inplace: перекрывающийся пример (неперекрывающаяся логика) ---
    char buf2[20];
    snprintf(buf2, sizeof(buf2), "aaaa");
    int r3 = replace_substring_inplace(buf2, (int)sizeof(buf2), "aa", -1, "b", -1);
    report_int_eq("replace_substring_inplace overlapping count (aa->b) non-overlap", 2, r3);
    report_str_eq("replace_substring_inplace overlapping result", "bb", buf2);

    // --- replace_substring_inplace: нет вхождений ---
    char buf3[20];
    snprintf(buf3, sizeof(buf3), "hello");
    int r4 = replace_substring_inplace(buf3, (int)sizeof(buf3), "x", -1, "y", -1);
    report_int_eq("replace_substring_inplace no matches returns 0", 0, r4);
    report_str_eq("replace_substring_inplace no matches unchanged", "hello", buf3);

    // --- reverse_blocks_inplace ---
    int arr1[] = {1,2,3,4,5,6,7,8,9};
    int expected1[] = {7,8,9,4,5,6,1,2,3};
    reverse_blocks_inplace(arr1, 9, 3);
    report_array_eq("reverse_blocks_inplace full blocks", expected1, arr1, 9);

    // неполная последняя часть
    int arr3[] = {10,11,12,20,21};
    int expected3[] = {12,20,10,11,21}; // блоки [10,11],[12,20] => swapped, tail 21 stays
    reverse_blocks_inplace(arr3, 5, 2);
    report_array_eq("reverse_blocks_inplace with tail", expected3, arr3, 5);

    // --- count_block_occurrences ---
    int arr2[] = {1,2,3,4,1,2,1,2,9};
    int block[] = {1,2};
    int c1 = count_block_occurrences(arr2, sizeof(arr2)/sizeof(arr2[0]), block, sizeof(block)/sizeof(block[0]));
    report_int_eq("count_block_occurrences example", 3, c1);

    // overlapping count test
    int arr4[] = {1,1,1};
    int b2[] = {1,1};
    int c2 = count_block_occurrences(arr4, 3, b2, 2);
    report_int_eq("count_block_occurrences overlapping", 2, c2);

    // edge cases for count_block_occurrences
    report_int_eq("count_block_occurrences block_len > arr_len", 0, count_block_occurrences(arr4, 2, b2, 3));
    report_int_eq("count_block_occurrences null arr", 0, count_block_occurrences(nullptr, 3, b2, 2));
    report_int_eq("count_block_occurrences null block", 0, count_block_occurrences(arr4, 3, nullptr, 2));

    // Итог
    printf("\n=== Итог: %d/%d тестов пройдено ===\n", tests_passed, tests_total);
    return (tests_passed == tests_total) ? 0 : 1;

}