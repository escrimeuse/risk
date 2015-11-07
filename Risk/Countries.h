#pragma once

#include "GamePlayers.h"
#include <string>
using namespace std;

class GamePlayers;

class Countries {

public:

	//Constructors and destructor

	Countries();
	Countries(const int value);
	Countries(const string name, const string continentName, int numberOfArmies, GamePlayers* gp);
	~Countries();

	//Accessors 

	string getCountryName();
	int getNumArmies();
	GamePlayers* getOwner();

	//Mutators 

	void setNumArmies(int newArmies);
	void setOwner(GamePlayers* newOwner);



	bool isOccupied();


private:

	string country;
	int countryValue;
	string continent;
	int numArmies;
	GamePlayers* owner;

};










