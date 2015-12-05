#ifndef GAME_H
#define GAME_H

#include <vector>
#include "../Map/Map.h"
#include "../Player/Player.h"

using namespace std;

class Game {
	friend class ExistingGameBuilder;

public:
	Game() {
	}
	string gameName;
	Map* map;
	vector<Player*>* gamePlayers;
	Player* currentPlayer;
	int phase;	// the current phase of the game (battle, reinforcement, etc)
	int numCardSetsTradedIn; // the number of card sets traded in for armies
	vector<Card*> *gameInfantryCards;	
	vector<Card*> *gameCavalryCards;	
	vector<Card*> *gameArtilleryCards;	
	vector<Card*> *gameWildCards;
	bool cardsInitialized;
	void initializeCards(); 
	void setGameName(string name) {
		gameName = name;
	}
	string getGameName() {
		return gameName;
	}

	

};


#endif