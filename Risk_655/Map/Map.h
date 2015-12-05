// Assignment #3 - COMP345 - Section DI - Fall 2015
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
#include "../ObserverPattern/Subject.h"

using namespace std;

#include "Continent.h"
#include "Country.h"

class Map : public Subject {
public:
	Map(string n, int countries, int continents);
	Map(string n, int ctry, int ctnt, int dummy);
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
	Continent* getContinentByName(string n);
	Country* getCountryByName(string n);
	
	void setName(string n);
	void setCountryNames();
	void setContinentNames();
	void setContinentCountries();

	void addContinent(Continent* c);
	void addCountry(Country* c);
	void setAdjacency(bool** matrix);
		
	void makeNotAdjacent(string c1, string c2);
	void makeAdjacent(string c1, string c2);//updates the adjacency matrices
	bool checkIsAdjacentByIndex(int c1, int c2);//check if c1 and c2 are adjacent via their id
	bool checkIsConnected();// called by getIsConnected
	bool checkContinentsValid();// called by getContinentsValid
	vector<Country*> getCountriesConnectedTo(Country* c);
	bool checkIsAdjacent(Country *c1, Country *c2);

	void printContinentsCountries(int n);
	void printAdjacentCountryNames(string n);
	void printAdjacentCountryNames(ofstream& fout, string n);
	void printAdjacentCountryNamesById(int n);//mainly for use in the demo
	vector<Country*> getAllyCountries(Country* c);
	vector<Country*> getEnemyCountries(Country* c);

	void attach(Observer* obs);

private:
	bool** countriesAdj;
	string name;
	int numCountries;
	int numContinents;
	vector<Continent*> *continents;
	vector<Country*> *countries;
	bool isConnected;
	bool continentsValid;// do the continents contain connected countries?
	void setIsConnected(bool b); // ONLY set in checkIsConnected
	void setContinentsValid(bool b); //ONLY set in checkContinentsValid
	void visitingMap(int x, int *a);//helper function for checkIsConnected 
	void visitingContinent(int x, bool **b, int *a, int aSize);//helper function for checkContinentsValid

	
};


