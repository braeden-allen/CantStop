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
        EColStatus colState;
        int markerPositions[5];
    public:
        Column(int colNum);
        ~Column() = default;
        [[nodiscard]] EColStatus columnState() const;
        [[nodiscard]] string colStateToString(EColStatus status)const;
        bool startTower(Player* player);
        bool move();
        void stop(Player* player);
        void bust();
        ostream& print(ostream& os) const;
};

ostream& operator << (ostream&, const Column&);