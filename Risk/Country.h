#ifndef COUNTRY_H
#define COUNTRY_H

#include <string>

class Player;

class Country {

private:

	// DATA MEMBERS
	std::string name;	// name of the country
	int id;				// country ID
	Player* owner;		// pointer to the owner of the country
	Country** adjacencies;	// an array of the adjacent countries
	int numOfAdjacencies;	// the number of adjacent countries
	int numOfArmies;		// the number of armies on the country


public: 

	// Constructors
	// Note: Constructions were implemented as inline due to their simple, single-line code
	Country() {

	}
	Country(std::string aName, int aID, Player* player) : name(aName), id(aID), owner(player) {

	}
	Country(std::string aName, int aID, Player* player, Country* countries, int num) : name(aName), id(aID), owner(player), adjacencies(&countries), numOfArmies(num) {

	}

	// Mutators
	// Note: Mutators were implemented as inline due to their simple, single-line code
	void setName(std::string aName) {
		name = aName;
	}
	void setID(int aID) {
		id = aID;
	}
	void setOwner(Player* player) {
		owner = player;
	}
	void setAdjacencies(Country** countries, int num) {
		adjacencies = countries;
		numOfAdjacencies = num;
	}
	void setNumOfArmies(int num) {
		numOfArmies = num;
	}

	// Accessors
	// Note: Accessors were implemented as inline due to their simple, single-line code
	std::string getName() const {
		return name;
	}
	int getID() const  {
		return id;
	}
	Player* getOwner() const {
		return owner;
	}
	Country** getAdjacencies() const {
		return adjacencies;
	}
	int getNumOfAdjacencies() const {
		return numOfAdjacencies;
	}
	int getNumOfArmies() const {
		return numOfArmies;
	}


	

};

#endif