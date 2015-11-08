#pragma once

#include "Startphase.h"
#include "GamePlayers.h"
#include "Countries.h"
#include "Continents.h"
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

class GamePlayers;

class Startphase{

public:

	Startphase();
	void welcome();
	int initializeNumOfGamePlayers(vector<GamePlayers*> gamePlayers) throw (int);
	void createPlayers(vector<GamePlayers*> gamePlayers);
	void initializePlayersTurn(vector<GamePlayers*> gamePlayers);
	void assignCountries(vector<GamePlayers*> gamePlayers);

};



