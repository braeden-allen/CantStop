//----------------------------------------
// File: column.cpp
// Authors: Braeden and Mateusz
//----------------------------------------
#include "Column.hpp"
#include "Player.hpp"
//----------------------------------------

const int Column::colLength[13] = {0, 0, 3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};

Column::Column(int colNum)
        : colNumber(colNum), maxPos(colLength[colNum]), capturedColor(ECcolor::White) {
    if (colNum < 2 || colNum > 12) { fatal("Column number must be between 2 and 12."); }
    for (int& pos : markerPositions) { pos = 0; } // Initialize all markers to 0
}

string Column::colStateToString(EColStatus status) const {
    switch (status) {
        case EColStatus::captured: return "captured";
        case EColStatus::pending: return "pending";
        case EColStatus::available: return "available";
    }
    return "unknown";
}

// Helper function for printing (add before Column::print)
string Column::colorToString(ECcolor color) {
    switch(color) {
        case ECcolor::Orange: return "Orange";
        case ECcolor::Yellow: return "Yellow";
        case ECcolor::Green:  return "Green";
        case ECcolor::Blue:   return "Blue";
        case ECcolor::White:  return "White";
        default: return "Unknown";
    }
}

bool Column::startTower(Player* player) {
    if (colState == EColStatus::captured) return false;

    ECcolor playerColor = player->getColor();
    int colorIdx = static_cast<int>(playerColor);

    // Check if player can start here (has existing marker or column is available)
    if (markerPositions[colorIdx] == 0 && colState != EColStatus::available) {
        return false;
    }

    // Set temporary tower (using White index)
    int towerIdx = static_cast<int>(ECcolor::White);
    markerPositions[towerIdx] = max(markerPositions[colorIdx], 1);
    colState = EColStatus::pending;
    return true;
}

bool Column::move() {
    if (colState != EColStatus::pending) return false;

    int towerIdx = static_cast<int>(ECcolor::White);
    if (markerPositions[towerIdx] < maxPos) {
        markerPositions[towerIdx]++;
        return true;
    }
    return false;
}

void Column::stop(Player* player) {
    if (colState != EColStatus::pending) return;

    ECcolor playerColor = player->getColor();
    int colorIdx = static_cast<int>(playerColor);
    int towerIdx = static_cast<int>(ECcolor::White);

    // Convert temporary tower to permanent marker
    markerPositions[colorIdx] = markerPositions[towerIdx];
    markerPositions[towerIdx] = 0; // Clear temporary tower

    // Check if column is captured
    if (markerPositions[colorIdx] == maxPos) {
        colState = EColStatus::captured;
        capturedColor = playerColor;
        player->wonColumn(colNumber);
    } else {
        colState = EColStatus::available;
    }
}

void Column::bust() {
    if (colState == EColStatus::pending) {
        // Only clear the temporary tower (White marker)
        int towerIdx = static_cast<int>(ECcolor::White);
        markerPositions[towerIdx] = 0;
        colState = EColStatus::available;
    }
}

void Column::printColors(ostream& os, int k) const {
    char square[6] = "-----"; // 5 chars (TOYGB)

    // Print permanent markers first
    for (int colorIdx = 1; colorIdx < 5; ++colorIdx) { // Skip White (index 0)
        if (markerPositions[colorIdx] >= k) {
            switch (static_cast<ECcolor>(colorIdx)) {
                case ECcolor::Orange: square[1] = 'O'; break;
                case ECcolor::Yellow: square[2] = 'Y'; break;
                case ECcolor::Green: square[3] = 'G'; break;
                case ECcolor::Blue: square[4] = 'B'; break;
                default: break;
            }
        }
    }

    // Print temporary tower on top (White marker)
    if (colState == EColStatus::pending && markerPositions[0] >= k) {
        square[0] = 'T';
    }
    os << square << " | ";
}

ostream& Column::print(ostream& os) const {
    if (colState == EColStatus::captured) {
        os << " by " << colorToString(capturedColor);
    }
    os << endl;

    // Print all squares in the column in one line
    os << "Column " << colNumber << ": ";
    os << "State: " << colStateToString(colState);
    os << " | ";

    for (int k = 1; k <= maxPos; ++k) {
        printColors(os, k);
        os << " | ";
    }
    os << endl;  // Extra spacing between columns

    return os;
}