// Тимченко
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>

#define MIN_VAL -100
#define MAX_VAL 100
#define SIZES 3

using namespace std;

void fill_arr(int *arr, int size, int min_value, int max_value);
int *concatenation(int *arr1, int *arr2, int size);
unordered_set<int> find_duplicates_with_loops(int *arr, int size);
unordered_set<int> find_duplicates_with_set(int *arr, int size);

int main(void) {
    srand(static_cast<int>(time(nullptr)));
    int *arrs_sizes = new int[SIZES];
    for (int i = 0; i < SIZES; i++) {
        arrs_sizes[i] = 1000 * pow(100, i);
    }

    printf("-----------------------------------\n\n");
    for (int i = 0; i < SIZES; i++) {
        int *first_arr = new int[arrs_sizes[i]], *second_arr = new int[arrs_sizes[i]];
        fill_arr(first_arr, arrs_sizes[i], MIN_VAL, MAX_VAL);
        fill_arr(second_arr, arrs_sizes[i], MIN_VAL, MAX_VAL);

        auto start_c = std::chrono::high_resolution_clock::now();
        int *new_arr = concatenation(first_arr, second_arr, arrs_sizes[i]);
        auto end_c = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_c = end_c - start_c;

        int *new_arr_copy = new int[arrs_sizes[i] * 2];
        for (int i = 0; i < arrs_sizes[i] * 2; i++) {
            new_arr_copy[i] = new_arr[i];
        }

        auto start_1 = std::chrono::high_resolution_clock::now();
        unordered_set<int> loops_duplicates = find_duplicates_with_loops(new_arr, arrs_sizes[i] * 2);
        auto end_1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_1 = end_1 - start_1;

        auto start_2 = std::chrono::high_resolution_clock::now();
        unordered_set<int> set_duplicates = find_duplicates_with_set(new_arr, arrs_sizes[i] * 2);
        auto end_2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_2 = end_2 - start_2;

        printf("New array length: %d;\n", arrs_sizes[i] * 2);
        printf("Concatenation time: %.10lf;\n", elapsed_c.count());
        printf("Searching duplicates\nwith loops: %.10lf;\n", elapsed_1.count());
        printf("Searching duplicates with\nunordered set: %.10lf;\n", elapsed_2.count());
        printf("\n-----------------------------------\n\n");

        delete[] first_arr;
        delete[] second_arr;
        delete[] new_arr;
        delete[] new_arr_copy;
    }

    delete[] arrs_sizes;
    return 0;
}

// O(n)
void fill_arr(int *arr, int size, int min_value, int max_value) {
    for (int i = 0; i < size; i++) {
        arr[i] = min_value + rand() % (max_value - min_value + 1);
    }
}

// O(2 * n)
int *concatenation(int *arr1, int *arr2, int size) {
    int *new_arr = new int[size * 2];
    for (int i = 0; i < size; i++) {
        new_arr[i] = arr1[i];
    }
    for (int i = 0; i < size; i++) {
        new_arr[i + size] = arr2[i];
    }
    return new_arr;
}

// O(n**2), вложенный цикл
unordered_set<int> find_duplicates_with_loops(int *arr, int size) {
    unordered_set<int> result_array;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                result_array.insert(arr[i]);
                break;
            }
        }
    }
    return result_array;
}

// O(n), один проход по массиву
unordered_set<int> find_duplicates_with_set(int *arr, int size) {
    unordered_set<int> seen;
    unordered_set<int> duplicates;
    for (int i = 0; i < size; i++) {
        if (seen.count(arr[i])) {
            duplicates.insert(arr[i]);
        } else {
            seen.insert(arr[i]);
        }
    }
    return duplicates;
}
