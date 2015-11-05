// Assignment #1 - COMP345 - Section DI - Fall 2015
// Author: Jennifer Sunahara (27590628)
//
//This is the header file Map.h. This is the interface for the class Map.
//Values of this type are maps, which have a name, a list of continents and
//a list of countries. 
//The concept of connectivity, adjacency and of continent exclusivity (countries being 
//members of only one continent) are implemented here.
//Please note that many of the function have been changed to output to the console for the 
//sake of the demo.

#pragma once
#include <string>
#include <vector>

using namespace std;

#include "Continent.h"
#include "Country.h"

class Map {
public:
	Map(string n, int countries, int continents);
	int getNumCountries() const;
	int getNumContinents() const;
	string getName() const;
	string getContinentNames() const;
	string getCountryNames() const;
	void makeAdjacent(string c1, string c2);//updates the adjacency matrices
	bool getIsConnected();
	void setCountryNames();
	void setContinentNames();
	void printAdjacentCountryNames(string n);
	void printContinentsCountries(int n);
	void demoMap();//function specifically for the demo, used to set up the map
	
	
private:
	string name;
	int numCountries;
	int numContinents;
	int visited[9];//9 because there are 9 countries
	vector<Continent*> *continents;
	vector<Country*> *countries;
	void addContinent(Continent* c);
	void addCountry(Country* c);
	bool countriesAdj[9][9]; 
	bool isConnected; 
	bool ContinentsValid;// do the continents contain connected countries?
	void setIsConnected(bool b); // set in checkIsConnected
	bool checkIsConnected();// called by getIsConnected
	void visiting(int x);//helper function for checkIsConnected
	void printAdjacentCountryNamesById(int n);//mainly for use in the demo
	


};


