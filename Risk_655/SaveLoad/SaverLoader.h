// Assignment #3 - COMP345 - Section DI - Fall 2015
// Author of SAVERLOADER: Caio Paiva, Catryn Griffiths, Jennifer Sunahara
//
//This is the implementation file ConquestSaverLoader.cpp of the class ConquestSaverLoader.
//The interface of this class is in the header file ConquestSaverLoader.h.

#pragma once

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "../Map/Map.h"
#include "../GameBuilder/Game.h"

using namespace std;

class SaverLoader {
public:
	SaverLoader();
	SaverLoader(string fn);
	virtual void savingMap(Map *map);
	static const string extension;
	virtual Map* loadMap();
	vector<Player*>* loadPlayers();
	vector<Card*>* loadCards(cardType card);
	string loadCurrentPlayer();
	int loadCurrentPhase();
	int loadNumCardSetsTradedIn();
	void savePlayersAndCards(Game* game);
	void saveState(Game* game);
	string loadGameName();









private:
	string fileName;
	void saveMap(ofstream& out, Map *map);
	void saveCountries(ofstream& out, Map *map);
	void saveContinents(ofstream& out, Map *map);
	void saveAdjencencies(ofstream& out, Map *map);
};
