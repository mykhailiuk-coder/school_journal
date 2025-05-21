#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "JournalEntry.h"
#include "Attendance.h"

class Journal {
    vector<unique_ptr<JournalEntry>> entries;
public:
    void addEntry(unique_ptr<JournalEntry> entry) {
        entries.push_back(move(entry));
    }

    void printAll() const {
        for (const auto& entry : entries) {
            cout << entry->getInfo() << endl;
        }
    }
};