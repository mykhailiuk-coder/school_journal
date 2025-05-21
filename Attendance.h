//Attendance.h
#pragma once
#include "JournalEntry.h"

using namespace std;

class Attendance : public JournalEntry {
    bool isPresent;
public:
    Attendance(const Student& student, bool isPresent) : JournalEntry(student), isPresent(isPresent) {}
    string getInfo() const override { return student.getName() + ": " + (isPresent ? "Present" : "Absent"); }
};