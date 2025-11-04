//
// Created by josha on 11/3/2025.
//

#ifndef FOOD_H
#define FOOD_H
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Food {
    std::string category;
    std::string description;
    std::vector<double> nutrients;
};

vector<string> parseHeader(const string& line);
vector<Food> parseFoods(const string& filename, vector<string>& headers);

#endif //FOOD_H
