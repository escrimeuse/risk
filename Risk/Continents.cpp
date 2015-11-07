
#include "Continents.h"
#include "GamePlayers.h"
#include "Countries.h"
#include <iostream>
#include<vector>
#include <string>
using namespace std;

Continents::Continents() {

}

Continents::Continents(const string continentName, const int numCountries, int numArmies, vector<Countries*> countries, GamePlayers* continentOwner) {
	name = continentName;
	totalNumOfArmies = numCountries;
	totalNumCountries = numArmies;
	countriesInContinent = countries;
	owner = continentOwner;
}

Continents::~Continents() {
}


string Continents::getName() {
	return name;
}

int Continents::getTotalNumOfCountries() {
	return totalNumCountries;

}

int Continents::getTotalNumOfArmies() {
	return totalNumOfArmies;
}
GamePlayers* Continents::getOwner() {
	return owner;

}

void Continents::setTotalNumArmies(int newNumArmies) {
	totalNumOfArmies = newNumArmies;
}


void Continents::setOwner(GamePlayers* newOwner) {
	owner = newOwner;
}
