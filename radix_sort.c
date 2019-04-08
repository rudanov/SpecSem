#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_ARRAY_SIZE 200000
#define MAX_ELEM 20000
#define MAX_DIGITS_IN_NUM  10


int get_digit(int number, int position) {
    return number / (int)(pow(10, position)) % 10;
}

int get_byte(int number, int position) {
    return (number & (255 << position * 8)) >> position * 8;
}

void reverse(int* array, int array_len) {
    for (int i = 0; i < array_len / 2; ++i) {
        int swap_var = array[i];
        array[i] = array[array_len - i - 1];
        array[array_len - i - 1] = swap_var;
    }
}

void make_negative(int* array, int array_len) {
    for (int i = 0; i < array_len; ++i)
       array[i] *= -1;
}

void counting_sort(int* array, int* result, int array_len) {
    int counters[MAX_ELEM] = {};
    for (int i = 0; i < array_len; ++i)
        ++counters[array[i]];
    for (int i = 1; i < MAX_ELEM; ++i)
        counters[i] += counters[i-1];
    for (int i = array_len - 1; i >= 0; --counters[array[i]], --i)
        result[counters[array[i]] - 1] = array[i];
}

void signed_counting_sort(int* array, int* result, int array_len) {
    int negative[MAX_ARRAY_SIZE] = {}, positive[MAX_ARRAY_SIZE] = {};
    int neg_i = 0, pos_i = 0;
    for (int i = 0; i < array_len; ++i) {
        if (array[i] < 0) {
            negative[neg_i] = abs(array[i]);
            ++neg_i;
        } else {
            positive[pos_i] = array[i];
            ++pos_i;
        }
    }

    memset(result, 0, array_len * sizeof(int));
    counting_sort(negative, result, neg_i);
    reverse(result, neg_i);
    make_negative(result, neg_i);
    counting_sort(positive, result + neg_i, pos_i);
}

void digit_counting_sort(int* array, int* result, int array_len, int position) {
    int counters[MAX_ELEM] = {};
    for (int i = 0; i < array_len; ++i)
        ++counters[get_digit(array[i], position)];
    for (int i = 1; i < MAX_ELEM; ++i)
        counters[i] += counters[i-1];
    for (int i = array_len - 1; i >= 0; --counters[get_digit(array[i], position)], --i)
        result[counters[get_digit(array[i], position)] - 1] = array[i];
}

void byte_counting_sort(int* array, int* result, int array_len, int position) {
    int counters[MAX_ELEM] = {};
    for (int i = 0; i < array_len; ++i)
        ++counters[get_byte(array[i], position)];
    for (int i = 1; i < MAX_ELEM; ++i)
        counters[i] += counters[i-1];
    for (int i = array_len - 1; i >= 0; --counters[get_byte(array[i], position)], --i)
        result[counters[get_byte(array[i], position)] - 1] = array[i];
}


void radix_sort(int* array, int* result, int array_len) {
    int* buffer = (int*)(malloc(array_len * sizeof(int)));
    memcpy(buffer, array, array_len * sizeof(int));

    for(int i = 0; i < MAX_DIGITS_IN_NUM; ++i) {
        digit_counting_sort(buffer, result, array_len, i);
        memcpy(buffer, result, array_len * sizeof(int));
    }

    free(buffer);
}

void byte_radix_sort(int* array, int* result, int array_len) {
    int* buffer = (int*)(malloc(array_len * sizeof(int)));
    memcpy(buffer, array, array_len * sizeof(int));

    for(int i = 0; i < sizeof(int); ++i) {
        digit_counting_sort(buffer, result, array_len, i);
        memcpy(buffer, result, array_len * sizeof(int));
    }

    free(buffer);
}

int main(void) {
    int array[MAX_ARRAY_SIZE], result[MAX_ARRAY_SIZE];
    int array_size;

    scanf("%d", &array_size);
    for (int i = 0; i < array_size; ++i)
        scanf("%d", array + i);

    signed_counting_sort(array, result, array_size);
    //byte_radix_sort(array, result, array_size);

    for (int i = 0; i < array_size; ++i)
        printf("%d ", result[i]);
    printf("\n");

    return 0;
}
