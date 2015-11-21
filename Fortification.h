#pragma once

#include "Country.h"
#include "Player.h"
#include"Map.h"
#include"MapDemo.h"
#include<iostream>

class MapDemo;

class Fortification {

public:
	Fortification();
	void fortify(Player* gamePlayer, Map* map);

};