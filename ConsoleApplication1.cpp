#include <iostream>
#include <string>
#include <vector>
using namespace std;

class student {
public:
    vector<float> grades;
    string name;

    struct date {
        int day;
        string month;
        int year;
    };

    vector<date> absences;

    student() {
        name = "John Doe";
        grades = { 4.0, 3.0, 3.0, 2.0, 4.0 };
    }

    student(string n, vector<float> g) {
        name = n;
        grades = g;
    }

    float getAverage() {
        if (grades.empty()) return 0.0;
        float sum = 0;
        for (float g : grades)
            sum += g;
        return sum / grades.size();
    }

    void getGrades() {
        cout << "Grades: ";
        for (float g : grades)
            cout << g << " ";
        cout << endl;
    }

    float getMaxGrade() {
        if (grades.empty()) return 0.0;
        float max = grades[0];
        for (size_t i = 1; i < grades.size(); i++) {
            if (grades[i] > max)
                max = grades[i];
        }
        return max;
    }

    float getMinGrade() {
        if (grades.empty()) return 0.0;
        float min = grades[0];
        for (size_t i = 1; i < grades.size(); i++) {
            if (grades[i] < min)
                min = grades[i];
        }
        return min;
    }

    void getAbsence() {
        if (absences.empty()) {
            cout << "No absences recorded." << endl;
            return;
        }
        cout << "Absences: ";
        for (const date& date : absences) {
            cout << date.day << " " << date.month << " " << date.year << "; ";
        }
        cout << endl;
    }
};

class teacher {
public:
    vector<student> students;

    void addStudent(student s) {
        students.push_back(s);
    }

    void getStudentInfo(student& s) {
        cout << "Student name: " << s.name << endl;
        s.getGrades();
        cout << "Average grade: " << s.getAverage() << endl;
        cout << "Max grade: " << s.getMaxGrade() << endl;
        cout << "Min grade: " << s.getMinGrade() << endl;
    }

    void setStudentAbsence(student& s, int d, string m, int y) {
        student::date absenceDate{ d, m, y };
        s.absences.push_back(absenceDate);
    }

    student* getStudentByName(const string& name) {
        for (auto& s : students) {
            if (s.name == name)
                return &s;
        }
        return nullptr;
    }

    void setStudentGrades(student& s, vector<float> g) {
        s.grades = g;
    }

    void addGrade(student& s, float g) {
        s.grades.push_back(g);
    }

    void getAbsence(student& s) {
        s.getAbsence();
    }

    void changeGrades(student& s, float g) {
        s.grades.push_back(g);
    }

    void addAbsence(student& s, int d, string m, int y) {
        s.absences.push_back({ d, m, y });
    }
};

int main() {
    student s;
    student s1("Maksym Lisoviy", { 5.0, 5.0, 4.0, 5.0, 4.0, 5.0 });
    teacher t;

    t.addStudent(s1);
    t.addStudent(s);

    int role;

    cout << "Possible roles:\n1. Student\n2. Teacher\n3. Exit\n" << endl;

    while (true) {
        cout << "Choose your role: ";
        cin >> role;
        cin.ignore();

        if (role == 1) {
            string fullname;
            cout << "Enter full name: ";
            getline(cin, fullname);

            student* stud = t.getStudentByName(fullname);
            if (stud != nullptr) {
                t.getStudentInfo(*stud);
                t.getAbsence(*stud);
            }
            else {
                cout << "Student not found!" << endl;
            }
        }
        else if (role == 2) {
            char choice0;
            cout << "Add new student(Y|N)?: ";
            cin >> choice0;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice0 == 'Y' || choice0 == 'y') {
                string name;
                cout << "Enter student name: ";
                getline(cin, name);

                vector<float> grades;
                cout << "Enter grades (space-separated): ";
                float grade;
                while (cin >> grade) {
                    grades.push_back(grade);
                    if (cin.peek() == '\n') break;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                t.addStudent(student(name, grades));
            }

            string fullname;
            cout << "Enter existing student`s name: ";
            getline(cin, fullname);

            student* stud = t.getStudentByName(fullname);

            if (stud != nullptr) {
                t.setStudentAbsence(*stud, 10, "April", 2025);
                t.getStudentInfo(*stud);
                t.getAbsence(*stud);

                string choice;
                cout << "Select what to change (grades|absence): ";
                cin >> choice;

                if (choice == "grades") {
                    cout << "Want to change or add grades? ";
                    string choice2;
                    cin >> choice2;

                    if (choice2 == "add") {
                        float newGrade;
                        cout << "Enter new grade: ";
                        cin >> newGrade;
                        t.addGrade(*stud, newGrade);
                    }
                    else if (choice2 == "change") {
                        cout << "Enter new grades (space-separated): ";
                        vector<float> newGrades;
                        float grade;
                        while (cin >> grade) {
                            newGrades.push_back(grade);
                            if (cin.peek() == '\n') break;
                        }
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        t.setStudentGrades(*stud, newGrades);
                    }
                }
                else if (choice == "absence") {
                    int day, year;
                    string month;
                    cout << "Enter absence date (day): ";
                    cin >> day;
                    cout << "Enter absence date (month): ";
                    cin >> month;
                    cout << "Enter absence date (year): ";
                    cin >> year;

                    t.addAbsence(*stud, day, month, year);
                }
            }
            else {
                cout << "Student not found!" << endl;
            }
        }

        else if (role == 3) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid role. Please try again." << endl;
        }

        cout << endl;
    }
    return 0;
}