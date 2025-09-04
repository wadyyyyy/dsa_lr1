// Тимченко
#include <chrono>
#include <cstdio>
#include <cstdlib>

int fill_arr(int *arr, int size, int min_value, int max_value);
int read_int(const char *prompt, int *value, int *status);

int main(void) {
    srand(static_cast<int>(time(NULL)));
    int size, min_value, max_value, status = 1;
    read_int("Input size: ", &size, &status);
    read_int("Input min value: ", &min_value, &status);
    read_int("Input max value: ", &max_value, &status);
    if (status == 0) {
        return 1;
    }
    int *array = new int[size];
    fill_arr(array, size, min_value, max_value);
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    delete[] array;
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

int fill_arr(int *arr, int size, int min_value, int max_value) {
    int status = 1;
    if (max_value < min_value) {
        status = 0;
    } else {
        for (int i = 0; i < size; i++) {
            arr[i] = min_value + rand() % (max_value - min_value + 1);
        }
    }
    return status;
}
