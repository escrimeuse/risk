#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Map.h"
#include "Player.h"

using namespace std;

class Game {

public:
	Map* map;
	vector<Player*>* gamePlayers;
	Player* currentPlayer;
	int phase; 


};


#endif