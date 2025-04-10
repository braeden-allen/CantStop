//----------------------------------------
//File: exceptions.hpp
//Authors: Mateusz & Braeden
//----------------------------------------

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <iostream>
#include <cstring>

// Base exception for player input problems
class BadPlayer {
public:
    char* input;  // holds the offending input string

    BadPlayer(const char* inp = "") {
        input = new char[strlen(inp) + 1];
        strcpy(input, inp);
    }
    
    virtual ~BadPlayer() { 
        delete[] input; 
    }
    
    virtual void print() const {
        std::cout << "BadPlayer exception: invalid input -> " << input << "\n";
    }
    
    virtual void basePrint() const {
        std::cout << "Player data entered: " << input << "\n";
    }
};

// Thrown if a name is already in use
class BadName : public BadPlayer {
public:
    BadName(const char* inp = "") : BadPlayer(inp) {}
    
    virtual void print() const override {
        std::cout << "BadName exception: Name already in use.\n";
        basePrint();
    }
};

// Thrown if a color is already in use
class BadColor : public BadPlayer {
public:
    BadColor(const char* inp = "") : BadPlayer(inp) {}
    
    virtual void print() const override {
        std::cout << "BadColor exception: Color already in use.\n";
        basePrint();
    }
};

#endif // EXCEPTIONS_HPP
