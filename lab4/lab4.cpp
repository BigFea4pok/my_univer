#include <stdio.h>

// Функции для печати битов (bits битов, старший слева):
void print_bits_uint(unsigned int value, int bits, int group) {
    for (int i = bits - 1; i >= 0; --i) {
        unsigned int bit = (value >> i) & 1;
        putchar(bit ? '1' : '0');
        if (group > 0 && (i % group) == 0 && i != 0) putchar(' ');
    }
}

void print_bits_ushort(unsigned short value, int bits, int group) {
    for (int i = bits - 1; i >= 0; --i) {
        unsigned short bit = (value >> i) & 1;
        putchar(bit ? '1' : '0');
        if (group > 0 && (i % group) == 0 && i != 0) putchar(' ');
    }
}


// Часть 1
// Возвращает x mod 2^n без использования оператора %
unsigned int mod_pow2(unsigned int x, unsigned int n) {
    const unsigned int W = sizeof(unsigned int) * 8; // ширина в битах (обычно 32)
    if (n == 0) {      // 2^0 = 1 => остаток при делении на 1 всегда 0
        return 0;
    }
    if (n >= W) {       // деление на 2^W или больше: для W-битного unsigned x < 2^W, значит x % 2^W == x
        return x;
    }
    // Создаём маску с n единицами в младших битах:
    unsigned int all_ones = ~0;          // все биты 1 (например 0xFFFFFFFF)
    unsigned int mask = all_ones >> (W - n); // сдвиг вправо даёт n единиц в младших битах
    return x & mask;
}


// Часть 2: печать битов short и float
// Для short используем unsigned short для сдвигов
void print_short_bits(short s) {
    unsigned short u = (unsigned short)s; // raw bits
    int bits = sizeof(unsigned short) * 8;
    printf("short value = %d\nbits: ", (int)s);
    print_bits_ushort(u, bits, 4); // группируем по 4 бита
    putchar('\n');
}

// Часть 2: печать битов short и float
// Для float используем union для "переинтерпретации" битов
void print_float_bits(float f) {
    union convers { 
        float f; 
        unsigned int u; 
    };

    union convers conv; 
    conv.f = f;
    unsigned int bits = conv.u;
    const int W = sizeof(unsigned int) * 8; // обычно 32
    const int sign_bits = 1;
    const int exp_bits = 8;
    const int man_bits = W - sign_bits - exp_bits; // обычно 23

    printf("float value = %g\n", f);
    printf("bits: ");
    print_bits_uint(bits, W, 4);
    putchar('\n');

    // извлекаем поля
    unsigned int sign = (bits >> (W - 1)) & 1u; // старший бит
    unsigned int exp_mask = ((1u << exp_bits) - 1u); // 0xFF (неопасно — exp_bits=8)
    unsigned int exp = (bits >> man_bits) & exp_mask;
    unsigned int mantissa = bits & ((1u << man_bits) - 1u);

    // детальная печать
    printf("sign: %u\n", sign);
    printf("exponent (raw, biased): ");
    print_bits_uint(exp, exp_bits, 4);
    printf("  (decimal = %u)\n", exp);
    printf("mantissa (fraction bits): ");
    print_bits_uint(mantissa, man_bits, 4);
    putchar('\n');

    // интерпретация
    if (exp == 0u && mantissa == 0u) {
        printf("This is zero (sign = %u)\n", sign);
    } else if (exp == (unsigned int)((1u << exp_bits) - 1u)) {
        if (mantissa == 0u) printf("This is %s infinity\n", sign ? "negative" : "positive");
        else printf("This is NaN (Not a Number)\n");
    } else {
        int unbiased = (int)exp - 127; // bias for IEEE754 single
        printf("interpreted: sign=%u, exponent(biased)=%u, exponent(unbiased)=%d\n",
               sign, exp, unbiased);
    }
    putchar('\n');
}


// Часть 3: шифрование/дешифровка XOR-цепочкой
void encrypt_xor_seq(const int *pIn, int *pOut, int Size) {
    if (!pIn || !pOut || Size <= 0) return;
    pOut[0] = pIn[0];
    for (int i = 1; i < Size; ++i) {
        pOut[i] = pOut[i-1] ^ pIn[i];
    }
}

