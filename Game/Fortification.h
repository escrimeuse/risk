#pragma once

#include "../Map/Country.h"
#include "../Player/Player.h"
#include"../Map/Map.h"
#include"../Map/MapDemo.h"
#include<iostream>

class MapDemo;

class Fortification {

public:
	Fortification();
	void fortify(Player* gamePlayer, Map* map);

};