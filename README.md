# Lab Booking System

A simple console-based C++ program for booking science labs at a university.
Built for **BAXU1113 Programming Technique** | Sem 2, 2025/2026.

---

## What It Does

| Option | Description |
|---|---|
| Add Booking | Enter your name, pick a lab, pick a time, enter a date |
| View All Bookings | See all bookings in a table |
| Modify Booking | Find a booking by ID and update its details |
| Delete Booking | Find a booking by ID and remove it |

Bookings are saved to `bookings.txt` automatically after every change and loaded back when the program starts.

---

## Getting Started

### Compile & Run

```bash
g++ -o LabBooking lab_booking.cpp
./LabBooking
```

On Windows (MinGW):
```bash
g++ -o LabBooking.exe lab_booking.cpp
LabBooking.exe
```

---

## Project Structure

```
scilab-manager/
├── lab_booking.cpp   # Entire source code (single file)
└── bookings.txt      # Auto-generated at runtime
```

---

## Available Labs

```
1. Chemistry Lab
2. Biology Lab
3. Physics Lab
```

## Available Times

```
1. 8:00 AM
2. 10:00 AM
3. 12:00 PM
4. 2:00 PM
5. 4:00 PM
```

---

## Sample Screens

### Main Menu
```
==============================
    LAB BOOKING SYSTEM
==============================
1. Add Booking
2. View All Bookings
3. Modify Booking
4. Delete Booking
0. Exit
==============================
Enter choice: _
```

### View All Bookings
```
ID  Name                 Lab              Time       Date
--  -------------------  ---------------  ---------  ----------
1   Ali                  Chemistry Lab    10:00 AM   15/06/2026
2   Sara                 Biology Lab      8:00 AM    16/06/2026

Total bookings: 2
```

---

## Data Structure

```cpp
struct Booking {
    int  id;
    char name[50];
    char lab[30];
    char time[10];
    char date[12];
};
```

Max: 100 bookings stored in a global array.

---

## Course Info

- **Course:** BAXU1113 Programming Technique — Sem 2, 2025/2026
- **Institution:** UTeM
