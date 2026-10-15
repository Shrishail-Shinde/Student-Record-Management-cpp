#pragma once
#include <string>

const int NUM_SUBJECTS = 3;

class Student {
private:
    int id;
    std::string name;
    double marks[NUM_SUBJECTS];

public:
    Student();
    Student(int id, const std::string& name, const double m[]);

    int getId() const;
    std::string getName() const;
    void setName(const std::string& newName);
    void setMarks(const double m[]);

    double total() const;
    double percentage() const;
    char grade() const;

    void display() const;
    static void printHeader();

    std::string toFileString() const;                      // id|name|m1|m2|m3
    static Student fromFileString(const std::string& line);
};