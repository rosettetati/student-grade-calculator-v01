#include "Person.h"
#include <numeric>
#include <algorithm>
#include <iomanip>

Person::Person() : exam(0), finalAvg(0.0), finalMed(0.0) {}

Person::Person(std::string n, std::string s, std::vector<int> hw, int ex)
    : name(n), surname(s), homeworks(hw), exam(ex) {
    calculateGrades();
}

// Copy Constructor
Person::Person(const Person& other)
    : name(other.name), surname(other.surname), homeworks(other.homeworks),
      exam(other.exam), finalAvg(other.finalAvg), finalMed(other.finalMed) {}

// Copy Assignment Operator
Person& Person::operator=(const Person& other) {
    if (this != &other) {
        name = other.name;
        surname = other.surname;
        homeworks = other.homeworks;
        exam = other.exam;
        finalAvg = other.finalAvg;
        finalMed = other.finalMed;
    }
    return *this;
}

// Destructor
Person::~Person() {}

void Person::calculateGrades() {
    if (homeworks.empty()) {
        finalAvg = 0.6 * exam;
        finalMed = 0.6 * exam;
        return;
    }

    // Average calculation
    double sum = std::accumulate(homeworks.begin(), homeworks.end(), 0.0);
    double hwAvg = sum / homeworks.size();
    finalAvg = (0.4 * hwAvg) + (0.6 * exam);

    // Median calculation
    std::vector<int> tempHw = homeworks;
    std::sort(tempHw.begin(), tempHw.end());
    double hwMed = 0.0;
    size_t size = tempHw.size();
    if (size % 2 == 0) {
        hwMed = (tempHw[size / 2 - 1] + tempHw[size / 2]) / 2.0;
    } else {
        hwMed = tempHw[size / 2];
    }
    finalMed = (0.4 * hwMed) + (0.6 * exam);
}

std::string Person::getName() const { return name; }
std::string Person::getSurname() const { return surname; }
double Person::getFinalAvg() const { return finalAvg; }
double Person::getFinalMed() const { return finalMed; }

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << std::left << std::setw(10) << p.name 
       << std::setw(12) << p.surname 
       << std::right << std::setw(15) << std::fixed << std::setprecision(2) << p.finalAvg 
       << " | " << std::setw(12) << std::setprecision(2) << p.finalMed;
    return os;
}