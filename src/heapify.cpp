#include "heapify.h"
#include <algorithm>
using namespace std;

//pseudocode from discussion slides
void buildHeap(vector<Food>& arr, int size, int nutrientIdx) {
    int startIndex = (size/2)-1;
    for (int i = startIndex; i >= 0; i--) {
        heapifyDown(arr, i, size, nutrientIdx);
    }
}

void heapifyDown(vector<Food>& arr, int index, int size, int nutrientIdx) {
    int newParentIndex = index;
    if ((2*index+1 < size) && (arr[(2*index)+1].nutrients[nutrientIdx] > arr[newParentIndex].nutrients[nutrientIdx])) {
        newParentIndex = (2*index)+1;
    }
    if ((2*index+2) < size && (arr[(2*index)+2].nutrients[nutrientIdx] > arr[newParentIndex].nutrients[nutrientIdx])) {
        newParentIndex = (2*index)+2;
    }
    if (newParentIndex != index) {
        swap(arr[index], arr[newParentIndex]);
        heapifyDown(arr, newParentIndex, size, nutrientIdx);
    }
}