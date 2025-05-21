#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
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
    vector<string> students;

    int choice = -1;
    string currentStudentName;

    while (true) {
        if (currentStudentName.empty()) {
            cout << "Enter student name to work with: ";
            getline(cin, currentStudentName);
            if (find(students.begin(), students.end(), currentStudentName) == students.end()) {
                students.push_back(currentStudentName);
            }
        }

        cout << "\n=== Journal Menu for " << currentStudentName << " ===\n";
        cout << "1. Add Attendance\n";
        cout << "2. Add Performance\n";
        cout << "3. Show All Entries\n";
        cout << "4. Switch Student\n";
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

            Student currentStudent(0, currentStudentName);
            journal.addEntry(make_unique<Attendance>(currentStudent, isPresent));
            attendanceRecords.push_back({ currentStudentName, dateStr, isPresent });
            break;
        }
        case 2: {
            int grade;
            cout << "Enter grade: ";
            cin >> grade;
            cin.ignore();

            Student currentStudent(0, currentStudentName);
            journal.addEntry(make_unique<Performance>(currentStudent, grade));
            break;
        }
        case 3: {
            cout << "\n--- All Entries for " << currentStudentName << " ---\n";

           
            cout << "Attendance:\n";
            for (const auto& rec : attendanceRecords) {
                if (rec.studentName == currentStudentName) {
                    cout << rec.date << ": " << (rec.isPresent ? "Present" : "Absent") << '\n';
                }
            }

            cout << "\nPerformance:\n";

            journal.printAll();

            break;
        }
        case 4: {
            cout << "Available students:\n";
            for (size_t i = 0; i < students.size(); ++i) {
                cout << i + 1 << ". " << students[i] << '\n';
            }
            cout << "Enter student number to switch: ";
            int num;
            cin >> num;
            cin.ignore();
            if (num >= 1 && num <= (int)students.size()) {
                currentStudentName = students[num - 1];
            }
            else {
                cout << "Invalid number\n";
            }
            break;
        }
        case 0:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice.\n";
        }
    }
}
