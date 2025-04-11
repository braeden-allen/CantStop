//----------------------------------------
//File: exceptions.hpp
//Authors: Mateusz & Braeden
//----------------------------------------
#pragma once
#include <cstring>
#include "tools.hpp"
//----------------------------------------
//----------------------------------------
// Base Case BadPlayer
//----------------------------------------
class BadPlayer {
protected:
    char* name;
    char* color;

public:
    explicit BadPlayer(const char* n = "", const char* c = "") {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        color = new char[strlen(c) + 1];
        strcpy(color, c);
    }

    virtual ~BadPlayer() {
        delete[] name;
        delete[] color;
    }

    virtual void print() const {
        cout << "BadPlayer exception: Both name and color are invalid\n";
        basePrint();
    }

    virtual void basePrint() const {
        cout << "  Name entered: " << name << "\n";
        cout << "  Color entered: " << color << "\n";
    }
};

//----------------------------------------
// Derived class BadName
//----------------------------------------
class BadName : public BadPlayer {
public:
    BadName(const char* n, const char* c) : BadPlayer(n, c) {}

    virtual void print() const override {
        cout << "BadName exception: Name '" << name << "' is already in use\n";
        basePrint();
    }
};

//----------------------------------------
// Derived class BadColor
//----------------------------------------
class BadColor : public BadPlayer {
public:
    BadColor(const char* n, const char* c) : BadPlayer(n, c) {}

    virtual void print() const override {
        cout << "ERROR: Color '";
        switch(toupper(color[0])) {
            case 'O': cout << "Orange"; break;
            case 'Y': cout << "Yellow"; break;
            case 'G': cout << "Green"; break;
            case 'B': cout << "Blue"; break;
            default: cout << color;
        }
        cout << "' is already in use.\n";
        basePrint();
    }
};

//----------------------------------------
// Derived class BadChoice
//----------------------------------------
class BadChoice : public std::exception {
protected:
    char choice;

public:
    explicit BadChoice(char c) : choice(c) {}

    virtual void print() const {
        cerr << "Invalid choice: " << choice << endl;
    }
};

//----------------------------------------
// Derived class DuplicateSlot
//----------------------------------------
class DuplicateSlot : public BadChoice {
public:
    DuplicateSlot(char c) : BadChoice(c) {}

    void print() const override {
        cerr << "\nDuplicate dice selection: " << choice << endl;
        cerr << "Select two different dice (e.g., ab): ";
    }
};

class BadSlot : public BadChoice {
public:
    BadSlot(char c) : BadChoice(c) {}

    void print() const override {
        cerr << "Invalid dice selection: " << choice << endl;
        cerr << "Please select from the available options." << endl;
    }
};