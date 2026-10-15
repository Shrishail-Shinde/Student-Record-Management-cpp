#include <iostream>
#include "StudentManager.h"
#include "Utils.h"
using namespace std;

const string DATA_FILE = "students.txt";

void showMenu() {
    cout << "\n===== Student Record Management System =====\n"
         << "1. Add student\n"
         << "2. Display all students\n"
         << "3. Search by ID\n"
         << "4. Search by name\n"
         << "5. Update student\n"
         << "6. Delete student\n"
         << "7. Sort students\n"
         << "8. Statistics\n"
         << "9. Save now\n"
         << "0. Save and exit\n";
}

int main() {
    StudentManager manager;

    try {
        manager.loadFromFile(DATA_FILE);
    } catch (const exception& e) {
        cout << "Error loading data: " << e.what() << "\n";
    }

    int choice;
    do {
        showMenu();
        choice = readInt("Choice: ", 0, 9);

        try {
            switch (choice) {
                case 1: manager.addStudent(); break;
                case 2: manager.displayAll(); break;
                case 3: manager.searchById(); break;
                case 4: manager.searchByName(); break;
                case 5: manager.updateStudent(); break;
                case 6: manager.deleteStudent(); break;
                case 7: manager.sortStudents(); break;
                case 8: manager.showStatistics(); break;
                case 9: manager.saveToFile(DATA_FILE); cout << "Saved.\n"; break;
                case 0:
                    manager.saveToFile(DATA_FILE);
                    cout << "Data saved. Goodbye!\n";
                    break;
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    } while (choice != 0);

    return 0;
}

