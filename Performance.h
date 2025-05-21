//Performance.h
#pragma once
#include "JournalEntry.h"

using namespace std;

class Performance : public JournalEntry {
    int grade;
public:
    Performance(const Student& student, int grade) : JournalEntry(student), grade(grade) {}
    string getInfo() const override { return student.getName() + ": Grade " + to_string(grade); }
};