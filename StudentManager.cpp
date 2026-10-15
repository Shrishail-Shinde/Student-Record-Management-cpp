#include "StudentManager.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <cctype>
#include <stdexcept>
#include <iomanip>
using namespace std;

static string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c) { return tolower(c); });
    return s;
}

int StudentManager::findIndexById(int id) const {
    for (size_t i = 0; i < students.size(); i++)
        if (students[i].getId() == id) return static_cast<int>(i);
    return -1;
}

void StudentManager::addStudent() {
    int id = readInt("Enter ID: ", 1, 999999);
    if (findIndexById(id) != -1)
        throw runtime_error("A student with this ID already exists.");

    string name;
    while (true) {
        name = readLine("Enter name: ");
        if (name.find('|') == string::npos) break;
        cout << "Name cannot contain the '|' character.\n";
    }

    double marks[NUM_SUBJECTS];
    for (int i = 0; i < NUM_SUBJECTS; i++)
        marks[i] = readDouble("Enter marks for subject " + to_string(i + 1) + " (0-100): ", 0, 100);

    students.push_back(Student(id, name, marks));
    cout << "Student added successfully!\n";
}

void StudentManager::displayAll() const {
    if (students.empty()) {
        cout << "No records found.\n";
        return;
    }
    Student::printHeader();
    for (const Student& s : students) s.display();
}

void StudentManager::searchById() const {
    int id = readInt("Enter ID to search: ", 1, 999999);
    int idx = findIndexById(id);
    if (idx == -1) {
        cout << "No student found with ID " << id << ".\n";
        return;
    }
    Student::printHeader();
    students[idx].display();
}

void StudentManager::searchByName() const {
    string query = toLower(readLine("Enter name (or part of it): "));
    bool found = false;
    for (const Student& s : students) {
        if (toLower(s.getName()).find(query) != string::npos) {
            if (!found) Student::printHeader();
            s.display();
            found = true;
        }
    }
    if (!found) cout << "No matching students found.\n";
}

void StudentManager::updateStudent() {
    int id = readInt("Enter ID of student to update: ", 1, 999999);
    int idx = findIndexById(id);
    if (idx == -1) throw runtime_error("No student found with that ID.");

    cout << "Current record:\n";
    Student::printHeader();
    students[idx].display();

    string newName;
    while (true) {
        newName = readLine("New name (press Enter to keep current): ", true);
        if (newName.find('|') == string::npos) break;
        cout << "Name cannot contain the '|' character.\n";
    }
    if (!newName.empty()) students[idx].setName(newName);

    double marks[NUM_SUBJECTS];
    for (int i = 0; i < NUM_SUBJECTS; i++)
        marks[i] = readDouble("New marks for subject " + to_string(i + 1) + " (0-100): ", 0, 100);
    students[idx].setMarks(marks);

    cout << "Record updated.\n";
}

void StudentManager::deleteStudent() {
    int id = readInt("Enter ID of student to delete: ", 1, 999999);
    int idx = findIndexById(id);
    if (idx == -1) throw runtime_error("No student found with that ID.");

    string confirm = readLine("Delete " + students[idx].getName() + "? (y/n): ");
    if (tolower(confirm[0]) == 'y') {
        students.erase(students.begin() + idx);
        cout << "Record deleted.\n";
    } else {
        cout << "Deletion cancelled.\n";
    }
}

void StudentManager::sortStudents() {
    if (students.empty()) {
        cout << "No records to sort.\n";
        return;
    }
    cout << "Sort by:\n1. ID\n2. Name (A-Z)\n3. Percentage (highest first)\n";
    int opt = readInt("Choice: ", 1, 3);

    if (opt == 1) {
        sort(students.begin(), students.end(),
             [](const Student& a, const Student& b) { return a.getId() < b.getId(); });
    } else if (opt == 2) {
        sort(students.begin(), students.end(),
             [](const Student& a, const Student& b) {
                 return toLower(a.getName()) < toLower(b.getName());
             });
    } else {
        sort(students.begin(), students.end(),
             [](const Student& a, const Student& b) { return a.percentage() > b.percentage(); });
    }
    displayAll();
}

void StudentManager::showStatistics() const {
    if (students.empty()) {
        cout << "No records to analyse.\n";
        return;
    }
    auto cmp = [](const Student& a, const Student& b) { return a.percentage() < b.percentage(); };
    const Student& topper = *max_element(students.begin(), students.end(), cmp);
    const Student& lowest = *min_element(students.begin(), students.end(), cmp);

    double sum = 0;
    map<char, int> gradeCount;
    for (const Student& s : students) {
        sum += s.percentage();
        gradeCount[s.grade()]++;
    }

    cout << fixed << setprecision(2);
    cout << "Total students : " << students.size() << "\n";
    cout << "Class average  : " << sum / students.size() << "%\n";
    cout << "Topper         : " << topper.getName() << " (" << topper.percentage() << "%)\n";
    cout << "Lowest         : " << lowest.getName() << " (" << lowest.percentage() << "%)\n";
    cout << "Grade distribution:\n";
    for (map<char, int>::const_iterator it = gradeCount.begin(); it != gradeCount.end(); ++it)
        cout << "  " << it->first << " : " << it->second << "\n";
}

void StudentManager::saveToFile(const string& filename) const {
    ofstream out(filename);
    if (!out) throw runtime_error("Could not open " + filename + " for writing.");
    for (const Student& s : students) out << s.toFileString() << "\n";
}

void StudentManager::loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in) return;   // first run: no file yet, that's fine

    students.clear();
    string line;
    int lineNo = 0;
    while (getline(in, line)) {
        lineNo++;
        if (line.empty()) continue;
        try {
            students.push_back(Student::fromFileString(line));
        } catch (const exception&) {
            cout << "Warning: skipped corrupted record on line " << lineNo << ".\n";
        }
    }
    cout << students.size() << " record(s) loaded from " << filename << ".\n";
}