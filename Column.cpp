//----------------------------------------
//File: column.cpp
//Authors: Braeden and Mateusz
//----------------------------------------

#include "Column.hpp"

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
    if (colState == EColStatus::captured) {return false;}//can't start tower if captured

    int colorIdx = static_cast<int>(player->getColor());
    int currentPos = markerPositions[colorIdx];

    if (currentPos == 0) {markerPositions[colorIdx] = 1;} //place tower at position 1
    else if (currentPos < 7) {markerPositions[colorIdx]++;}//move tower forward
    else {return false;}//can't start on a captured column

    if (markerPositions[colorIdx] == 7) {colState = EColStatus::pending;}//column is pending capture
    return true;
}

bool Column::move(){
    if (colState == EColStatus::captured) {return false;}//can't move if column is not available

    for (int colorIdx = 0; colorIdx < 5; ++colorIdx) {
        if (markerPositions[colorIdx] > 0 && markerPositions[colorIdx] < 7) {
            markerPositions[colorIdx]++;
            if (markerPositions[colorIdx] == 7) {colState = EColStatus::pending;}//column is pending capture
            return true;
        }
    }
    return false; //No tower to move
}

void Column::stop(Player* player) {
    int colorIdx = static_cast<int>(player->getColor());
    int currentPos = markerPositions[colorIdx];

    if (colState == EColStatus::pending) {//capture column if pending
        colState = EColStatus::captured;
        player->wonColumn(colNumber); //notify player of column win
    }
    markerPositions[colorIdx] = 0; //reset marker position
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

    // Print each square in the column
    for (int i = 1; i <= 7; ++i) {
        os << "Square " << i << ": ";
        string square = "-----"; //Default empty square

        // Check for towers or markers in the current square
        for (int colorIdx = 0; colorIdx < 5; ++colorIdx) {
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