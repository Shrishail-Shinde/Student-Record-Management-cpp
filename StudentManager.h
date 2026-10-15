#pragma once
#include <vector>
#include <string>
#include "Student.h"

class StudentManager {
private:
    std::vector<Student> students;
    int findIndexById(int id) const;

public:
    void addStudent();
    void displayAll() const;
    void searchById() const;
    void searchByName() const;
    void updateStudent();
    void deleteStudent();
    void sortStudents();
    void showStatistics() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};