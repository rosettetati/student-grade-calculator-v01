#ifndef FILE_GENERATOR_H
#define FILE_GENERATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

class FileGenerator {
public:
    static void generateFile(int recordCount) {
        std::string filename = "students" + std::to_string(recordCount) + ".txt";
        std::ofstream outfile(filename);

        if (!outfile.is_open()) {
            throw std::runtime_error("Error: Could not create file " + filename);
        }

        // Write header
        outfile << "Name Surname HW1 HW2 HW3 HW4 HW5 Exam\n";

        // Generate records
        for (int i = 1; i <= recordCount; ++i) {
            outfile << "Name" << i << " Surname" << i 
                    << " " << (rand() % 10 + 1)
                    << " " << (rand() % 10 + 1)
                    << " " << (rand() % 10 + 1)
                    << " " << (rand() % 10 + 1)
                    << " " << (rand() % 10 + 1)
                    << " " << (rand() % 10 + 1) << "\n";
        }

        outfile.close();
        std::cout << "Successfully generated: " << filename << "\n";
    }
};

#endif