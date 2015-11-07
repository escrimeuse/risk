#pragma once

#include"Subject.h"
#include "Countries.h"
#include "Continents.h"
#include <string>
#include<vector>
using namespace std;

class Continents;
class Countries;
class Subject;


enum Colours { BLUE, RED, GREEN, YELLOW, PURPLE, ORANGE };
int MINIMUM_NUM_OF_PLAYERS = 2;
int MAXIMUM_NUM_OF_PLAYERS = 6;

class GamePlayers: public Subject{

public:

	//Constructors and destructor

	GamePlayers();
	GamePlayers(string playersName, const int playersID, int playersTurn);
	GamePlayers(Colours col, int numCountries, int numContinents);
	GamePlayers(int numReinforcements, int numBattlesWon, int totalNumArmies);
	~GamePlayers();


	//Accessor functions

	string getPlayersName();
	int getPlayersID();
	int getTurn();
	Colours getColour();
	int getNumCountries();
	vector<Countries*> GamePlayers::getPlayersCountries();
	int getNumContinents();
	vector<Continents*> GamePlayers::getPlayersContinents();
	int getNumReinforcements();
	int getBattlesWon();
	int getTotalNumArmies();

	//Mutator functions
	void setTurn(int newTurn);
	void setNumCountries(int newNumCountries);
	void setNumContinents(int  newNumContinents);
	void setNumReinforcements(int newNumReinforcements);
	void setBattlesWon(int newNumBattlesWon);
	void setTotalNumArmies(int newNumArmies);

	bool isActive();
	void addCountry(Countries* country);
	void removeCountry(Countries* country);
	bool hasCountry(string countryName);
	void addContinent(Continents* continent);
	void removeContinent(Continents* continent);
	int roll();
	virtual void Notify(GamePlayers* p);



private:

	string name;
	int id;
	int turn;
	Colours assignedColour;
	int numOwnedCountries;
	vector<Countries*> listOfOwnedCountries;
	int numOwnedContinents;
	vector<Continents*> listOfOwnedContinents;
	int reinforcements;
	int battlesWon;
	int armies;
};
