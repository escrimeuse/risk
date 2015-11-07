#include "GamePlayers.h"
#include "Countries.h"
#include <iostream>
#include <string>



Countries::Countries(){
}

Countries::Countries(const int value){
	countryValue = value;
}

Countries::Countries(const std::string name, const std::string continentName, int numberOfArmies, GamePlayers* gp){
	country = name;
	continent = continentName;
	numArmies = numberOfArmies;
	owner = gp;
}

Countries::~Countries() {

}



inline std::string Countries::getCountryName(){
	return country;
}

inline int Countries::getNumArmies(){
	return numArmies;
}

inline GamePlayers* Countries::getOwner(){
	return owner;
}



void Countries::setNumArmies(int newArmies){
	numArmies = newArmies;
}

void Countries::setOwner(GamePlayers* newOwner){
	owner = newOwner;
}




bool Countries::isOccupied(){
	if (owner != NULL)
		return true;
	return false;
}