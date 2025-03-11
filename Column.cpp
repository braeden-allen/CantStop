//----------------------------------------
// File: column.cpp
// Authors: Braeden and Mateusz
//----------------------------------------
#include "Column.hpp"
#include "Player.hpp" // Assuming Player.hpp is needed for Player class
//----------------------------------------

const int Column::colLength[13] = {0, 0, 3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};

Column::Column(int colNum)
        : colNumber(colNum), maxPos(colLength[colNum]) {
    if (colNum < 2 || colNum > 12) {fatal("Column number must be between 2 and 12.");}
    for (int& pos : markerPositions) {pos = 0;}//Initialize markerPositions to 0
}

EColStatus Column::getState() const {
    return colState;
}

string Column::colStateToString(EColStatus status) const {
    switch (status) {
        case EColStatus::captured: return "captured";
        case EColStatus::pending: return "pending";
        case EColStatus::available: return "available";
    }
    return "unknown"; //fallback, though unreachable
}

bool Column::startTower(Player* player) {
    if (colState == EColStatus::captured) {return false;}//can't start tower on captured column

    int colorIdx = (int)(player->getColor());
    int currentPos = markerPositions[colorIdx];

    if (currentPos == 0) {markerPositions[colorIdx] = 1;} //place tower at pos 1 if empty
    else if (currentPos < maxPos) {markerPositions[colorIdx]++;} //move tower if available
    else {return false;}//can't start tower if at max position

    int towerIdx = (int)(ECcolor::White); //set tower marker for White
    if (markerPositions[towerIdx] == 0) {markerPositions[towerIdx] = 1;}//place the tower at position 1

    if (markerPositions[colorIdx] == maxPos) {colState = EColStatus::pending;}//column is pending

    return true;
}

bool Column::move() {
    if (colState == EColStatus::captured || colState == EColStatus::pending) {return false;} //can't move if unavailable

    bool moved = false;
    for (int& pos : markerPositions) {
        if (pos > 0 && pos < maxPos) {
            pos++; //move the marker forward
            if (pos == maxPos) {colState = EColStatus::pending;}//column is pending capture
            moved = true;
        }
    }
    return moved; //return true if marker moved
}

void Column::stop(Player* player) {
    int colorIdx = (int)(player->getColor());
    if (markerPositions[colorIdx] == maxPos) {
        colState = EColStatus::captured;
        player->wonColumn(colNumber); //notify player of col win
    } else {markerPositions[colorIdx] = 0;}//reset marker to 0
}

void Column::bust() {
    for (int& pos : markerPositions) {
        pos = 0; //reset all markers to 0
    }
    colState = EColStatus::available; //reset column to available
}

void Column::printColors(ostream& os, int k) const {
    char square[6] = "-----"; //5 chars (TOYGB)
    if (markerPositions[(int)(ECcolor::White)] == k) {
        square[0] = 'T'; //tower
    }
    for (int colorIdx = 1; colorIdx < 5; ++colorIdx) { //skip white (tower)
        if (markerPositions[colorIdx] == k) {
            switch ((ECcolor)(colorIdx)) {
                case ECcolor::Orange: square[1] = 'O'; break;
                case ECcolor::Yellow: square[2] = 'Y'; break;
                case ECcolor::Green: square[3] = 'G'; break;
                case ECcolor::Blue: square[4] = 'B'; break;
            }
        }
    }
    os << square << " | ";
}

ostream& Column::print(ostream& os) const {
    os << "\nColumn " << colNumber << ": ";
    os << "State: " << colStateToString(colState) << endl;
    for (int k = 1; k <= maxPos; ++k) {
        os << "Square " << k << ": ";
        printColors(os, k);
    }
    os << endl;
    return os;
}