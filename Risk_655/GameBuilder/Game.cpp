#include <iostream>
#include "Game.h"

void Game::initializeCards() {
	
	if (!cardsInitialized) {
		cout << "Initializing game cards..." << endl;
		gameInfantryCards = new vector<Card*>();
		gameCavalryCards = new vector<Card*>();
		gameArtilleryCards = new vector<Card*>();
		gameWildCards = new vector<Card*>();
		vector<Country*>* tempCountries = map->getCountries();
		for (vector<Country*>::iterator i = tempCountries->begin(); i != tempCountries->end(); ++i) {
			gameInfantryCards->push_back(new Card((*i)->getName(), infantry));
			gameCavalryCards->push_back(new Card((*i)->getName(), cavalry));
			gameArtilleryCards->push_back(new Card((*i)->getName(), artillery));
			gameWildCards->push_back(new Card((*i)->getName(), wild));
		}
		
		cardsInitialized = true;
		cout << "Finished initializing game cards..." << endl;
	}
	else {
		std::cout << "ERROR: Cards cannot be re-initialized!" << endl;
	}
	
}

