#pragma once 

#include "Countries.h"
#include "GamePlayers.h"
#include<vector>
#include <string>
using namespace std;

class Countries;
class GamePlayers;

class Continents{

public:

	//Constructors and destructor

	Continents();
	Continents(const string continentName, const int numCountries, int numArmies, vector<Countries*> countries, GamePlayers* continentOwner);
	~Continents();


	//Accessors

	string getName();
	int getTotalNumOfCountries();
	int getTotalNumOfArmies();
	GamePlayers *getOwner();

	//Mutators

	void setTotalNumArmies(int newNumArmies);
	void setOwner(GamePlayers* newOwner);


private:

	std::string name;
	int totalNumOfArmies;
	int totalNumCountries;
	std::vector<Countries*> countriesInContinent;
	GamePlayers* owner;


};