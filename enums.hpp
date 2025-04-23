//----------------------------------------
//File: enums.hpp
//Authors: Braeden and Mateusz
//----------------------------------------
#pragma once
#include "tools.hpp"
//----------------------------------------

enum class ECcolor {White, Orange, Yellow, Green, Blue};
enum class EColStatus{available, pending, captured};
enum class EGameStatus{Begun, Done, Quit};

extern const string colorNames[];
extern const string colState[];
extern const string gameState[];