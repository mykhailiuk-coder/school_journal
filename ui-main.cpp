#include <iostream>
#include <string>
#include "Journal.h"
#include "Performance.h"

using namespace std;

int main() {
    Journal journal;
    int choice;

    do {
        cout << "\n=== Journal Menu ===\n";
        cout << "1. Add Attendance\n";
        cout << "2. Add Performance\n";
        cout << "3. Show All Entries\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int id;
            string name;
            int presentInput;

            cout << "Enter student ID: ";
            cin >> id;
            cin.ignore(); // для очищення буфера після cin >> int
            cout << "Enter student name: ";
            getline(cin, name);
            cout << "Is the student present? (1 - Yes, 0 - No): ";
            cin >> presentInput;

            Student student(id, name);
            bool isPresent = (presentInput == 1 ? true : false);

            journal.addEntry(make_unique<Attendance>(student, isPresent));
            break;
        }
        case 2: {
            int id, grade;
            string name;

            cout << "Enter student ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter student name: ";
            getline(cin, name);
            cout << "Enter grade: ";
            cin >> grade;

            Student student(id, name);
            journal.addEntry(make_unique<Performance>(student, grade));
            break;
        }
        case 3:
            journal.printAll();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
