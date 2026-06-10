/*
 * Lab Booking System
 * Course: BAXU1113 Programming Technique | Sem 2, 2025/2026
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;

void clearScreen() {
    cout << "\033[2J\033[H";
}

// Clears any leftover characters from the input buffer
void flushInput() {
    cin.ignore(1000, '\n');
}

struct Booking {
    int  id;
    char name[50];
    char lab[30];
    char time[10];
    char date[12];
};

Booking bookings[100];
int totalBookings = 0;

const char* LABS[]  = {"Chemistry Lab", "Biology Lab", "Physics Lab"};
const char* TIMES[] = {"8:00 AM", "10:00 AM", "12:00 PM", "2:00 PM", "4:00 PM"};

// Shows lab options and copies the chosen lab name into dest
void pickLab(char* dest) {
    cout << "Choose a lab:\n";
    cout << "1. Chemistry Lab\n";
    cout << "2. Biology Lab\n";
    cout << "3. Physics Lab\n";
    cout << "Enter choice        : ";
    int c; cin >> c; flushInput();
    if (c < 1 || c > 3) c = 1;
    strncpy(dest, LABS[c - 1], 29);
    dest[29] = '\0';
}

// Shows time options and copies the chosen time into dest
void pickTime(char* dest) {
    cout << "Choose a time:\n";
    cout << "1. 8:00 AM\n";
    cout << "2. 10:00 AM\n";
    cout << "3. 12:00 PM\n";
    cout << "4. 2:00 PM\n";
    cout << "5. 4:00 PM\n";
    cout << "Enter choice        : ";
    int c; cin >> c; flushInput();
    if (c < 1 || c > 5) c = 1;
    strncpy(dest, TIMES[c - 1], 9);
    dest[9] = '\0';
}

// Saves all bookings to bookings.txt (overwrites each time)
void saveToFile() {
    ofstream file("bookings.txt");
    for (int i = 0; i < totalBookings; i++) {
        file << bookings[i].id   << ","
             << bookings[i].name << ","
             << bookings[i].lab  << ","
             << bookings[i].time << ","
             << bookings[i].date << "\n";
    }
    file.close();
}

// Loads bookings from bookings.txt on program start
void loadFromFile() {
    ifstream file("bookings.txt");
    if (!file) return;
    char line[120];
    while (file.getline(line, 120) && totalBookings < 100) {
        char* t = strtok(line, ",");
        if (!t) continue;
        bookings[totalBookings].id = atoi(t);

        t = strtok(NULL, ","); if (!t) continue;
        strncpy(bookings[totalBookings].name, t, 49);
        bookings[totalBookings].name[49] = '\0';

        t = strtok(NULL, ","); if (!t) continue;
        strncpy(bookings[totalBookings].lab, t, 29);
        bookings[totalBookings].lab[29] = '\0';

        t = strtok(NULL, ","); if (!t) continue;
        strncpy(bookings[totalBookings].time, t, 9);
        bookings[totalBookings].time[9] = '\0';

        t = strtok(NULL, ","); if (!t) continue;
        strncpy(bookings[totalBookings].date, t, 11);
        bookings[totalBookings].date[11] = '\0';

        totalBookings++;
    }
    file.close();
}

// Adds a new booking and saves to file
void addBooking() {
    clearScreen();
    if (totalBookings >= 100) {
        cout << "Booking limit reached.\n";
        return;
    }

    Booking b;
    b.id = (totalBookings == 0) ? 1 : bookings[totalBookings - 1].id + 1;

    cout << "Enter your name     : ";
    cin.getline(b.name, 50);

    pickLab(b.lab);
    pickTime(b.time);

    cout << "Enter date (DD/MM/YYYY): ";
    cin.getline(b.date, 12);

    bookings[totalBookings++] = b;
    saveToFile();

    cout << "\nBooking added successfully! (auto-saved)\n";
    cout << "\nPress Enter to continue...";
    cin.get();
}

// Displays all bookings in a table
void viewBookings() {
    clearScreen();
    cout << "==============================\n";
    cout << "      ALL BOOKINGS\n";
    cout << "==============================\n";

    if (totalBookings == 0) {
        cout << "No bookings yet.\n";
    } else {
        cout << "\n";
        cout << "ID  Name                 Lab              Time       Date\n";
        cout << "--  -------------------  ---------------  ---------  ----------\n";
        for (int i = 0; i < totalBookings; i++) {
            cout.width(2);  cout << left << bookings[i].id   << "  ";
            cout.width(19); cout << left << bookings[i].name << "  ";
            cout.width(15); cout << left << bookings[i].lab  << "  ";
            cout.width(9);  cout << left << bookings[i].time << "  ";
            cout.width(10); cout << left << bookings[i].date << "\n";
        }
        cout << "\nTotal bookings: " << totalBookings << "\n";
    }

    cout << "\nPress Enter to continue...";
    cin.get();
}

// Finds a booking by ID and updates its details
void modifyBooking() {
    clearScreen();
    cout << "Enter Booking ID to modify: ";
    int id; cin >> id; flushInput();

    for (int i = 0; i < totalBookings; i++) {
        if (bookings[i].id == id) {
            cout << "\nCurrent details:\n";
            cout << "Name: "  << bookings[i].name
                 << " | Lab: "  << bookings[i].lab
                 << " | Time: " << bookings[i].time
                 << " | Date: " << bookings[i].date << "\n\n";

            cout << "Enter new name     : ";
            cin.getline(bookings[i].name, 50);

            pickLab(bookings[i].lab);
            pickTime(bookings[i].time);

            cout << "Enter new date     : ";
            cin.getline(bookings[i].date, 12);

            saveToFile();
            cout << "\nBooking updated! (auto-saved)\n";
            cout << "\nPress Enter to continue...";
            cin.get();
            return;
        }
    }

    cout << "Booking ID " << id << " not found.\n";
    cout << "\nPress Enter to continue...";
    cin.get();
}

// Finds a booking by ID and removes it
void deleteBooking() {
    clearScreen();
    cout << "Enter Booking ID to delete: ";
    int id; cin >> id; flushInput();

    for (int i = 0; i < totalBookings; i++) {
        if (bookings[i].id == id) {
            cout << "\nAre you sure? (1 = Yes, 0 = No): ";
            int confirm; cin >> confirm; flushInput();

            if (confirm == 1) {
                for (int j = i; j < totalBookings - 1; j++)
                    bookings[j] = bookings[j + 1];
                totalBookings--;
                saveToFile();
                cout << "\nBooking deleted! (auto-saved)\n";
            }

            cout << "\nPress Enter to continue...";
            cin.get();
            return;
        }
    }

    cout << "Booking ID " << id << " not found.\n";
    cout << "\nPress Enter to continue...";
    cin.get();
}

// Shows the main menu and handles user choice
void mainMenu() {
    int choice;
    do {
        clearScreen();
        cout << "==============================\n";
        cout << "    UTEM-LAB-SCHEDULER\n";
        cout << "==============================\n";
        cout << "1. Add Booking\n";
        cout << "2. View All Bookings\n";
        cout << "3. Modify Booking\n";
        cout << "4. Delete Booking\n";
        cout << "0. Exit\n";
        cout << "==============================\n";
        cout << "Enter choice: ";
        cin >> choice; flushInput();

        switch (choice) {
            case 1: addBooking();    break;
            case 2: viewBookings();  break;
            case 3: modifyBooking(); break;
            case 4: deleteBooking(); break;
            case 0: cout << "\nGoodbye!\n"; break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);
}

int main() {
    loadFromFile();
    mainMenu();
    return 0;
}