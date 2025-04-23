//----------------------------------------
// File: CList.cpp
// Authors: Braeden & Mateusz
//----------------------------------------
#include "CList.hpp"
//----------------------------------------

CList::~CList() { //destructor deletes all cells in CList
    if (empty()) return;

    Cell* curr = head;
    do {
        Cell* temp = curr;
        curr = curr->next;
        delete temp;  //auto deletes the unique_ptr<Player>
    } while (curr != head);
}

void CList::add(unique_ptr<Player>&& p) {
    Cell* newCell = new Cell(std::move(p));

    if (empty()) {
        head = tail = newCell;
        newCell->next = head;
    } else {
        tail->next = newCell;
        newCell->next = head;
        tail = newCell;
    }
    count++;
}

void CList::remove() {
    if (empty()) {cout << "List is empty\n"; return;}
    Cell* toDelete = current;
    if (head == tail) {// Handle a single-node case
        head = tail = current = nullptr;
    }
    else {// Find previous node
        Cell* prev = head;
        while (prev->next != current && prev->next != head) {
            prev = prev->next;
        }

        // Update links
        if (current == head) head = head->next;
        if (current == tail) tail = prev;
        prev->next = current->next;
        current = current->next;  //walk CList
        tail->next = head;        //maintain circularity
    }
    delete toDelete;
    count--;
}

void CList::print(ostream& os) const {
    if (empty()) {os << "No players in the list.\n";return;}

    Cell* curr = head;
    do {
        os << *curr->upp << "\n---------------\n";
        curr = curr->next;
    } while (curr != head);
}

Player* CList::next() {
    if (empty()) return nullptr;
    if (!current) current = head;

    Player* p = current->upp.get();
    current = current->next;
    return p;
}

Player* CList::getCurrent() const {
    if (current == nullptr) {
        return nullptr;
    }
    return current->upp.get();
}

ostream& operator<<(ostream& os, const CList& clist) {
    clist.print(os);
    return os;
}