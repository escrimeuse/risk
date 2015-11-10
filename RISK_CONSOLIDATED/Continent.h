// Assignment #1 - COMP345 - Section DI - Fall 2015
// Author: Jennifer Sunahara (27590628)
//
//This is the header file Continent.h. This is the interface for the class Continent.
//Values of this type are continents, which have an id number, a name, an owner and
//a list of countries. 
//Note that the notion of connectivity and of exclusive country membership is implemented in the map.
#pragma once
#include<string>
#include<vector>

using namespace std;
#include "Player.h"
#include "Country.h"

class Continent {
public:
	Continent(); //  id is set automatically with static int continentCount
	Continent(string aname, int numC, int id, int controlValue); 
	string getName() const;
	Player* getOwner() const;
	bool getIsOwned() const;
	int getNumCountries() const;
	string getCountryNames() const;
	void setName(string n);
	void setOwner(Player* o);
	static int getCount();
	void addCountry(Country* c);
	static void resetCount();//this method only exists for demo purposes (to reset the continentCount to 0 when a new menu option is selected)
	int getControlValue();

private:
	static int continentCount;//number of existing continents
	int id; 
	string name;
	vector<Country*> *countries;
	int numCountries;
	bool isOwned;
	Player* owner; 
	void setIsOwned(bool o);//set to true in setOwner
	int controlValue; 
};