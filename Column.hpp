//----------------------------------------
//File: column.hpp
//Authors: Braeden and Mateusz
//----------------------------------------
#pragma once
#include "tools.hpp"
#include "enums.hpp"
#include "Player.hpp"
#include <array>

class Column {
    private:
        static const int colLength[13];
        const int colNumber;
        EColStatus colState;
        array<int, 5> markerPositions;
    public:
        Column(int colNum);
        ~Column();
        EColStatus columnState() const;
        string colStateToString(EColStatus status);
        bool startTower(Player* player);
        bool move();
        void stop(Player* player);
        void bust();
        ostream& print(ostream& os) const;
};

ostream& operator << (ostream&, const Column&);