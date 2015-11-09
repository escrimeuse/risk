// Assignment #2 - COMP345 - Section DI - Fall 2015
// Author: Jennifer Sunahara (27590628)
//
//This is the header file MapDemo.h. This is the interface for the class MapDemo.
//Values of this type are specialised maps, which have a name, a list of continents and
//a list of countries. 
//The DemoMap has 6 countries, 3 continents, with 2 countries per continent.
//The concept of connectivity, adjacency and of continent exclusivity (countries being 
//members of only one continent) are implemented here.
//Please note that many of the function have been changed to output to the console for the 
//sake of the demo.

#pragma once
#include <string>
#include <vector>

using namespace std;
#include "Map.h"
#include "Continent.h"
#include "Country.h"

class MapDemo:public Map {


public:
	static const int DEMO_MAP_NUM_COUNTRIES = 6;//number of countries in the map
	static const int DEMO_MAP_NUM_CONTINENTS = 3;//number of continents in the map
	static const int DEMO_MAP_NUM_CONT_COUNTRIES = 2;//number of countries per continent
	MapDemo(string n);
	void makeAdjacent(string c1, string c2);//updates the adjacency matrices
	void printAdjacentCountryNames(string n);
	void printContinentsCountries(int n);
	void demoMap();//function specifically for the demo, used to set up the map


private:
	
	int visitedMap[DEMO_MAP_NUM_COUNTRIES];//6
	int visitedContinent[DEMO_MAP_NUM_CONT_COUNTRIES];//2 
	bool countriesAdj[DEMO_MAP_NUM_COUNTRIES][DEMO_MAP_NUM_COUNTRIES];//6 by 6
	bool checkContinentsValid();// do the continents contain connected countries?
	bool checkIsConnected();// called by getIsConnected
	void visitingMap(int x);//helper function for checkIsConnected 
	void visitingContinent(int x, bool b[][DEMO_MAP_NUM_CONT_COUNTRIES]);//helper function for checkContinentsValid
	void printAdjacentCountryNamesById(int n);//mainly for use in the demo
	
};


