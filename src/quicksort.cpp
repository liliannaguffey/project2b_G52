//
// Created by josha on 11/3/2025.
//
using namespace std;

#include "quicksort.h"
#include <algorithm>

static int partition(vector<Food>& arr, int low, int high, int nutrientIdx) {
    double pivot = arr[high].nutrients[nutrientIdx];
    int i = low-1;
    for (int j = low; j < high; ++j) {
        if (arr[j].nutrients[nutrientIdx] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i + 1;
}

static void quicksort_impl(vector<Food>& arr, int low, int high, int nutrientIdx) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high, nutrientIdx);
        quicksort_impl(arr, low, pivotIndex-1, nutrientIdx);
        quicksort_impl(arr, pivotIndex+1, high, nutrientIdx);
    }
}
void quicksort(vector<Food>& foods, int nutrientIdx) {
    if (!foods.empty()) {
        quicksort_impl(foods, 0, static_cast<int>(foods.size())-1, nutrientIdx);
    }
}

