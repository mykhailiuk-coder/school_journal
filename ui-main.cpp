#include <iostream>
#include <string>
#include "Journal.h"
#include "Performance.h"

using namespace std;

int main() {
    Journal journal;
    string studentName;

    cout << "Enter student name to work with: ";
    getline(cin, studentName);
    Student currentStudent(0, studentName); // ID не використовується

    int choice;

    do {
        cout << "\n=== Journal Menu for " << currentStudent.getName() << " ===\n";
        cout << "1. Add Attendance\n";
        cout << "2. Add Performance\n";
        cout << "3. Show Entries for " << currentStudent.getName() << "\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int presentInput;
            cout << "Is the student present? (1 - Yes, 0 - No): ";
            cin >> presentInput;
            bool isPresent = (presentInput == 1 ? true : false);
            journal.addEntry(make_unique<Attendance>(currentStudent, isPresent));
            break;
        }
        case 2: {
            int grade;
            cout << "Enter grade: ";
            cin >> grade;
            journal.addEntry(make_unique<Performance>(currentStudent, grade));
            break;
        }
        case 3: {
            cout << "\n--- Entries for " << currentStudent.getName() << " ---\n";
            journal.printAll(); // Зараз виводить усе — змінемо нижче
            break;
        }
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
