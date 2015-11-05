#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Country;

class Player {

private:

	// DATA MEMBERS
	std::string name; 				// player's name
	Country** ownedCountries;		// collection of counties owned by the player
	int numOfOwnedCountries;		// number of countries owned by player


public:
	
	// Constructors 
	// Note: Constructions were implemented as inline due to their simple, single-line code
	Player() {

	}
	Player(std::string aName) : name(aName) {

	}
	Player(std::string aName, Country** countries, int num) : name(aName), ownedCountries(countries), numOfOwnedCountries(num) {

	}


	// Mutators
	// Note: Mutators were implemented as inline due to their simple, single-line code
	void setOwnedCountries(Country** countries) {
		ownedCountries = countries;
	}
	void setName(std::string aName) {
		name = aName;
	}
	void setNumOwnedCountries(int num) {
		numOfOwnedCountries = num;
	}


	// Accessors
	// Note: Accessors were implemented as inline due to their simple, single-line code
	std::string getName() const{
		return name;
	}
	Country** getOwnedCountries() const{
		return ownedCountries;
	}
	int getNumOfOwnedCountries() const {
		return numOfOwnedCountries;
	}


	

};

#endif