#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>
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
    bool hasPerformance = false;

    vector<pair<string, int>> performanceRecords;

    while (true) {
        if (currentStudentName.empty()) {
            cout << "Enter student name to work with: ";
            getline(cin, currentStudentName);
            if (find(students.begin(), students.end(), currentStudentName) == students.end()) {
                students.push_back(currentStudentName);
            }
            hasPerformance = false;
        }

        cout << "\n=== Journal Menu for " << currentStudentName << " ===\n";
        cout << "1. Add Attendance\n";
        cout << "2. Add Performance (multiple grades allowed)\n";
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
            cout << "Enter date (DD-MM-YYYY): ";
            getline(cin, dateStr);

            bool isPresent = (presentInput == 1);

            Student currentStudent(0, currentStudentName);
            journal.addEntry(make_unique<Attendance>(currentStudent, isPresent));
            attendanceRecords.push_back({ currentStudentName, dateStr, isPresent });
            break;
        }
        case 2: {
            cout << "Enter grades separated by spaces: ";
            string line;
            getline(cin, line);
            istringstream iss(line);
            int grade;
            Student currentStudent(0, currentStudentName);
            bool added = false;
            while (iss >> grade) {
                journal.addEntry(make_unique<Performance>(currentStudent, grade));
                performanceRecords.push_back({ currentStudentName, grade });
                added = true;
            }
            if (added) {
                hasPerformance = true;
            }
            break;
        }
        case 3: {
            cout << "\n--- All Entries for " << currentStudentName << " ---\n";

            cout << "Attendance:\n";
            vector<string> presentDates;
            vector<string> absentDates;
            for (const auto& rec : attendanceRecords) {
                if (rec.studentName == currentStudentName) {
                    (rec.isPresent ? presentDates : absentDates).push_back(rec.date);
                }
            }

            cout << "Absent:\n";
            if (absentDates.empty()) {
                cout << "-\n";
            }
            else {
                for (const auto& date : absentDates) {
                    cout << date << '\n';
                }
            }

            cout << "Present:\n";
            if (presentDates.empty()) {
                cout << "-\n";
            }
            else {
                for (const auto& date : presentDates) {
                    cout << date << '\n';
                }
            }

            cout << "\nPerformance:\n";
            bool foundGrades = false;
            for (const auto& p : performanceRecords) {
                if (p.first == currentStudentName) {
                    if (foundGrades) cout << ' ';
                    cout << p.second;
                    foundGrades = true;
                }
            }
            cout << "\nAverage grade:";
			if (foundGrades) {
				double sum = 0;
				for (const auto& p : performanceRecords) {
					if (p.first == currentStudentName) {
						sum += p.second;
					}
				}
				cout << " " << sum / count_if(performanceRecords.begin(), performanceRecords.end(),
					[&currentStudentName](const pair<string, int>& p) { return p.first == currentStudentName; });
			}
			else {
				cout << " -";
			}
            if (!foundGrades) {
                cout << "-";
            }
            cout << '\n';

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
                hasPerformance = false;
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
