#pragma once
#include "Food.h"
#include <vector>
using namespace std;

void buildHeap(vector<Food>& heap, int size, int nutrientIdx);
void heapifyDown(vector<Food>& heap, int index, int size, int nutrientIdx);
