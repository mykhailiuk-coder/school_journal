# Student Journal Management System

This C++ project implements a basic **Student Journal System** to track and manage attendance and performance records for students. It uses object-oriented programming principles including inheritance, polymorphism, and smart pointers.

## 📋 Features

- Add multiple students by name.
- Track attendance with dates (present/absent).
- Record multiple grades for each student.
- View a complete report per student, including:
  - Attendance (present and absent dates)
  - Performance (grades in a single line)
- Switch between different students during runtime.
- Console-based interface with structured menu.

## 🧩 Project Structure

.
├── ui-main.cpp
├── Student.h
├── JournalEntry.h
├── Attendance.h
├── Performance.h
├── Journal.h


### Header Files

- **Student.h** – Defines a student with ID and name.
- **JournalEntry.h** – Abstract base class with virtual method `getInfo()`.
- **Attendance.h** – Derived class that stores presence or absence info.
- **Performance.h** – Derived class that stores student grades.
- **Journal.h** – Holds and prints all journal entries using smart pointers.

### ui-main.cpp

Handles the console interface, data input, student switching, and summary reports. Does **not** allow direct editing of class definitions.

## 🛠️ How to Build

Make sure all `.h` and `.cpp` files are in the same directory.
Compile the project
