// Assignment #2 - COMP345 - Section DI - Fall 2015
// Author: Jennifer Sunahara (27590628)
//
//This is the header file Country.h. This is the interface for the class Country.
//Values of this type are countries, which have an id number, a name, an owner and
//some number of armies.

#pragma once
#include<string>
#include "Player.h"

using namespace std;

class Country {
	friend class SaverLoader;

public:
	Country(); // id is set automatically with static int countryCount
	Country(string aname, int aid, int aarmies, bool aowned, Player* o);
	string getName() const;
	Player* getOwner() const;
	bool getIsOwned() const;
	int getArmies() const;
	int getId() const;
	void setName(string n); 
	void setOwner(Player* o);//string for now, will be a real Player class later
	void setArmies(int a); 
	static int getCount();
	static void resetCount();//this method only exists for demo purposes (to reset the countryCount to 0 when a new menu option is selected)

private:
	static int countryCount; //number of existing countries
	int id; 
	string name;
	bool isOwned;
	Player* owner;; //string for now, will be a real Player class later
	void setIsOwned(bool o);//set to true in setOwner only
	int armies; //number of armies in a country
	
};