void decrypt_xor_seq(const int *pIn, int *pOut, int Size) {
    if (!pIn || !pOut || Size <= 0) return;
    pOut[0] = pIn[0];
    for (int i = 1; i < Size; ++i) {
        pOut[i] = pIn[i-1] ^ pIn[i];
    }
}



/* =========================
   Демонстрация и тесты
   ========================= */

int main(void) {
    puts("=== lab4_nostdint: демонстрация функций ===\n");

    // --- Тесты для mod_pow2 ---
    printf("--- Часть 1: mod_pow2 (x mod 2^n) ---\n");
    unsigned int xs[] = {0u, 1u, 5u, 16u, 29u, 12345u};
    unsigned int ns[] = {0u, 1u, 2u, 3u, 4u, 5u, 8u, 16u, 31u};
    for (int i = 0; i < (int)(sizeof(xs)/sizeof(xs[0])); ++i) {
        for (int j = 0; j < (int)(sizeof(ns)/sizeof(ns[0])); ++j) {
            unsigned int x = xs[i];
            unsigned int n = ns[j];
            unsigned int r = mod_pow2(x, n);
            // ожидаемое значение (для проверки) - считаем через % здесь только в демонстрации:
            unsigned int expected;
            if (n == 0u) expected = 0u;
            else if (n >= (unsigned int)(sizeof(unsigned int)*8)) expected = x;
            else expected = x % (1u << n);
            printf("x=%5u (bin=", x);
            print_bits_uint(x, (int)(sizeof(unsigned int)*8), 8);
            printf(") n=%2u -> mod_pow2=%5u (expected=%5u)\n", n, r, expected);
        }
    }
    putchar('\n');

    // --- Часть 2: печать short и float ---
    printf("--- Часть 2: битовые представления short и float ---\n");
    short s1 = -12345;
    print_short_bits(s1);

    float f1 = -12.375f; // пример: -12.375 = - (1100.011)_2
    print_float_bits(f1);

    // Ввод от пользователя (опционально)
    printf("Введите short и float через пробел (например: -5 3.25), либо нажмите Enter чтобы пропустить:\n");
    short user_s;
    float user_f;
    int rc = scanf("%hd %f", &user_s, &user_f);
    if (rc == 2) {
        print_short_bits(user_s);
        print_float_bits(user_f);
    } else {
        printf("Ввод пропущен или некорректен — продолжаем демонстрацию.\n\n");
    }

    // --- Часть 3: шифрование/дешифровка ---
    printf("--- Часть 3: XOR-шифрование и дешифровка ---\n");
    const int Size = 30;
    int A[Size], B[Size], C[Size];
    for (int i = 0; i < Size; ++i) A[i] = -15 + i; // -15..+14

    printf("Исходный массив A:\n");
    for (int i = 0; i < Size; ++i) {
        printf("%4d ", A[i]);
        if ((i+1) % 10 == 0) putchar('\n');
    }
    putchar('\n');

    encrypt_xor_seq(A, B, Size);

    printf("Зашифрованный массив B:\n");
    for (int i = 0; i < Size; ++i) {
        printf("%4d ", B[i]);
        if ((i+1) % 10 == 0) putchar('\n');
    }
    putchar('\n');

    decrypt_xor_seq(B, C, Size);

    printf("Дешифрованный массив C (должен совпадать с A):\n");
    for (int i = 0; i < Size; ++i) {
        printf("%4d ", C[i]);
        if ((i+1) % 10 == 0) putchar('\n');
    }
    putchar('\n');

    // Проверка равенства A и C
    int ok = 1;
    for (int i = 0; i < Size; ++i) if (A[i] != C[i]) { ok = 0; break; }
    if (ok) printf("Успех: дешифровка вернула исходный массив A.\n");
    else printf("Ошибка: дешифровка не совпала с A.\n");

    puts("\n=== Конец демонстрации ===");
    return 0;
}
