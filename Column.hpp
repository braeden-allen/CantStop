//----------------------------------------
//File: column.hpp
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
    public:
        Column(int colNum);
        ~Column() = default;
        [[nodiscard]] string colStateToString(EColStatus status)const;
        bool startTower(Player* player);
        bool move();
        void stop(Player* player);
        void bust();
        void printColors(ostream& os, int k) const;
        ostream& print(ostream& os) const;

    EColStatus getState() const;
};

ostream& operator << (ostream&, const Column&);