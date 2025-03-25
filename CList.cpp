//----------------------------------------
// File: CList.cpp
// Authors: Braeden
//----------------------------------------
#include "CList.hpp"
//----------------------------------------

CList::~CList() { //destructor deletes all cells in list
    if (empty()) return;

    Cell* curr = head;
    do {
        Cell* temp = curr;
        curr = curr->next;
        delete temp;  //auto deletes the unique_ptr<Player>
    } while (curr != head);
}

void CList::add(unique_ptr<Player>&& p) { //adds new player to the list
    Cell* newCell = new Cell(std::move(p));

    if (empty()) {
        head = tail = newCell;
        newCell->next = head;  //points to itself
    } else {
        tail->next = newCell;
        newCell->next = head;  //close the circle
        tail = newCell;
    }
    count++;
}

void CList::remove() { //removes the current cell
    if (empty()) return;

    Cell* toRemove = current;

    if (count == 1) head = tail = current = nullptr;
    else {
        Cell* prev = head; //find previous cell to update list
        while (prev->next != current) prev = prev->next;

        prev->next = current->next;
        if (current == head) head = current->next;
        if (current == tail) tail = prev;
        current = current->next;  //walk the list
    }
    delete toRemove;  //unique_ptr<Player> auto-deletes
    count--;
}

void CList::print(ostream& os) const {
    if (empty()) {os << "No players in the list.\n";return;}

    Cell* curr = head;
    do {
        os << *curr->upp << "\n---\n";
        curr = curr->next;
    } while (curr != head);
}

Player* CList::next() { // advances to the next cell and returns the Player*
    if (empty()) return nullptr;

    if (!current) current = head;  // initialize if needed
    Player* player = current->upp.get();
    current = current->next;
    return player;
}

ostream& operator<<(ostream& os, const CList& clist) {
    clist.print(os);
    return os;
}