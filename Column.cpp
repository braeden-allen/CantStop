//----------------------------------------
//File: column.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Column.hpp"
//----------------------------------------

const int Column::colLength[13] = {0,0,3,5,7,9,11,13,11,9,7,5,3};

Column::Column(int colNum) : colNumber(colNum), colState(EColStatus::available){
    if (colNum < 2 || colNum > 12) {throw invalid_argument("Column number must be between 2 and 12.");}
    for(int & markerPosition : markerPositions) {markerPosition = 0;} //init markerPositions to 0
}

EColStatus Column::columnState() const{return colState;}

string Column::colStateToString(EColStatus status)const{
    switch (status) {
        case EColStatus::captured: return "captured";
        case EColStatus::pending: return "pending";
        case EColStatus::available: return "available";
        default: return "unknown";
    }
}

bool Column::startTower(Player* player) {
    if (colState == EColStatus::captured) {return false;}//can't start a tower on captured column

    int colorIdx = static_cast<int>(player->getColor());
    int currentPos = markerPositions[colorIdx];
    int maxPos = colLength[colNumber];

    if (currentPos == 0) {markerPositions[colorIdx] = 1;} //place the tower at position 1 if empty
    else if (currentPos < maxPos) {markerPositions[colorIdx]++;} //move tower if available
    else {return false;} //can't start tower if @max position

    int towerIdx = static_cast<int>(ECcolor::White);//set tower marker for the White (Tower)
    if (markerPositions[towerIdx] == 0) {markerPositions[towerIdx] = 1;}//place the tower at position 1

    if (markerPositions[colorIdx] == maxPos) {colState = EColStatus::pending;}//column is pending capture

    return true;
}

bool Column::move() {
    if (colState == EColStatus::captured || colState == EColStatus::pending) {return false;} //can't move if unavailable

    int maxPos = colLength[colNumber];
    bool moved = false;

    for (int &markerPosition : markerPositions) {
        if (markerPosition > 0 && markerPosition < maxPos) {markerPosition++; //move the marker forward
            if (markerPosition == maxPos) {colState = EColStatus::pending;} //column is pending capture
            moved = true;
        }
    }
    return moved; //return true if moved
}

void Column::stop(Player* player) {
    int colorIdx = static_cast<int>(player->getColor());
    int maxPos = colLength[colNumber];

    if (markerPositions[colorIdx] == maxPos) {
        colState = EColStatus::captured;
        player->wonColumn(colNumber); //notify of column win
    }
    else {markerPositions[colorIdx] = 0;} //reset marker to 0 (no progress saved)

    bool hasMarkers = false;
    for (int markerPosition : markerPositions) {if (markerPosition > 0) {hasMarkers = true; break;}}
    if (!hasMarkers) {colState = EColStatus::available;} //set state to available if no markers
}

void Column::bust(){
    for (int & markerPosition : markerPositions) {markerPosition = 0;}
    colState = EColStatus::available; //reset column to available
}

ostream& Column::print(ostream& os) const {
    os << "\nColumn " << colNumber << ": ";
    os << "State: " << colStateToString(colState) << endl;

    int maxPos = colLength[colNumber];
    for (int k = 1; k <= maxPos; ++k) {
        os << "Square " << k << ": ";
        string square = "-----"; //5 characters for tiles (TOYGB)

        for (int colorIdx = 0; colorIdx < 5; ++colorIdx) { //check markers in square
            if (markerPositions[colorIdx] == k) {
                if (colorIdx == static_cast<int>(ECcolor::White)) {square[0] = 'T';} //tower
                else {
                    switch (static_cast<ECcolor>(colorIdx)) { //player markers (O, Y, G, B)
                        case ECcolor::Orange: square[1] = 'O'; break;
                        case ECcolor::Yellow: square[2] = 'Y'; break;
                        case ECcolor::Green: square[3] = 'G'; break;
                        case ECcolor::Blue: square[4] = 'B'; break;
                        default: break;
                    }
                }
            }
        }
        for (char &c : square) {if (c == '\0') c = '-';}
        os << square << " | ";
    }
    os << endl;
    return os;
}