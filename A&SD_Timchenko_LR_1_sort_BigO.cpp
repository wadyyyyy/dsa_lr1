// Тимченко
#include <math.h>

#include <chrono>
#include <cstdio>
#include <cstdlib>

#define MIN_VAL -100
#define MAX_VAL 100
#define SIZES 3

void fill_arr(int *arr, int size, int min_value, int max_value);
int is_subsequence(int *arr1, int size1, int *arr2, int size2);

int main(void) {
    srand(static_cast<int>(time(nullptr)));
    int *first_arr_sizes = new int[SIZES];
    for (int i = 0; i < SIZES; i++) {
        first_arr_sizes[i] = 1000 * pow(100, i);
    }
    int *second_arr_sizes = new int[SIZES];
    for (int i = 0; i < SIZES; i++) {
        second_arr_sizes[i] = first_arr_sizes[i] / 100;
    }

    printf("---------------------------------");
    for (int i = 0; i < SIZES; i++) {
        int *first_arr = new int[first_arr_sizes[i]], *second_arr = new int[second_arr_sizes[i]];
        fill_arr(first_arr, first_arr_sizes[i], MIN_VAL, MAX_VAL);
        fill_arr(second_arr, second_arr_sizes[i], MIN_VAL, MAX_VAL);

        auto start = std::chrono::high_resolution_clock::now();
        bool result = is_subsequence(first_arr, first_arr_sizes[i], second_arr, second_arr_sizes[i]);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        printf("\n\nTest for sizes: %d, %d\n", first_arr_sizes[i], second_arr_sizes[i]);
        printf("Is subsequence: %s\n", result ? "Yes" : "No");
        printf("Execution time: %.10lf\n\n", elapsed.count());
        printf("---------------------------------");
        delete[] first_arr;
        delete[] second_arr;
    }

    delete[] first_arr_sizes;
    delete[] second_arr_sizes;
    return 0;
}

// O(n)
void fill_arr(int *arr, int size, int min_value, int max_value) {
    for (int i = 0; i < size; i++) {
        arr[i] = min_value + rand() % (max_value - min_value + 1);
    }
}

// O(n), точнее - O(size1)
int is_subsequence(int *arr1, int size1, int *arr2, int size2) {
    int j = 0;
    for (int i = 0; i < size1 && j < size2; i++) {
        if (arr1[i] == arr2[j]) {
            j++;
        }
    }
    return j == size2;
}
