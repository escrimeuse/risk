// Assignment #2 - COMP345 - Section DI - Fall 2015
// Author: Jennifer Sunahara (27590628)
//
//This is the header file Map.h. This is the interface for the class Map.
//Values of this type are maps, which have a name, a list of continents and
//a list of countries. 
//The concept of connectivity, adjacency and of continent exclusivity (countries being 
//members of only one continent) are implemented here.
//This class is an abstract class with virtual methods.
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
	~Map();
	string getName() const;
	int getNumCountries() const;
	int getNumContinents() const;
	vector<Country*>* getCountries() const;
	vector<Continent*>* getContinents() const;
	bool getIsConnected();
	bool getContinentsValid();
	string getContinentNames() const;
	string getCountryNames() const;
	
	void setCountryNames();
	void setContinentNames();
	void setIsConnected(bool b); // set in checkIsConnected
	void setContinentsValid(bool b); //set in checkContinentsValid

	void addContinent(Continent* c);
	void addCountry(Country* c);

	void printContinentsCountries(int n);
	virtual void printAdjacentCountryNames(string n)=0;
	virtual void printAdjacentCountryNamesById(int n) = 0;//mainly for use in the demo
	virtual void demoMap()=0;//function specifically for the demo, used to set up the map

	virtual void makeAdjacent(string c1, string c2) = 0;//updates the adjacency matrices
	virtual bool checkIsConnected() = 0;// called by getIsConnected
	virtual bool checkContinentsValid() = 0;// called by getContinentsValid
	virtual void visitingMap(int x) = 0;//helper function for checkIsConnected

private:
	string name;
	int numCountries;
	int numContinents;
	vector<Continent*> *continents;
	vector<Country*> *countries;
	bool isConnected;
	bool continentsValid;// do the continents contain connected countries?
	//int visited[9];//9 because there are 9 countries	
	//bool countriesAdj[9][9]; 
	
};


