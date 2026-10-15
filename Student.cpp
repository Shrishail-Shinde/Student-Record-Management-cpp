#include "Student.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
using namespace std;

Student::Student() : id(0) {
    for (int i = 0; i < NUM_SUBJECTS; i++) marks[i] = 0;
}

Student::Student(int id, const string& name, const double m[]) : id(id), name(name) {
    for (int i = 0; i < NUM_SUBJECTS; i++) marks[i] = m[i];
}

int Student::getId() const { return id; }
string Student::getName() const { return name; }
void Student::setName(const string& newName) { name = newName; }

void Student::setMarks(const double m[]) {
    for (int i = 0; i < NUM_SUBJECTS; i++) marks[i] = m[i];
}

double Student::total() const {
    double sum = 0;
    for (int i = 0; i < NUM_SUBJECTS; i++) sum += marks[i];
    return sum;
}

double Student::percentage() const { return total() / NUM_SUBJECTS; }

char Student::grade() const {
    double p = percentage();
    if (p >= 90) return 'A';
    if (p >= 75) return 'B';
    if (p >= 60) return 'C';
    if (p >= 40) return 'D';
    return 'F';
}

void Student::printHeader() {
    cout << left << setw(8) << "ID" << setw(22) << "Name";
    for (int i = 1; i <= NUM_SUBJECTS; i++)
        cout << setw(8) << ("Sub" + to_string(i));
    cout << setw(10) << "Percent" << "Grade\n";
    cout << string(62, '-') << "\n";
}

void Student::display() const {
    cout << left << setw(8) << id << setw(22) << name;
    for (int i = 0; i < NUM_SUBJECTS; i++)
        cout << setw(8) << marks[i];
    cout << setw(10) << fixed << setprecision(2) << percentage()
         << grade() << "\n";
}

string Student::toFileString() const {
    ostringstream out;
    out << id << '|' << name;
    for (int i = 0; i < NUM_SUBJECTS; i++) out << '|' << marks[i];
    return out.str();
}

Student Student::fromFileString(const string& line) {
    stringstream ss(line);
    string idStr, name, field;
    double m[NUM_SUBJECTS];

    if (!getline(ss, idStr, '|') || !getline(ss, name, '|'))
        throw runtime_error("Malformed record");
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        if (!getline(ss, field, '|')) throw runtime_error("Malformed record");
        m[i] = stod(field);   // throws if not a number
    }
    return Student(stoi(idStr), name, m);
}