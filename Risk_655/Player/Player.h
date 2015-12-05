#pragma once

#include <string>
#include <list>
#include "Card.h"
#include "../ObserverPattern/Subject.h"

class Continent;
class Country;
class Strategy;

enum Colours { BLUE, RED, GREEN, YELLOW, PURPLE, ORANGE };


class Player : public Subject{

public:

	//Constructors and destructor

	Player();
	Player(std::string playersName);
	Player::Player(std::string playersName, int strategyId);
	Player(std::string playersName, Colours col);
	Player(std::string playersName, list<Country*> *countries, list<Continent*> *continents, int num, int art, int cav, int infan);
	~Player();

	//Mutator functions
	void setTurn(int newTurn) {
		turn = newTurn;
	};

	void setTotalNumArmies(int newNumArmies) {
		armies = newNumArmies;
		notify(ARMIES_ID);
		notify(0);
	};

	void setOwnedCountries(list<Country*> *countries) {
		ownedCountries = countries;
	};
	void setOwnedContinents(list<Continent*> *continents) {
		ownedContinents = continents;
	};
	void setName(std::string playersName) {
		name = playersName;
	};
	void setNumOwnedCountries(int newNumCountries) {
		numOfOwnedCountries = newNumCountries;
	};
	void setNumOwnedContinents(int  newNumContinents) {
		numOfOwnedContinents = newNumContinents;
	};
	void setNumCardsInfantry(int newNumInfantry) {
		numCardsInfantry = newNumInfantry;
	};
	void setNumCardsArtillery(int newNumInfantry) {
		numCardsArtillery = newNumInfantry;
	};
	void setNumCardsCavalry(int newNumCavalry) {
		numCardsCavalry = newNumCavalry;
	};

	//Accessor functions

	std::string getName() const{
		return name;
	};

	int getTurn() {
		return turn;
	};

	int getNumOfOwnedCountries() const {
		return numOfOwnedCountries;
	};
	int getNumOfOwnedContinents() const {
		return numOfOwnedContinents;
	};
	int getNumCardsInfanty() {
		return numCardsInfantry;
	};
	int getNumCardsCavalry() {
		return numCardsCavalry;
	}
	int getNumCardsArtillery() {
		return numCardsArtillery;
	}
	list<Country*>* getOwnedCountries() const {
		return ownedCountries;
	};
	list<Continent*>* getOwnedContinents() const {
		return ownedContinents;
	};

	int getTotalNumArmies();

	Strategy* getStrategy() {
		return strategy;
	}
	

	bool isActive(){
		if (numOfOwnedCountries != 0)
			return true;
		return false;
	};
	int roll() {
		int num = (1 + rand() % 6);
		return num;
	};
	void addOwnedCountry(Country* newCountry);
	void addOwnedContinent(Continent* newContinent);
	void removeOwnedCountry(std::string countryName);
	void removeOwnedContinent(std::string continentName);
	void reinforceCountries();
	static int getNumCardSetsTradedIn() {
		return numCardSetsTradedIn;
	};
	static void setNumCardSetsTradedIn(int num) {
		numCardSetsTradedIn = num;
	};
	void setPlayersInfantryCards(list<Card*> *infantry) {
		playersInfantryCards = infantry;
	};
	void setPlayersCavalryCards(list<Card*> *cavalry) {
		playersCavalryCards = cavalry;
	};
	void setPlayersArtilleryCards(list<Card*> *artillery) {
		playersArtilleryCards = artillery;
	};
	void setPlayersWildCards(list<Card*> *wild) {
		playersWildCards = wild;
	};
	list<Card*>* getPlayersInfantryCards() {
		return playersInfantryCards;
	};
	list<Card*>* getPlayersCavalryCards() {
		return playersCavalryCards;
	};
	list<Card*>* getPlayersArtilleryCards() {
		return playersArtilleryCards;
	};
	list<Card*>* getPlayersWildCards() {
		return playersWildCards;
	};
	void addPlayerCard(Card* newCard);
	void removePlayerCard(Card* removeCard);
	void displayCards(cardType type);
	void placeArmiesOnCountriesLoop(int num);
	Country* getCountryById(int id);
	bool isComputer();
	void Player::setArmiesInCountry(Country* c, int n);
	bool isAlive();
	void setNumCardsWild(int newNumWild) {
		numCardsWild = newNumWild;
	};
	int getNumCardsWild() {
		return numCardsWild;
	}
	int getNumberBattlesWon() {
		return numberBattlesWon;
	}
	void setNumberBattlesWon(int num) {
		numberBattlesWon = num;
	}

	static const int CARDS_ID = 7638;
	static const int ARMIES_ID = 47184;
	static const int REINFORCEMENT_ID = 12648;
	static const int COUNTRY1_ID = 9823;
	static const int COUNTRY2_ID = 9993;
	static const int STRATEGY_ID = 37762;

private:

	std::string name; 				// player's name
	int turn;
	Colours assignedColour;
	list<Country*> *ownedCountries;		// collection of counties owned by the player
	int numOfOwnedCountries;
	list<Continent*> *ownedContinents;	// collection of continents owned by the player
	int numOfOwnedContinents;
	int armies;
	list<Card*> *playersInfantryCards;	// collection of player's infantry cards
	list<Card*> *playersCavalryCards;	// collection of player's cavalry cards
	list<Card*> *playersArtilleryCards;	// collection of player's artillery cards
	list<Card*> *playersWildCards;	// collection of player's wild cards
	int numCardsInfantry;
	int numCardsCavalry;
	int numCardsArtillery;
	int numCardsWild;
	static int numCardSetsTradedIn;		// total number of card sets traded in across the game
	bool validateCardSelection(string name);
	bool validateCountryIDSelection(int id);
	Card* getCard(string name);		// returns the card corresponding to the name passed as an argument
	void setStrategy(int strategyId);
	Country* getCountry(int id);

	bool computer;				// If player is computer
	Strategy* strategy;

	int numberBattlesWon;	// player's total number of battles won

};

