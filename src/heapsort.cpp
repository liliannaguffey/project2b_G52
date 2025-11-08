#include "heapsort.h"
#include "heapify.h"
#include <vector>
#include <algorithm>
using namespace std;

void heapsort(vector<Food>& arr, int nutrientIdx) {
    int size = arr.size();
    buildHeap(arr, size, nutrientIdx);
    for (int i = size - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapifyDown(arr, 0, i, nutrientIdx);
    }
}