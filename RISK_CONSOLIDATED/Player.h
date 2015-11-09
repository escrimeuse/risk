#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <list>
#include "Card.h"

class Country;
class Continent;

class Player {

private:

	std::string name; 				// player's name
	list<Country*> *ownedCountries;		// collection of counties owned by the player
	list<Continent*> *ownedContinents;	// collection of continents owned by the player
	int numOfOwnedCountries;		
	int numOfOwnedContinents;		
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
	Country* getCountry(int id);
	static int initalReinforcementNumArmiesPerPlayer;

public:
	
	Player();
	Player(std::string aName);
	Player(std::string aName, list<Country*> *countries, list<Continent*> *continents, int num, int art, int cav, int infan);
	~Player();
	void setOwnedCountries(list<Country*> *countries) {
		ownedCountries = countries;
	};
	void setOwnedContinents(list<Continent*> *continents) {
		ownedContinents = continents;
	};
	void setName(std::string aName) {
		name = aName;
	};
	void setNumOwnedCountries(int num) {
		numOfOwnedCountries = num;
	};
	void setNumOwnedContinents(int num) {
		numOfOwnedContinents = num;
	};
	void setNumCardsInfantry(int num) {
		numCardsInfantry = num;
	};
	void setNumCardsArtillery(int num) {
		numCardsArtillery = num;
	}
	void setNumCardsCavalry(int num) {
		numCardsCavalry = num;
	}
	std::string getName() const{
		return name;
	};
	list<Country*>* getOwnedCountries() const{
		return ownedCountries;
	};
	list<Continent*>* getOwnedContinents() const {
		return ownedContinents;
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
	void addOwnedCountry(Country* newCountry);
	void addOwnedContinent(Continent* newContinent);
	void removeOwnedCountry(string countryName);
	void removeOwnedContinent(string continentName); 
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
	void initialReinforcement();
	static void setInitalReinforcementNumArmiesPerPlayer(int num) {
		initalReinforcementNumArmiesPerPlayer = num;
	}
	void placeArmiesOnCountriesLoop(int num);

	

};

#endif