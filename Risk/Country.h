#ifndef COUNTRY_H
#define COUNTRY_H

#include <string>

class Player;

class Country {

private:

	// data members
	std::string name;
	int id;
	Player* owner; 
	Country** adjacencies;
	int numOfAdjacencies;
	int numOfArmies;


public: 

	// Constructors
	Country();
	Country(std::string aName, int aID, Player* player);
	Country(std::string aName, int aID, Player* player, Country* adjacencies, int numOfArmies);

	// Mutators
	void setName(std::string aName);
	void setID(int ID);
	void setOwner(Player* player);
	void setAdjacencies(Country** countries, int num);
	void setNumOfArmies(int num);

	// Accessors
	std::string getName();
	int getID();
	Player* getOwner();
	Country** getAdjacencies();
	int getNumOfAdjacencies();
	int getNumOfArmies();



	

};

#endif