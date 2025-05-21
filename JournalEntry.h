#pragma once
#include "Student.h"
#include <chrono>

class JournalEntry {
protected:
    Student student;
    std::chrono::system_clock::time_point date;
public:
    JournalEntry(const Student& student) : student(student), date(std::chrono::system_clock::now()) {}
    virtual ~JournalEntry() = default;
    virtual std::string getInfo() const = 0;
};
