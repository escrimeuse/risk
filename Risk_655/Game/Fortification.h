#pragma once

#include "../Map/Country.h"
#include "../Player/Player.h"
#include"../Map/Map.h"
#include "../ObserverPattern/Subject.h"
#include<iostream>
#include <vector>


class Fortification :public Subject {

public:
	Fortification();
	void fortify(Player* gamePlayer, Map* map); //function called in the game to fortify the country each player
	static const int FORTIFICATION_ID = 98765;
};