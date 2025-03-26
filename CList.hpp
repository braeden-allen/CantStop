//----------------------------------------
// File: CList.hpp
// Authors: Braeden
//----------------------------------------
#pragma once
#include <memory>
#include "Player.hpp"
//----------------------------------------

class CList;

class Cell {
private:
    unique_ptr<Player> upp;
    Cell* next;
    friend class CList;

public:
    Cell(unique_ptr<Player>&& p, Cell* n = nullptr) : upp(std::move(p)), next(n) {}
    ~Cell() = default;
};

class CList {

private:
    Cell* head = nullptr;
    Cell* tail = nullptr;
    Cell* current = nullptr;
    int count = 0;

public:
    CList() = default;
    ~CList();

    bool empty() const { return count == 0; }
    int size() const { return count; }

    void add(unique_ptr<Player>&& p);
    void remove();
    void print(ostream& os) const;
    Player* next();
    Player* getCurrent() const;
    inline void init() { current = head; }
    friend class Cell;

}; ostream& operator << (ostream& os, const CList& clist);
