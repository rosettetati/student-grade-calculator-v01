#include <iostream>

int main() {
    double homeworkScore = 0.0;
    double examScore = 0.0;

    std::cout << "=== Student Grade Calculator v0.1 ===" << std::endl;
    
    std::cout << "Enter Homework Score: ";
    std::cin >> homeworkScore;

    std::cout << "Enter Exam Score: ";
    std::cin >> examScore;

    double finalGrade = (0.4 * homeworkScore) + (0.6 * examScore);

    std::cout << "\nFinal Grade: " << finalGrade << std::endl;

    return 0;
}