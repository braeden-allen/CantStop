//----------------------------------------
// File: CList.hpp
// Authors: Braeden
//----------------------------------------
#pragma once
#include <memory>
#include "Player.hpp"
//----------------------------------------

class CList {

private:
    class Cell {
        unique_ptr<Player> upp;
        Cell* next;
        Cell(unique_ptr<Player>&& p, Cell* n = nullptr) : upp(std::move(p)), next(n) {}
        ~Cell() = default;
        friend class CList;
    };

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
    void init() { current = head; }
    friend class Cell;

    friend ostream& operator << (ostream& os, const CList& clist);
};