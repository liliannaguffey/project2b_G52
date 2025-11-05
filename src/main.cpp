//
// Created by josha on 11/3/2025.
//

#include "main.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "Food.cpp"
#include "quicksort.cpp"
#include "heapify.cpp"
#include "heapsort.cpp"
using namespace std;

void printTopFoods(const vector<Food>& foods, int nutrientIdx, int topN = 5) {
  if (foods.empty()) return;
  int n = static_cast<int>(foods.size());
  int start = max(0, n - topN);
  for (int i = n-1; i >= start; --i) {
    cout << foods[i].description << ": " << foods[i].nutrients[nutrientIdx] << "\n";
  }
}

int main() {
  std::vector<string> headers;
  auto foods = parseFoods("food.csv", headers);
  if (foods.empty()) {
    cerr << "Failed too load data.\n";
    return 1;
  }

  vector<string> nutrients;
  for (size_t i = 3; i < headers.size(); ++i) {
    nutrients.push_back(headers[i]);
  }
  cout << "\n Available nutrients(" << nutrients.size() << " total):\n";
  for (size_t i = 0; i < nutrients.size(); ++i) {
    cout << (i+1) << ". " << nutrients[i] << "\n";
  }
  string response;
  do {
    int choice = 0;
    string input;
    while (choice < 1 || choice > (int)nutrients.size()) {
      cout << "Enter the number of the nutrient you wish to sort by: ";
      getline(cin, input);
      try {
        choice = stoi(input);
      }catch (...) {
        choice = 0;
      }
      if (choice < 1 || choice > (int)nutrients.size()) {
        cout << "Please enter a number between 1 and " << nutrients.size() << ".\n";
      }
    }
    string selectedNutrient = nutrients[choice - 1];
    int nutrientIdx = choice - 1;
    cout << "Sorting by: " << selectedNutrient << "...\n";
    vector<Food> foodCopy = foods;

    auto start = chrono::high_resolution_clock::now();
    quicksort(foods, nutrientIdx);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> quicksortTime = end - start;

    cout << "\n Top 5 foods high in " << selectedNutrient << ":\n";
    printTopFoods(foods, nutrientIdx);
    cout << "Quicksort Elapsed Time: " << quicksortTime.count() << " seconds\n" << endl;

    start = chrono::high_resolution_clock::now();
    heapsort(foodCopy, nutrientIdx);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> heapsortTime = end - start;

    printTopFoods(foodCopy, nutrientIdx);
    cout << "Heapsort Elapsed Time: " << heapsortTime.count() << " seconds" << endl;

    cout <<"\n Check another nutrient? (y/n): ";
    getline(cin, response);
  }while (response == "y" || response == "Y");

  cout << "Eat Healthy!\n";
  return 0;
}