//----------------------------------------
//File: column.cpp
//Authors: Braeden and Mateusz
//----------------------------------------

#include "Column.hpp"

const int Column::colLength[13] = {0,0,3,5,7,9,11,13,11,9,7,5,3}; //

Column::Column(int colNum) : colNumber(colNum), colState(EColStatus::available){
    if (colNum < 2 || colNum > 12) {throw invalid_argument("Column number must be between 2 and 12.");}
    for(int & markerPosition : markerPositions) {markerPosition = 0;}// Initialize markerPositions to 0
}

Column::~Column() = default;

EColStatus Column::columnState() const{return colState;}

string Column::colStateToString(EColStatus status){
    switch (status) {
        case EColStatus::captured: return "captured";
        case EColStatus::pending: return "pending";
        case EColStatus::available: return "available";
    }
}

bool Column::startTower(Player* player) {
    if (colState == EColStatus::captured || colState == EColStatus::pending) {return false;}    // Cannot start a tower if not avilable

    int colorIdx = static_cast<int>(player->getColor());
    int currentPos = markerPositions[colorIdx];
    int maxPos = colLength[colNumber];

    if (currentPos == 0) {markerPositions[colorIdx] = 1;}    //place the tower at position 1 if empty
    else if (currentPos < maxPos) {markerPositions[colorIdx]++;} // If the player already has a tile, move the tower forward
    else {return false;} //if the tower is @ max, illegal to start new tower

    if (markerPositions[colorIdx] == maxPos) {colState = EColStatus::pending;}    // If the tower reaches max, pending

    return true;
}

bool Column::move() {

    if (colState == EColStatus::captured || colState == EColStatus::pending) {return false;}//can't move if the column is captured or pending
    int maxPos = colLength[colNumber];//maximum position for column

    for (int colorIdx = 0; colorIdx < 5; ++colorIdx) {
        if (markerPositions[colorIdx] > 0 && markerPositions[colorIdx] < maxPos) {markerPositions[colorIdx]++;
            if (markerPositions[colorIdx] == maxPos) {colState = EColStatus::pending;}//column is pending capture
            return true;
        }
    }
    return false; //no tower to move
}

void Column::stop(Player* player) {
    int colorIdx = static_cast<int>(player->getColor());
    int currentPos = markerPositions[colorIdx];
    int maxPos = colLength[colNumber]; //max position for column


    if (currentPos == maxPos) {//check if marker is at end
        colState = EColStatus::captured;
        player->wonColumn(colNumber); // Notify player of column win
    }
    markerPositions[colorIdx] = 0; //reset the marker position
}

void Column::bust(){
    //placeholder function until implemented
}

ostream& Column::print(ostream& os)const {

    string state;
    switch (colState) {
        case EColStatus::captured: state = "captured"; break;
        case EColStatus::pending: state = "pending"; break;
        case EColStatus::available: state = "available"; break;
    }

    os << "\n\nColumn " << colNumber << ": " << endl;
    os << "State: " << state << endl;

    int maxPos = colLength[colNumber];//print each square in the column

    for (int i = 1; i <= maxPos; ++i) {
        os << "Square " << i << ": ";
        string square = "-----";//default empty square

        for (int colorIdx = 0; colorIdx < 5; ++colorIdx) {//check for markers in space
            if (markerPositions[colorIdx] == i) {
                if (colorIdx == static_cast<int>(ECcolor::White)) {square[0] = 'T';} // Tower
                else {square[colorIdx + 1] = colorNames[colorIdx][0];} // Player marker
            }
        }
        os << square << endl;
    }
    os << endl;
    return os;
}