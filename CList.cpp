//----------------------------------------
// File: CList.cpp
// Authors: Braeden & Mateusz
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

void CList::add(unique_ptr<Player>&& p) { //adds new player to the list with move constructor
    Cell* newCell = new Cell(std::move(p));

    if (empty()) {
        head = tail = current = newCell;
        newCell->next = head;  //points to itself
    } else {
        tail->next = newCell;
        newCell->next = head;  //close the circle
        tail = newCell;
    }
    count++;
}

void CList::remove() {
    if (empty() || !current) return;

    Cell* toRemove = current;
    Cell* prev = head;

    // Find the node before `toRemove`
    while (prev->next != toRemove && prev->next != head) {
        prev = prev->next;
    }

    // Update links
    prev->next = toRemove->next;
    if (toRemove == head) head = toRemove->next;
    if (toRemove == tail) tail = (head == tail) ? nullptr : prev;

    // Update current (move to next node before deletion)
    current = toRemove->next;
    delete toRemove;
    count--;

    if (empty()) current = head = tail = nullptr;
}

void CList::print(ostream& os) const {
    if (empty()) {os << "No players in the list.\n";return;}

    Cell* curr = head;
    do {
        os << *curr->upp << "\n---------------\n";
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
