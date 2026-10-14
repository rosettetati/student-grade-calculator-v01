#include <iostream>
#include <fstream>
#include <sstream>
#include <deque> // Change to <vector> or <list> as needed for testing
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <stdexcept>
#include "Person.h"
#include "FileGenerator.h"

int main() {
    try {
        std::string filename = "students10000.txt"; // Test with 10k, 100k, 1M, etc.
        std::cout << "\n--- Container Performance Analysis (v0.25) --- \n";
        std::cout << "Processing file: " << filename << " using std::deque\n";

        auto startTotal = std::chrono::high_resolution_clock::now();

        // 1. Read from file
        auto startRead = std::chrono::high_resolution_clock::now();
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Error: Could not open file " + filename);
        }

        std::deque<Person> students;
        std::string line;
        std::getline(file, line); // Skip header

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
                students.emplace_back(name, surname, tempValues, exam);
            }
        }
        file.close();
        auto endRead = std::chrono::high_resolution_clock::now();

        // 2. Sort students (Note: if using std::list, use students.sort() instead of std::sort)
        auto startSort = std::chrono::high_resolution_clock::now();
        std::sort(students.begin(), students.end(), [](const Person& a, const Person& b) {
            return a.getFinalAvg() < b.getFinalAvg();
        });
        auto endSort = std::chrono::high_resolution_clock::now();

        // 3. Split into passed/failed categories
        auto startSplit = std::chrono::high_resolution_clock::now();
        std::deque<Person> failedStudents;
        std::deque<Person> passedStudents;

        for (const auto& student : students) {
            if (student.getFinalAvg() < 5.0) {
                failedStudents.push_back(student);
            } else {
                passedStudents.push_back(student);
            }
        }
        auto endSplit = std::chrono::high_resolution_clock::now();

        // 4. Output results to files
        auto startWrite = std::chrono::high_resolution_clock::now();
        std::ofstream failFile("failed_students.txt");
        std::ofstream passFile("passed_students.txt");

        if (!failFile.is_open() || !passFile.is_open()) {
            throw std::runtime_error("Error: Could not create output files.");
        }

        for (const auto& s : failedStudents) {
            failFile << s.getName() << " " << s.getSurname() << " " << s.getFinalAvg() << "\n";
        }
        for (const auto& s : passedStudents) {
            passFile << s.getName() << " " << s.getSurname() << " " << s.getFinalAvg() << "\n";
        }

        failFile.close();
        passFile.close();
        auto endWrite = std::chrono::high_resolution_clock::now();

        auto endTotal = std::chrono::high_resolution_clock::now();

        // Results
        std::cout << "Data Read Time:  " << std::chrono::duration<double>(endRead - startRead).count() << " seconds\n";
        std::cout << "Data Sort Time:  " << std::chrono::duration<double>(endSort - startSort).count() << " seconds\n";
        std::cout << "Data Split Time: " << std::chrono::duration<double>(endSplit - startSplit).count() << " seconds\n";
        std::cout << "Data Write Time: " << std::chrono::duration<double>(endWrite - startWrite).count() << " seconds\n";
        std::cout << "Total Execution: " << std::chrono::duration<double>(endTotal - startTotal).count() << " seconds\n";

    } catch (const std::exception& e) {
        std::cerr << "Exception Caught: " << e.what() << "\n";
        return 1;
    }

    return 0;
}