/*
 * SciLab Manager v1.0
 * Science/Chemistry Lab Management System
 * Course: BAXU1113 Programming Technique | Sem 2, 2025/2026
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

// ─── Data Structures ─────────────────────────────────────────────────────────

struct Student {
    int id;
    char name[50];
    char course[30];
};

struct Equipment {
    int id;
    char name[50];
    int quantity;
};

struct Booking {
    int bookingId;
    int studentId;
    int equipmentId;
    char date[12]; // DD/MM/YYYY
};

// ─── Global Arrays ───────────────────────────────────────────────────────────

Student   students[50];
Equipment equipment[30];
Booking   bookings[100];

int studentCount   = 0;
int equipmentCount = 0;
int bookingCount   = 0;

// ─── Forward Declarations ────────────────────────────────────────────────────

void mainMenu();
void studentMenu();
void equipmentMenu();
void bookingMenu();

void addStudent();
void viewStudents();
void searchStudent(int id);

void addEquipment();
void viewEquipment();
void updateQuantity(int id);

void addBooking();
void viewBookings();
void saveBookingsToFile();
void loadBookingsFromFile();
void saveStudentsToFile();
void loadStudentsFromFile();

void viewSummary();
void pauseScreen();
void printHeader(const char* title);

// ─── Utility ─────────────────────────────────────────────────────────────────

// Clears the console screen (Windows-compatible for UTeM labs)
void clearScreen() {
    system("cls");
}

// Pauses and waits for any key before returning to menu
void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// Prints a consistent section header
void printHeader(const char* title) {
    cout << "\n=========================================\n";
    cout << "  " << title << "\n";
    cout << "=========================================\n";
}

// ─── File I/O ────────────────────────────────────────────────────────────────

// Saves all bookings to bookings.txt in CSV format
void saveBookingsToFile() {
    ofstream file("bookings.txt");
    if (!file) {
        cout << "Error: Could not open bookings.txt for writing.\n";
        return;
    }
    for (int i = 0; i < bookingCount; i++) {
        file << bookings[i].bookingId << ","
             << bookings[i].studentId << ","
             << bookings[i].equipmentId << ","
             << bookings[i].date << "\n";
    }
    file.close();
}

// Loads bookings from bookings.txt on program start
void loadBookingsFromFile() {
    ifstream file("bookings.txt");
    if (!file) return; // file may not exist yet

    bookingCount = 0;
    char line[100];
    while (file.getline(line, 100) && bookingCount < 100) {
        // Parse CSV line: bookingId,studentId,equipmentId,date
        int bId, sId, eId;
        char date[12];

        if (sscanf(line, "%d,%d,%d,%11s", &bId, &sId, &eId, date) == 4) {
            bookings[bookingCount].bookingId   = bId;
            bookings[bookingCount].studentId   = sId;
            bookings[bookingCount].equipmentId = eId;
            strncpy(bookings[bookingCount].date, date, 11);
            bookings[bookingCount].date[11] = '\0';
            bookingCount++;
        }
    }
    file.close();
}

// Saves all students to students.txt in CSV format
void saveStudentsToFile() {
    ofstream file("students.txt");
    if (!file) {
        cout << "Error: Could not open students.txt for writing.\n";
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        file << students[i].id << ","
             << students[i].name << ","
             << students[i].course << "\n";
    }
    file.close();
}

// Loads students from students.txt on program start
void loadStudentsFromFile() {
    ifstream file("students.txt");
    if (!file) return;

    studentCount = 0;
    char line[100];
    while (file.getline(line, 100) && studentCount < 50) {
        int id;
        char name[50], course[30];
        // Find first comma
        char* p1 = strchr(line, ',');
        if (!p1) continue;
        *p1 = '\0';
        id = atoi(line);

        // Find second comma
        char* p2 = strchr(p1 + 1, ',');
        if (!p2) continue;
        *p2 = '\0';
        strncpy(name, p1 + 1, 49);
        name[49] = '\0';
        strncpy(course, p2 + 1, 29);
        course[29] = '\0';

        students[studentCount].id = id;
        strncpy(students[studentCount].name, name, 49);
        students[studentCount].name[49] = '\0';
        strncpy(students[studentCount].course, course, 29);
        students[studentCount].course[29] = '\0';
        studentCount++;
    }
    file.close();
}

// ─── Student Module ───────────────────────────────────────────────────────────

// Adds a new student record to the students array
void addStudent() {
    clearScreen();
    printHeader("ADD STUDENT");

    if (studentCount >= 50) {
        cout << "Maximum student limit (50) reached.\n";
        pauseScreen();
        return;
    }

    Student s;
    cout << "Enter Student ID   : ";
    cin >> s.id;
    cin.ignore();

    // Check for duplicate ID
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == s.id) {
            cout << "Error: Student ID " << s.id << " already exists.\n";
            pauseScreen();
            return;
        }
    }

    cout << "Enter Student Name : ";
    cin.getline(s.name, 50);
    if (strlen(s.name) == 0) {
        cout << "Error: Name cannot be empty.\n";
        pauseScreen();
        return;
    }

    cout << "Enter Course       : ";
    cin.getline(s.course, 30);
    if (strlen(s.course) == 0) {
        cout << "Error: Course cannot be empty.\n";
        pauseScreen();
        return;
    }

    students[studentCount] = s;
    studentCount++;
    saveStudentsToFile();

    cout << "\nStudent added successfully!\n";
    pauseScreen();
}

// Displays all registered students in a table
void viewStudents() {
    clearScreen();
    printHeader("STUDENT LIST");

    if (studentCount == 0) {
        cout << "No students registered yet.\n";
        pauseScreen();
        return;
    }

    cout << "\n";
    cout << "ID     Name                               Course\n";
    cout << "-----  ---------------------------------  ----------------------------\n";

    for (int i = 0; i < studentCount; i++) {
        cout.width(5);  cout << left << students[i].id << "  ";
        cout.width(33); cout << left << students[i].name << "  ";
        cout.width(28); cout << left << students[i].course << "\n";
    }

    cout << "\nTotal Students: " << studentCount << "\n";
    pauseScreen();
}

// Searches for a student by their ID
void searchStudent(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            cout << "\nStudent Found:\n";
            cout << "  ID     : " << students[i].id << "\n";
            cout << "  Name   : " << students[i].name << "\n";
            cout << "  Course : " << students[i].course << "\n";
            return;
        }
    }
    cout << "\nStudent with ID " << id << " not found.\n";
}

// Student sub-menu
void studentMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\n=========================================\n";
        cout << "       STUDENT MANAGEMENT\n";
        cout << "=========================================\n";
        cout << "1. Add New Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "0. Back to Main Menu\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3: {
                int sid;
                clearScreen();
                printHeader("SEARCH STUDENT");
                cout << "Enter Student ID to search: ";
                cin >> sid;
                searchStudent(sid);
                pauseScreen();
                break;
            }
            case 0:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                pauseScreen();
        }
    } while (choice != 0);
}

// ─── Equipment Module ─────────────────────────────────────────────────────────

// Adds a new equipment record to the equipment array
void addEquipment() {
    clearScreen();
    printHeader("ADD EQUIPMENT");

    if (equipmentCount >= 30) {
        cout << "Maximum equipment limit (30) reached.\n";
        pauseScreen();
        return;
    }

    Equipment e;
    cout << "Enter Equipment ID   : ";
    cin >> e.id;
    cin.ignore();

    // Check for duplicate ID
    for (int i = 0; i < equipmentCount; i++) {
        if (equipment[i].id == e.id) {
            cout << "Error: Equipment ID " << e.id << " already exists.\n";
            pauseScreen();
            return;
        }
    }

    cout << "Enter Equipment Name : ";
    cin.getline(e.name, 50);
    if (strlen(e.name) == 0) {
        cout << "Error: Name cannot be empty.\n";
        pauseScreen();
        return;
    }

    cout << "Enter Quantity       : ";
    cin >> e.quantity;
    if (e.quantity < 0) {
        cout << "Error: Quantity cannot be negative.\n";
        pauseScreen();
        return;
    }

    equipment[equipmentCount] = e;
    equipmentCount++;

    cout << "\nEquipment added successfully!\n";
    pauseScreen();
}

// Displays all equipment in a table
void viewEquipment() {
    clearScreen();
    printHeader("EQUIPMENT LIST");

    if (equipmentCount == 0) {
        cout << "No equipment records yet.\n";
        pauseScreen();
        return;
    }

    cout << "\n";
    cout << "ID     Name                               Quantity\n";
    cout << "-----  ---------------------------------  --------\n";

    for (int i = 0; i < equipmentCount; i++) {
        cout.width(5);  cout << left << equipment[i].id << "  ";
        cout.width(33); cout << left << equipment[i].name << "  ";
        cout.width(8);  cout << left << equipment[i].quantity << "\n";
    }

    cout << "\nTotal Equipment Types: " << equipmentCount << "\n";
    pauseScreen();
}

// Updates the quantity of an equipment item by ID
void updateQuantity(int id) {
    for (int i = 0; i < equipmentCount; i++) {
        if (equipment[i].id == id) {
            cout << "Current quantity for '" << equipment[i].name
                 << "': " << equipment[i].quantity << "\n";
            cout << "Enter new quantity: ";
            int q;
            cin >> q;
            if (q < 0) {
                cout << "Error: Quantity cannot be negative.\n";
            } else {
                equipment[i].quantity = q;
                cout << "Quantity updated successfully!\n";
            }
            return;
        }
    }
    cout << "Equipment with ID " << id << " not found.\n";
}

// Equipment sub-menu
void equipmentMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\n=========================================\n";
        cout << "       EQUIPMENT INVENTORY\n";
        cout << "=========================================\n";
        cout << "1. Add New Equipment\n";
        cout << "2. View All Equipment\n";
        cout << "3. Update Equipment Quantity\n";
        cout << "0. Back to Main Menu\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEquipment();
                break;
            case 2:
                viewEquipment();
                break;
            case 3: {
                int eid;
                clearScreen();
                printHeader("UPDATE EQUIPMENT QUANTITY");
                cout << "Enter Equipment ID to update: ";
                cin >> eid;
                updateQuantity(eid);
                pauseScreen();
                break;
            }
            case 0:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                pauseScreen();
        }
    } while (choice != 0);
}

// ─── Booking Module ───────────────────────────────────────────────────────────

// Adds a new equipment booking
void addBooking() {
    clearScreen();
    printHeader("ADD BOOKING");

    if (bookingCount >= 100) {
        cout << "Maximum booking limit (100) reached.\n";
        pauseScreen();
        return;
    }

    if (studentCount == 0) {
        cout << "No students registered. Please add students first.\n";
        pauseScreen();
        return;
    }

    if (equipmentCount == 0) {
        cout << "No equipment available. Please add equipment first.\n";
        pauseScreen();
        return;
    }

    Booking b;
    b.bookingId = bookingCount + 1;

    // Validate student ID
    int sId;
    cout << "Enter Student ID    : ";
    cin >> sId;
    bool studentFound = false;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == sId) { studentFound = true; break; }
    }
    if (!studentFound) {
        cout << "Error: Student ID " << sId << " not found.\n";
        pauseScreen();
        return;
    }
    b.studentId = sId;

    // Validate equipment ID
    int eId;
    cout << "Enter Equipment ID  : ";
    cin >> eId;
    int eIdx = -1;
    for (int i = 0; i < equipmentCount; i++) {
        if (equipment[i].id == eId) { eIdx = i; break; }
    }
    if (eIdx == -1) {
        cout << "Error: Equipment ID " << eId << " not found.\n";
        pauseScreen();
        return;
    }
    if (equipment[eIdx].quantity <= 0) {
        cout << "Error: Equipment '" << equipment[eIdx].name
             << "' is out of stock.\n";
        pauseScreen();
        return;
    }
    b.equipmentId = eId;

    cin.ignore();
    cout << "Enter Date (DD/MM/YYYY): ";
    cin.getline(b.date, 12);
    if (strlen(b.date) == 0) {
        cout << "Error: Date cannot be empty.\n";
        pauseScreen();
        return;
    }

    // Reduce equipment quantity by 1
    equipment[eIdx].quantity--;

    bookings[bookingCount] = b;
    bookingCount++;
    saveBookingsToFile();

    cout << "\nBooking #" << b.bookingId << " added successfully!\n";
    pauseScreen();
}

// Displays all bookings in a table
void viewBookings() {
    clearScreen();
    printHeader("BOOKING LIST");

    if (bookingCount == 0) {
        cout << "No bookings made yet.\n";
        pauseScreen();
        return;
    }

    cout << "\n";
    cout << "Book#  Student ID  Equipment ID  Date\n";
    cout << "-----  ----------  ------------  ----------\n";

    for (int i = 0; i < bookingCount; i++) {
        cout.width(5);  cout << left << bookings[i].bookingId   << "  ";
        cout.width(10); cout << left << bookings[i].studentId   << "  ";
        cout.width(12); cout << left << bookings[i].equipmentId << "  ";
        cout.width(10); cout << left << bookings[i].date        << "\n";
    }

    cout << "\nTotal Bookings: " << bookingCount << "\n";
    pauseScreen();
}

// Booking sub-menu
void bookingMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\n=========================================\n";
        cout << "       EQUIPMENT BOOKING\n";
        cout << "=========================================\n";
        cout << "1. Make New Booking\n";
        cout << "2. View All Bookings\n";
        cout << "0. Back to Main Menu\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBooking();
                break;
            case 2:
                viewBookings();
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                pauseScreen();
        }
    } while (choice != 0);
}

// ─── Summary Report ───────────────────────────────────────────────────────────

// Displays a summary of all records in the system
void viewSummary() {
    clearScreen();
    printHeader("SUMMARY REPORT");

    cout << "\n";
    cout << "Total Students Registered : " << studentCount   << "\n";
    cout << "Total Equipment Types     : " << equipmentCount << "\n";
    cout << "Total Bookings Made       : " << bookingCount   << "\n";

    pauseScreen();
}

// ─── Main Menu ────────────────────────────────────────────────────────────────

// Main application loop with do-while and switch
void mainMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\n=========================================\n";
        cout << "          SCILAB MANAGER v1.0\n";
        cout << "  Science/Chemistry Lab Management System\n";
        cout << "=========================================\n";
        cout << "1. Student Management\n";
        cout << "2. Equipment Inventory\n";
        cout << "3. Equipment Booking\n";
        cout << "4. View Summary Report\n";
        cout << "0. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: studentMenu();   break;
            case 2: equipmentMenu(); break;
            case 3: bookingMenu();   break;
            case 4: viewSummary();   break;
            case 0:
                cout << "\nSaving data...\n";
                saveBookingsToFile();
                saveStudentsToFile();
                cout << "Thank you for using SciLab Manager. Goodbye!\n\n";
                break;
            default:
                cout << "Invalid choice. Please enter 0-4.\n";
                pauseScreen();
        }
    } while (choice != 0);
}

// ─── Entry Point ──────────────────────────────────────────────────────────────

int main() {
    // Load persisted data on startup
    loadStudentsFromFile();
    loadBookingsFromFile();

    mainMenu();
    return 0;
}
