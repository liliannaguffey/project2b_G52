//
// Created by josha on 11/3/2025.
//

#include "Food.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> splitCSVLine(const string& line) {
  vector<string> fields;
  string field;
  bool inQuotes = false;

  for (size_t i = 0; i < line.size(); ++i) {
    char ch = line[i];

    if (ch == '"') {
      inQuotes = !inQuotes;
    } else if (ch == ',' && !inQuotes) {
      fields.push_back(field);
      field.clear();
      }else{
        field += ch;
    }
  }
  fields.push_back(field);
  return fields;
}
vector<string> parseHeader(const string& line){
  return splitCSVLine(line);
}

vector<Food> parseFoods(const string& filename, vector<string>& headers) {
  vector<Food> foods;
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "File " << filename << " could not be opened" << endl;
    return foods;
  }

  string line;
  getline(file, line);
  headers = parseHeader(line);
  while (getline(file, line)) {
    auto fields = splitCSVLine(line);

    if (fields.size() != headers.size()) {
      cerr << "Warning: Skipping malformed line (field count mismatch)\n";
      continue;
    }
    Food f;
    f.category = fields[0];
    f.description = fields[1];
    int col = 0;
    for (size_t i = 3; i < fields.size(); ++i) {
      try {
        f.nutrients.push_back(stod(fields[i]));
      }catch (...) {
        f.nutrients.push_back(0.0);
      }
    }
    foods.push_back(f);
  }
  return foods;
}