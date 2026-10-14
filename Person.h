#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <iostream>

class Person {
private:
    std::string name;
    std::string surname;
    std::vector<int> homeworks;
    int exam;
    double finalAvg;
    double finalMed;

public:
    // Constructors & Destructor (Rule of Three)
    Person();
    Person(std::string n, std::string s, std::vector<int> hw, int ex);
    Person(const Person& other);            // Copy Constructor
    Person& operator=(const Person& other); // Copy Assignment Operator
    ~Person();                              // Destructor

    // Calculation Method
    void calculateGrades();

    // Getters
    std::string getName() const;
    std::string getSurname() const;
    double getFinalAvg() const;
    double getFinalMed() const;

    // Friend stream operators for I/O
    friend std::ostream& operator<<(std::ostream& os, const Person& p);
};

#endif