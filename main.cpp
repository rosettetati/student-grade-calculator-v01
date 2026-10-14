#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Person.h"

int main() {
    std::vector<Person> students;
    std::ifstream file("Students.txt");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open Students.txt\n";
        return 1;
    }

    std::string line;
    // Skip header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, surname;
        if (!(ss >> name >> surname)) continue;

        int grade;
        std::vector<int> tempValues;
        while (ss >> grade) {
            tempValues.push_back(grade);
        }

        if (!tempValues.empty()) {
            int exam = tempValues.back();
            tempValues.pop_back();
            std::vector<int> hwGrades = tempValues;

            students.emplace_back(name, surname, hwGrades, exam);
        }
    }
    file.close();

    // Sort students by name alphabetically
    std::sort(students.begin(), students.end(), [](const Person& a, const Person& b) {
        return a.getName() < b.getName();
    });

    // Display formatted output
    std::cout << std::left << std::setw(10) << "Name" 
              << std::setw(12) << "Surname" 
              << std::right << std::setw(15) << "Final (Avg.)" 
              << " | " << std::setw(12) << "Final (Med.)\n";
    std::cout << "----------------------------------------------------\n";

    for (const auto& student : students) {
        std::cout << student << "\n";
    }

    return 0;
}