#ifndef STARTER_H
#define STARTER_H
#include "Startphase.h"
#include "../Player/Player.h"
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

class Player;
class Map;

class Startphase{

public:

	Startphase();
	void welcome();
	int mainMenu();
	int initializeNumOfGamePlayers(vector<Player*>& gamePlayers);
	void createPlayers(vector<Player*>& gamePlayers, int numOfGamePlayers);
	void initializePlayersTurn(vector<Player*>& gamePlayers);
	void assignCountries(vector<Player*>& gamePlayers, Map* map);
	void setStatistics(vector<Player*>& gamePlayers);
	int roll();

};

#endif



