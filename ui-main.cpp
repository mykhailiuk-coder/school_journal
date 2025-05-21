#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Journal.h"
#include "Performance.h"
#include "Attendance.h"

using namespace std;

struct AttendanceRecord {
    string studentName;
    string date;
    bool isPresent;
};

int main() {
    Journal journal;
    vector<AttendanceRecord> attendanceRecords;

    cout << "Enter student name to work with: ";
    string currentStudentName;
    getline(cin, currentStudentName);
    Student currentStudent(0, currentStudentName);

    int choice;
    do {
        cout << "\n=== Journal Menu for " << currentStudentName << " ===\n";
        cout << "1. Add Attendance\n";
        cout << "2. Add Performance\n";
        cout << "3. Show Entries for " << currentStudentName << "\n";
        cout << "4. Show Attendance Summary for " << currentStudentName << "\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            int presentInput;
            cout << "Is the student present? (1 - Yes, 0 - No): ";
            cin >> presentInput;
            cin.ignore();

            string dateStr;
            cout << "Enter date (YYYY-MM-DD): ";
            getline(cin, dateStr);

            bool isPresent = (presentInput == 1);

            journal.addEntry(make_unique<Attendance>(currentStudent, isPresent));
            attendanceRecords.push_back({ currentStudentName, dateStr, isPresent });
            break;
        }
        case 2: {
            int grade;
            cout << "Enter grade: ";
            cin >> grade;
            cin.ignore();

            journal.addEntry(make_unique<Performance>(currentStudent, grade));
            break;
        }
        case 3: {
            cout << "\n--- Entries for " << currentStudentName << " ---\n";

            cout << "\nAttendance records:\n";
            for (const auto& rec : attendanceRecords) {
                if (rec.studentName == currentStudentName) {
                    cout << rec.date << ": " << (rec.isPresent ? "Present" : "Absent") << "\n";
                }
            }

            break;
        }
        case 4: {
            int presentCount = 0, absentCount = 0;
            for (const auto& rec : attendanceRecords) {
                if (rec.studentName == currentStudentName) {
                    rec.isPresent ? presentCount++ : absentCount++;
                }
            }

            cout << "\nAttendance summary for " << currentStudentName << ":\n";
            cout << "Present days: " << presentCount << "\n";
            cout << "Absent days: " << absentCount << "\n";
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
