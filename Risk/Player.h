#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Country;

class Player {

private:

	// data members
	std::string name; 					// player's name
	Country** ownedCountries;		// collection of counties owned by the player
	int numOfOwnedCountries;		// number of countries owned by player


public:
	
	// Constructors
	Player();
	Player(std::string aName);
	Player(std::string aName, Country** countries, int num);

	// Mutators
	void setOwnedCountries(Country** countries);
	void setName(std::string aName);
	void setNumOwnedCountries(int num);

	// Accessors
	std::string getName();
	Country** getOwnedCountries();
	int getNumOfOwnedCountries(); 

	

};

#endif