# Student Record Management System (C++)

A menu-driven console application for managing student records, marks and grades.
Built in C++ using OOP, STL containers, file handling and exception handling.

## Features
- Add, display, update and delete student records
- Search by ID or by name (partial, case-insensitive)
- Sort by ID, name, or percentage
- Statistics: class average, topper, lowest scorer, grade distribution
- Persistent storage: records are saved to and loaded from `students.txt`
- Input validation and exception handling for invalid input

## Concepts Used
- Classes, encapsulation and separation into header and source files
- `std::vector`, `std::map`, `std::sort` with lambdas
- File handling with `fstream`
- Exception handling with `try/catch` and `std::runtime_error`

## Project Structure
| File | Purpose |
|------|---------|
| `main.cpp` | Menu loop and program entry point |
| `Student.h / Student.cpp` | Student class: marks, grade calculation, file serialization |
| `StudentManager.h / StudentManager.cpp` | All record operations (add, search, update, delete, sort, statistics, save/load) |
| `Utils.h` | Validated input helpers |

## Build and Run
Requires a C++11 (or newer) compiler such as g++.

```
g++ -std=c++14 main.cpp Student.cpp StudentManager.cpp -o student.exe
.\student.exe
```

On Linux or macOS, run `./student` instead of `.\student.exe`.

## Grading Scale
| Percentage | Grade |
|-----------|-------|
| 90 and above | A |
| 75 - 89 | B |
| 60 - 74 | C |
| 40 - 59 | D |
| Below 40 | F |

## Sample Menu
```
===== Student Record Management System =====
1. Add student
2. Display all students
3. Search by ID
4. Search by name
5. Update student
6. Delete student
7. Sort students
8. Statistics
9. Save now
0. Save and exit
```

## Author
Shrishail Shinde