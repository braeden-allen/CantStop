//----------------------------------------
//File: Column.hpp
//Authors: Braeden and Mateusz
//----------------------------------------
#pragma once
#include "tools.hpp"
#include "enums.hpp"
#include "Player.hpp"
//----------------------------------------

class Column {
    private:
        static const int colLength[13];
        const int colNumber;
        EColStatus colState = EColStatus::available;
        int markerPositions[5];
        int const maxPos;
        ECcolor capturedColor;
    public:
        explicit Column(int colNum);
        ~Column() = default;
        static string colStateToString(EColStatus status);
        static string colorToString(ECcolor color);
        bool startTower(Player* player);
        bool move();
        void stop(Player* player);
        void bust();
        void printColors(ostream& os, int k) const;
        ostream& print(ostream& os) const;
        [[nodiscard]] EColStatus getState() const{return colState;}
};
ostream& operator << (ostream&, const Column&);