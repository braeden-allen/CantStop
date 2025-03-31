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
    if (empty()) {cout << "List is empty" << endl;return;}

    Cell* temp = current;

    if (current == head) {
        if (head == tail) { //only one node in list
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            tail->next = head; //keep circularity
        }
    } else if (current == tail) { //remove tail
        Cell* temp = head;
        while (temp->next != tail) {temp = temp->next;} //walk the list
        tail = temp;
        tail->next = head; // Update tail's next to point to the head
    } else { //remove middle node (most common)
        Cell* prev = head;
        while (prev->next != current) {prev = prev->next;} //walk the list
        prev->next = current->next; //skip current node
    }

    current = current->next; //rearrange list to close any gaps

    delete temp; //delete current
    count--; //update count

    if (empty()) {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }
}

void CList::print(ostream& os) const {
    if (empty()) {os << "No players in the list.\n";return;}

    Cell* curr = head;
    do {
        os << *curr->upp << "\n---------------\n";
        curr = curr->next;
    } while (curr != head);
}

Player* CList::next() { //advances to the next cell and returns the Player*
    if (empty()) return nullptr;
    if (!current) current = head;  //initialize if needed

    Player* player = current->upp.get();
    current = current->next;
    return player;
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
