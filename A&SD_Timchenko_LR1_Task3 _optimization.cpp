#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#define MIN_VAL -50
#define MAX_VAL 50
#define SIZES 3

using namespace std;

void fill_arr(vector<int> &arr, int size, int min_value, int max_value);
int arrs_comparison_slow(vector<int> &array1, vector<int> &array2);  // returns 1 if arrs are equal
int arrs_comparison_optimized(vector<int> &array1, vector<int> &array2);
void draw_dar(const string &label, double value, double max_value, int width = 20);

int main() {
    srand(static_cast<int>(time(nullptr)));
    vector<int> sizes;
    for (int i = 0; i < SIZES; i++) {
        sizes.push_back(1000 * pow(100, i));
    }
    vector<int> first_array_slow, second_array_slow, first_array_fast, second_array_fast;
    for (int i = 0; i < SIZES; i++) {
        int size = sizes[i];
        cout << "\n=== Тест для массива размера " << size << " ===" << endl;

        fill_arr(first_array_slow, size, MIN_VAL, MAX_VAL);
        first_array_fast = first_array_slow;
        fill_arr(second_array_slow, size, MIN_VAL, MAX_VAL);
        second_array_fast = second_array_slow;

        auto start_1 = std::chrono::high_resolution_clock::now();
        int first_result = arrs_comparison_slow(first_array_slow, second_array_slow);
        auto end_1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_1 = end_1 - start_1;

        auto start_2 = std::chrono::high_resolution_clock::now();
        int second_result = arrs_comparison_optimized(first_array_fast, second_array_fast);
        auto end_2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_2 = end_2 - start_2;

        cout << "Наивный метод: " << (first_result ? "Массивы равны" : "Массивы различаются")
             << ", время = " << elapsed_1.count() << " секунд" << endl;
        cout << "Оптимизированный метод: " << (second_result ? "Массивы равны" : "Массивы различаются")
             << ", время = " << elapsed_2.count() << " секунд" << endl;

        cout << "\nВизуализация времени (пропорциональные полоски):" << endl;
        double max_val = max(elapsed_1.count(), elapsed_2.count());
        draw_dar("Наивный метод", elapsed_1.count(), max_val, 30);
        draw_dar("Оптимизированный метод", elapsed_2.count(), max_val, 30);
        cout << "-------------------------------------------------" << endl;
    }

    return 0;
}

// O(n)
void fill_arr(vector<int> &arr, int size, int min_value, int max_value) {
    arr.resize(size);
    for (int i = 0; i < size; i++) {
        arr[i] = min_value + rand() % (max_value - min_value + 1);
    }
}

// O(n)
int arrs_comparison_slow(vector<int> &array1, vector<int> &array2) {
    int counter = 0;
    for (int i = 0; i < array1.size(); i++) {
        if (array1[i] != array2[i]) counter++;
    }
    return counter == 0;
}

// O(n)
int arrs_comparison_optimized(vector<int> &array1, vector<int> &array2) { return array1 == array2; }

void draw_dar(const string &label, double value, double max_value, int width) {
    int bar_len = static_cast<int>((value / max_value) * width);
    if (bar_len == 0) bar_len = 1;
    cout << label << " (" << value << " сек.):" << string(bar_len, '#') << endl;
}
