
#include "GamePlayers.h"
#include "Countries.h"
#include "Continents.h"
#include <string>
#include<iostream>

GamePlayers::GamePlayers(){
}

GamePlayers::GamePlayers(const string playersName, const int playersID, int playersTurn){
	name = playersName;
	id = playersID;
	turn = playersTurn;
	reinforcements = 25;
}

GamePlayers::GamePlayers(Colours col, int numCountries, int numContinents){
	assignedColour = col;
	numOwnedCountries = numCountries;
	numOwnedContinents = numContinents;
}
GamePlayers::GamePlayers(int numReinforcements, int numBattlesWon, int totalNumArmies){
	reinforcements = numReinforcements;
	battlesWon = numBattlesWon;
	armies = totalNumArmies;
}

GamePlayers::~GamePlayers() {

}

inline string GamePlayers::getPlayersName() {
	return name;
}
inline int GamePlayers::getPlayersID() {
	return id;
}
inline int GamePlayers::getTurn() {
	return turn;
}
inline Colours GamePlayers::getColour() {
	return assignedColour;
}
inline int GamePlayers::getNumCountries() {
	return numOwnedCountries;
}
inline vector<Countries*> GamePlayers::getPlayersCountries() {
	return listOfOwnedCountries;
}

inline int GamePlayers::getNumContinents() {
	return numOwnedContinents;
}
inline vector<Continents*> GamePlayers::getPlayersContinents() {
	return listOfOwnedContinents;
}

inline int GamePlayers::getNumReinforcements() {
	return reinforcements;
}
inline int GamePlayers::getBattlesWon() {
	return battlesWon;
}
inline int GamePlayers::getTotalNumArmies() {
	return armies;
}

void GamePlayers::setTurn(int newTurn){
	turn = newTurn;
	Notify(this);
}
void GamePlayers::setNumCountries(int newNumCountries){
	numOwnedCountries = newNumCountries;
	Notify(this);
}
void GamePlayers::setNumContinents(int  newNumContinents){
	numOwnedContinents = newNumContinents;
	Notify(this);
}
void GamePlayers::setNumReinforcements(int newNumReinforcements){
	reinforcements = newNumReinforcements;
	Notify(this);
}
void GamePlayers::setBattlesWon(int newNumBattlesWon) {
	battlesWon = newNumBattlesWon;
	Notify(this);
}
void GamePlayers::setTotalNumArmies(int newNumArmies) {
	armies = newNumArmies;
	Notify(this);
}



bool GamePlayers::isActive() {
	if ((numOwnedCountries != 0)||(armies != 0))
		return true;
	return false;
}
void GamePlayers::addCountry(Countries* country) {
	listOfOwnedCountries.push_back(country);
	Notify(this);
}
void GamePlayers::removeCountry(Countries* country) {
	for (int i = 0; i < listOfOwnedCountries.size(); i++) {
		if (listOfOwnedCountries[i] == country)
			listOfOwnedCountries.erase(listOfOwnedCountries.begin() + i);
	}
	Notify(this);
}

bool GamePlayers::hasCountry(string countryName) {
	for (unsigned int i = 0; i < numOwnedCountries; i++) {
		if (listOfOwnedCountries[i]->getCountryName() == countryName)
			return true;
	}
	return false;
}

void GamePlayers::addContinent(Continents* continent) {
	listOfOwnedContinents.push_back(continent);
	Notify(this);
}
void GamePlayers::removeContinent(Continents* continent) {
	for (int i = 0; i < listOfOwnedContinents.size(); i++) {
		if (listOfOwnedContinents[i] == continent)
			listOfOwnedContinents.erase(listOfOwnedContinents.begin() + i);
	}
	Notify(this);
}


int GamePlayers::roll() {
	int num = (1 + rand() % 6);
	return num;
}

