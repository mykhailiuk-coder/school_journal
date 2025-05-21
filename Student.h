#pragma once
#include <string>

class Student {
    int id;
    std::string name;
public:
    Student(int id, const std::string& name) : id(id), name(name) {}
    int getId() const { return id; }
    std::string getName() const { return name; }
};
