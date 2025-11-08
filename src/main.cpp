//
// Created by josha on 11/3/2025.
//
// All ASCII art used in this program was created using the website:
// https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type+Something+&x=none&v=4&h=4&w=80&we=false

#include "main.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "Food.cpp"
#include "quicksort.cpp"
#include "heapify.cpp"
#include "heapsort.cpp"
#include <iomanip>
#include <algorithm>

using namespace std;

static void print_Banner() {
    cout <<
    R"(
 _______  _______  _______  ______     _     _  ___   _______  _______
|       ||       ||       ||      |   | | _ | ||   | |       ||       |
|    ___||   _   ||   _   ||  _    |  | || || ||   | |  _____||    ___|
|   |___ |  | |  ||  | |  || | |   |  |       ||   | | |_____ |   |___
|    ___||  |_|  ||  |_|  || |_|   |  |       ||   | |_____  ||    ___|
|   |    |       ||       ||       |  |   _   ||   |  _____| ||   |___
|___|    |_______||_______||______|   |__| |__||___| |_______||_______|
)" << "\n";
}
static string strip_Data_Prefix(string s) {
    const string prefix = "Data.";
    if (s.rfind(prefix, 0) == 0) {
        s.erase(0, prefix.size());
    }
    return s;
}
/*static void print_In_Columns(const vector<string>& items, int cols, int colWidth) {
    if (items.empty() || cols <= 0) {
        return;
    }
    int n = (int)items.size();
    int rows = (int)ceil(n / (double)cols);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int idx = r + rows * c;
            if (idx < n) {
                string cell = to_string(idx + 1) + ". " + items[idx];
                cout << left << setw(colWidth) << cell;
            }
        }
        cout << "\n";
    }
}*/
static string nutrient_Group(const string& s) {
    if (s.rfind("Fat.", 0) == 0) {
        return "Fats";
    } else if (s.rfind("Major Minerals.", 0) == 0) {
        return "Major Minerals";
    } else if (s.rfind("Vitamins.", 0) == 0) {
        return "Vitamins";
    } else {
        return "General";
    }
}
static string strip_Group_Prefix(string s) {
    const string p1 = "Fat.";
    const string p2 = "Major Minerals.";
    const string p3 = "Vitamins.";

    if (s.rfind(p1, 0) == 0) {
        s.erase(0, p1.size());
        return s;
    } else if (s.rfind(p2, 0) == 0) {
        s.erase(0, p2.size());
        return s;
    } else if (s.rfind(p3, 0) == 0) {
        s.erase(0, p3.size());
        return s;
    } else {
        return s;
    }
}
static void print_Group_Title(const string& group) {
    if (group == "General") {
        cout <<
        R"(
   ___                       _
  / __|___ _ _  ___ _ _ __ _| |
 | (_ / -_) ' \/ -_) '_/ _` | |
  \___\___|_||_\___|_| \__,_|_|
)"<< "\n";
    } else if (group == "Fats") {
        cout <<
        R"(,------.         ,--.
|  .---',--,--.,-'  '-. ,---.
|  `--,' ,-.  |'-.  .-'(  .-'
|  |`  \ '-'  |  |  |  .-'  `)
`--'    `--`--'  `--'  `----'
)"<< "\n";
    } else if (group == "Major Minerals") {
        cout <<
        R"(
  __  __        _              __  __ _                      _
 |  \/  | __ _ (_) ___  _ __  |  \/  (_)_ __   ___ _ __ __ _| |___
 | |\/| |/ _` || |/ _ \| '__| | |\/| | | '_ \ / _ \ '__/ _` | / __|
 | |  | | (_| || | (_) | |    | |  | | | | | |  __/ | | (_| | \__ \
 |_|  |_|\__,_|/ |\___/|_|    |_|  |_|_|_| |_|\___|_|  \__,_|_|___/
             |__/
)"<< "\n";
    } else if (group == "Vitamins") {
        cout <<
        R"(
  _   ___ __             _
 | | / (_) /____ ___ _  (_)__  ___
 | |/ / / __/ _ `/  ' \/ / _ \(_-<
 |___/_/\__/\_,_/_/_/_/_/_//_/___/
)"<< "\n";
    }
}
static void print_In_Columns_With_Start(const vector<string>& items, int cols, int col_Width,int start_Number) {
    if (items.empty() || cols <= 0) return;
    int n = (int)items.size();
    int rows = (int)ceil(n / (double)cols);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int index = r + rows * c;
            if (index < n) {
                int num = start_Number + index;
                string cell = to_string(num) + ". " + items[index];
                cout << left << setw(col_Width) << cell;
            } else {
                cout << left << setw(col_Width) << "";
            }
        }
        cout << "\n";
    }
}
static void print_Ranked_Row(int rank, const string& name, double value) {
    const char* r1[5] = {
        "  _   ",
        " / |  ",
        " | |_ ",
        " |_(_)",
        "      " };
    const char* r2[5] = {
        "  ___   ",
        " |_  )  ",
        "  / / _ ",
        " /___(_)",
        "        " };
    const char* r3[5] = {
        "  ____  ",
        " |__ /  ",
        "  |_ \\_ ",
        " |___(_)",
        "        " };
    const char* r4[5] = {
        "  _ _   ",
        " | | |  ",
        " |_ _| ",
        "   |_(_)",
        "        " };
    const char* r5[5] = {
        "  ___   ",
        " | __|  ",
        " |__ \\_ ",
        " |___(_)",
        "        " };
    const char** art;
    if (rank == 1) {
        art = r1;
    }
    else if (rank == 2) {
        art = r2;
    }
    else if (rank == 3) {
        art = r3;
    }
    else if (rank == 4) {
        art = r4;
    }
    else {
        art = r5;
    }
    for (int position = 0; position < 5; ++position) {
        if (position == 2) {
            cout << art[position] << "  " << name << ": ";
            if ((int)value == value) {
                cout << (int)value << "\n";
            } else {
                cout << fixed << setprecision(2) << value << "\n";
            }
        } else {
            cout << art[position] << "\n";
        }
    }
}

void printTopFoods(const vector<Food>& foods, int nutrientIdx, int topN = 5) {
  if (foods.empty()) return;
  int n = static_cast<int>(foods.size());
  int start = max(0, n - topN);
  for (int i = n-1; i >= start; --i) {
    cout << foods[i].description << ": " << foods[i].nutrients[nutrientIdx] << "\n";
  }
}

// i want to print the big EAT HEALTHY ascii at the very end
static void print_Eat_Healthy() {
    cout <<
        R"(
$$$$$$$$\           $$\           $$\   $$\                     $$\   $$\     $$\                 $$\
$$  _____|          $$ |          $$ |  $$ |                    $$ |  $$ |    $$ |                $$ |
$$ |      $$$$$$\ $$$$$$\         $$ |  $$ | $$$$$$\   $$$$$$\  $$ |$$$$$$\   $$$$$$$\  $$\   $$\ $$ |
$$$$$\    \____$$\\_$$  _|        $$$$$$$$ |$$  __$$\  \____$$\ $$ |\_$$  _|  $$  __$$\ $$ |  $$ |$$ |
$$  __|   $$$$$$$ | $$ |          $$  __$$ |$$$$$$$$ | $$$$$$$ |$$ |  $$ |    $$ |  $$ |$$ |  $$ |\__|
$$ |     $$  __$$ | $$ |$$\       $$ |  $$ |$$   ____|$$  __$$ |$$ |  $$ |$$\ $$ |  $$ |$$ |  $$ |
$$$$$$$$\\$$$$$$$ | \$$$$  |      $$ |  $$ |\$$$$$$$\ \$$$$$$$ |$$ |  \$$$$  |$$ |  $$ |\$$$$$$$ |$$\
\________|\_______|  \____/       \__|  \__| \_______| \_______|\__|   \____/ \__|  \__| \____$$ |\__|
                                                                                        $$\   $$ |
                                                                                        \$$$$$$  |
                                                                                         \______/     )";
}

int main() {
    print_Banner();

    std::vector<string> headers;
    auto foods = parseFoods("food.csv", headers);
    if (foods.empty()) {
        cerr << "Failed to load data.\n";
        return 1;
    }

    vector<string> nutrients;
    for (size_t i = 3; i < headers.size(); ++i) {
        nutrients.push_back(headers[i]);
    }
    //vector<string> nutrientDisplay;
    //for (const auto& s : nutrients) {
    //nutrientDisplay.push_back(strip_Data_Prefix(s));
    //}

    cout << "\nAvailable nutrients(" << nutrients.size() << " total):\n";
    string current_Group = "";
    vector<string> section;
    int sectionStartNumber = 1;
    for (int i = 0; i < (int)nutrients.size(); ++i) {
        string noData = strip_Data_Prefix(nutrients[i]);
        string g = nutrient_Group(noData);
        if (current_Group.empty()) {
            current_Group = g;
        }
        if (g != current_Group) {
            if (!section.empty()) {
                print_Group_Title(current_Group);
                print_In_Columns_With_Start(section, 4, 30, sectionStartNumber);
                section.clear();
            }
            current_Group = g;
            sectionStartNumber = i + 1;
        }
        section.push_back(strip_Group_Prefix(noData));
    }
    if (!section.empty()) {
        print_Group_Title(current_Group);
        print_In_Columns_With_Start(section, 4, 30, sectionStartNumber);
        section.clear();
    }
    cout << "\n";
    //for (size_t i = 0; i < nutrients.size(); ++i) {
    //cout << (i+1) << ". " << nutrients[i] << ;//
    //}

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