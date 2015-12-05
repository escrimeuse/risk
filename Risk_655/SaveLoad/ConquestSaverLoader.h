// Assignment #3 - COMP345 - Section DI - Fall 2015
// Author: Jennifer Sunahara (27590628)
//
//This is the header file ConquestSaverLoader.h. This is the interface for the class ConquestSaverLoader.
//This exists to provide an alternative file format to that used by the Original SaverLoader.
//A double adapter class is used to provide both options.

#pragma once

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "../Map/Map.h"


using namespace std;

class ConquestSaverLoader {
public:
	ConquestSaverLoader();
	ConquestSaverLoader(string fn);
	virtual void savingMap(Map *map);
	static const string extension;
	virtual Map* loadMap();

private:
	string fileName;
	void saveMap(ofstream& out, Map *map);
	void saveTerritories(ofstream& out, Map *map);
	void saveContinents(ofstream& out, Map *map);
};
