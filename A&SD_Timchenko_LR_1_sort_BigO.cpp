// Тимченко
#include <chrono>
#include <cstdio>
#include <cstdlib>

#define MIN_VAL -5
#define MAX_VAL 5

int fill_arr(int *arr, int size, int min_value, int max_value);
int read_int(const char *prompt, int *value, int *status);
int is_subsequence(int *arr1, int size1, int *arr2, int size2);

int main(void) {
    srand(static_cast<int>(time(nullptr)));
    int first_size, second_size, status = 1;
    read_int("Input size of first array: ", &first_size, &status);
    read_int("Input size of second array: ", &second_size, &status);
    if (status == 0) {
        return 1;
    }
    if (second_size > first_size) {
        printf("Second array can't be subsequence of first one.\n");
        return 1;
    }
    int *array = new int[first_size];
    int *another_array = new int[second_size];
    if (!(fill_arr(array, first_size, MIN_VAL, MAX_VAL) ||
          fill_arr(another_array, second_size, MIN_VAL, MAX_VAL))) {
        printf("Filling error\n");
        return 1;
    }
    for (int i = 0; i < first_size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    for (int i = 0; i < second_size; i++) {
        printf("%d ", another_array[i]);
    }
    printf("\n");
    printf("Is subsequence: %s",
           is_subsequence(array, first_size, another_array, second_size) ? "Yes\n" : "No\n");
    delete[] array;
    delete[] another_array;
    return 0;
}

int read_int(const char *prompt, int *value, int *status) {
    *status = 1;
    printf("%s", prompt);
    if (scanf("%d", value) != 1) {
        printf("Input error\n");
        *status = 0;
    }
    return *status;
}

// O(n)
int fill_arr(int *arr, int size, int min_value, int max_value) {
    int status = 1;
    if (max_value < min_value) {
        printf("Filling error\n");
        status = 0;
    } else {
        for (int i = 0; i < size; i++) {
            arr[i] = min_value + rand() % (max_value - min_value + 1);
        }
    }
    return status;
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
