#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <stdexcept>
#include "Person.h"
#include "FileGenerator.h"

int main() {
    try {
        // 1. Generate required test files for v0.2
        std::cout << "Generating test files...\n";
        FileGenerator::generateFile(10000);
        FileGenerator::generateFile(100000);
        FileGenerator::generateFile(1000000);
        // Note: 10,000,000 can be generated too, but let's test execution with one or more files first.

        std::string filename = "students10000.txt"; // You can change this to test other file sizes
        std::cout << "\nProcessing file: " << filename << "\n";

        auto startTotal = std::chrono::high_resolution_clock::now();

        // 2. Read from file with Exception Handling
        auto startRead = std::chrono::high_resolution_clock::now();
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Error: Could not open file " + filename);
        }

        std::vector<Person> students;
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

        // 3. Sort students by final average score
        auto startSort = std::chrono::high_resolution_clock::now();
        std::sort(students.begin(), students.end(), [](const Person& a, const Person& b) {
            return a.getFinalAvg() < b.getFinalAvg();
        });
        auto endSort = std::chrono::high_resolution_clock::now();

        // 4. Split into passed (< 5.0 vs >= 5.0)
        auto startSplit = std::chrono::high_resolution_clock::now();
        std::vector<Person> failedStudents;
        std::vector<Person> passedStudents;

        for (const auto& student : students) {
            if (student.getFinalAvg() < 5.0) {
                failedStudents.push_back(student);
            } else {
                passedStudents.push_back(student);
            }
        }
        auto endSplit = std::chrono::high_resolution_clock::now();

        // 5. Output to new files
        auto startWrite = std::chrono::high_resolution_clock::now();
        std::ofstream failFile("failed_students.txt");
        std::ofstream passFile("passed_students.txt");

        if (!failFile.is_open() || !passFile.is_open()) {
            throw std::runtime_error("Error: Could not create output files for results.");
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

        // Performance Speed Rate Analysis Report
        std::cout << "\n--- Performance Analysis for " << filename << " ---\n";
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