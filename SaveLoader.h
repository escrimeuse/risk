// Assignment #2 - COMP345 - Section DI - Fall 2015
// Author of SAVERLOADER: Caio Paiva
//
//This file was made by Caio Paiva for assignment 1 and has been partially modified
//to be integrated in my code. Unfortunately, I have only had time to make changes to 
//the save function and not the load function.

#pragma once

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "Map.h"
#include "Game.h"

using namespace std;

class SaverLoader {
public:
	SaverLoader();
	SaverLoader(string fn);
	void save(Map *map);
	static const string extension;
	Map* loadMap();
	vector<Player*>* loadPlayers();
	list<Card*>* loadCards(cardType card);
	string loadCurrentPlayer();
	int loadCurrentPhase();
	int loadNumCardSetsTradedIn();
//	void saveGame(Game* game);

private:
	string fileName;
	//char* getTime();
	void saveMap(ofstream& out, Map *map);
	void saveCountries(ofstream& out, Map *map);
	void saveContinents(ofstream& out, Map *map);
	void saveAdjencencies(ofstream& out, Map *map);
	void savePlayersAndCards(Game* game);
	void saveState(Game* game);
	/*void loadMap(ifstream& in, Map* map);
	void loadCountries(ifstream& in, Map* map);
	void loadContinents(ifstream& in, Map* map);
	void loadAdjacencies(ifstream& in, Map* map);*/
};
