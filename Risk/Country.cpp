#include "Country.h"



// Constructors
Country::Country() {

}

Country::Country(std::string aName, int aID, Player* player): name(aName), id(aID), owner(player) {

}

Country::Country(std::string aName, int aID, Player* player, Country* countries, int num) : name(aName), id(aID), owner(player), adjacencies(&countries), numOfArmies(num) {

}

// Mutators

void Country::setName(std::string aName) {
	name = aName;
}

void Country::setID(int aID) {
	id = aID;
}

void Country::setOwner(Player* player) {
	owner = player;
}

void Country::setAdjacencies(Country** countries, int num) {
	adjacencies = countries;
	numOfAdjacencies = num;
}


void Country::setNumOfArmies(int num) {
	numOfArmies = num;
}

// Accessors

std::string Country::getName() {
	return name;
}

int Country::getID() {
	return id;
}

Player* Country::getOwner() {
	return owner;
}

Country** Country::getAdjacencies() {
	return adjacencies;
}

int Country::getNumOfAdjacencies() {
	return numOfAdjacencies;
}

int Country::getNumOfArmies() {
	return numOfArmies;
}

