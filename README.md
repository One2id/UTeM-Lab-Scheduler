# SciLab Manager v1.0

A console-based C++ application for managing a Science/Chemistry lab — built as a course project for **BAXU1113 Programming Technique** at UTeM.

---

## Features

| Module | Operations |
|---|---|
| **Student Management** | Add student, view all students, search by ID |
| **Equipment Inventory** | Add equipment, view all equipment, update quantity |
| **Equipment Booking** | Book equipment, view all bookings, auto-save to file |
| **Summary Report** | Total counts for students, equipment, and bookings |

---

## Getting Started

### Requirements
- A C++ compiler (g++, MinGW, or MSVC)
- Windows (uses `system("cls")` for screen clearing)

### Compile & Run

```bash
g++ -o SciLabManager main.cpp
./SciLabManager
```

On Windows (MinGW):
```bash
g++ -o SciLabManager.exe main.cpp
SciLabManager.exe
```

---

## Project Structure

```
scilab-manager/
├── main.cpp          # Entire source code (single file)
├── bookings.txt      # Auto-generated at runtime
└── students.txt      # Auto-generated at runtime
```

Data files are created automatically on first run and persist across sessions.

---

## Data Structures

```cpp
struct Student   { int id; char name[50]; char course[30]; };
struct Equipment { int id; char name[50]; int quantity; };
struct Booking   { int bookingId; int studentId; int equipmentId; char date[12]; };
```

Limits: 50 students · 30 equipment types · 100 bookings

---

## Sample Screens

### Main Menu
```
=========================================
          SCILAB MANAGER v1.0
  Science/Chemistry Lab Management System
=========================================
1. Student Management
2. Equipment Inventory
3. Equipment Booking
4. View Summary Report
0. Exit

Enter your choice: _
```

### Summary Report
```
=========================================
  SUMMARY REPORT
=========================================

Total Students Registered : 5
Total Equipment Types     : 3
Total Bookings Made       : 7
```

---

## Technical Highlights

- **Selection** — `if/else` for input validation; `switch` for all menu choices
- **Repetition** — `do-while` for every menu loop; `for` to display records
- **Functions** — one function per feature (`addStudent`, `viewEquipment`, etc.)
- **Arrays** — global arrays of structs for all data
- **File I/O** — CSV-format `.txt` files, loaded on startup and saved on changes
- **Structs** — `Student`, `Equipment`, `Booking`

---

## Course Info

- **Course:** BAXU1113 Programming Technique — Sem 2, 2025/2026
- **Institution:** UTeM
- **Deliverable:** 20% project
