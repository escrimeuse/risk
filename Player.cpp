#include "Player.h"
#include "Continent.h"
#include "Country.h"
#include <iostream>
#include <algorithm>

using namespace std;

int Player::numCardSetsTradedIn = 0;	// initialized to zero at the beginning of the game, as there have not been any card sets traded in yet


//Definition of class constructors
Player::Player() : name(NULL), ownedCountries(new list<Country*>), ownedContinents(new list<Continent*>), numOfOwnedCountries(0), numOfOwnedContinents(0), numCardsArtillery(0), numCardsCavalry(0), numCardsInfantry(0), playersArtilleryCards(new list<Card*>), playersCavalryCards(new list<Card*>), playersInfantryCards(new list<Card*>), playersWildCards(new list<Card*>) {

}

Player::Player(std::string playersName) : name(playersName), ownedCountries(new list<Country*>), ownedContinents(new list<Continent*>), numOfOwnedCountries(0), numOfOwnedContinents(0), numCardsArtillery(0), numCardsCavalry(0), numCardsInfantry(0), playersArtilleryCards(new list<Card*>), playersCavalryCards(new list<Card*>), playersInfantryCards(new list<Card*>), playersWildCards(new list<Card*>) {

}

Player::Player(std::string playersName, Colours col) : name(playersName),  assignedColour(col),ownedCountries(new list<Country*>), ownedContinents(new list<Continent*>), numOfOwnedCountries(0), numOfOwnedContinents(0), numCardsArtillery(0), numCardsCavalry(0), numCardsInfantry(0), playersArtilleryCards(new list<Card*>), playersCavalryCards(new list<Card*>), playersInfantryCards(new list<Card*>), playersWildCards(new list<Card*>) {

};

Player::Player(std::string playersName, list<Country*> *countries, list<Continent*> *continents, int num, int art, int cav, int infan) : name(playersName), ownedCountries(countries), ownedContinents(continents), numCardsArtillery(art), numCardsCavalry(cav), numCardsInfantry(infan), playersArtilleryCards(new list<Card*>), playersCavalryCards(new list<Card*>), playersInfantryCards(new list<Card*>), playersWildCards(new list<Card*>) {
	numOfOwnedCountries = ownedCountries->size();
	numOfOwnedContinents = ownedContinents->size();
};

//Definition of class destructor
Player::~Player() {
	delete ownedCountries;
	delete ownedContinents;
	delete playersInfantryCards;
	delete playersCavalryCards;
	delete playersArtilleryCards;
	delete playersWildCards;
}

//Private accessor function getCountry definition
Country* Player::getCountry(int id) {
	for (list<Country*>::iterator i = ownedCountries->begin(); i != ownedCountries->end(); ++i) {
		if ((*i)->getId() == id) {
			return (*i);
		}
	}

	return NULL;
}

//Private accessor function getCard definition
Card* Player::getCard(string name) {
	string lowercaseName = "";

	// convert to lowercase
	for (int i = 0; i < name.length(); ++i) {
		lowercaseName += name.substr(i, 1);
	}

	// search through artillery cards
	for (list<Card*>::iterator i = playersArtilleryCards->begin(); i != playersArtilleryCards->end(); ++i) {

		string lowercaseCountry = "";
		// convert to lowercase
		for (int j = 0; j < ((*i)->getCountryOnCard()).length(); ++j) {
			lowercaseCountry += ((*i)->getCountryOnCard()).substr(j, 1);
		}

		if (lowercaseCountry.compare(lowercaseName) == 0) {
			return (*i);
		}

	}

	//search through cavalry cards
	for (list<Card*>::iterator i = playersCavalryCards->begin(); i != playersCavalryCards->end(); ++i) {

		string lowercaseCountry = "";
		// convert to lowercase
		for (int j = 0; j < ((*i)->getCountryOnCard()).length(); ++j) {
			lowercaseCountry += ((*i)->getCountryOnCard()).substr(j, 1);
		}

		if (lowercaseCountry.compare(lowercaseName) == 0) {
			return (*i);
		}

	}

	//search through infantry cards
	for (list<Card*>::iterator i = playersInfantryCards->begin(); i != playersInfantryCards->end(); ++i) {

		string lowercaseCountry = "";
		// convert to lowercase
		for (int j = 0; j < ((*i)->getCountryOnCard()).length(); ++j) {
			lowercaseCountry += ((*i)->getCountryOnCard()).substr(j, 1);
		}

		if (lowercaseCountry.compare(lowercaseName) == 0) {
			return (*i);
		}

	}

	//search through wild cards
	for (list<Card*>::iterator i = playersWildCards->begin(); i != playersWildCards->end(); ++i) {

		string lowercaseCountry = "";
		// convert to lowercase
		for (int j = 0; j < ((*i)->getCountryOnCard()).length(); ++j) {
			lowercaseCountry += ((*i)->getCountryOnCard()).substr(j, 1);
		}

		if (lowercaseCountry.compare(lowercaseName) == 0) {
			return (*i);
		}

	}


	return NULL;
}

void Player::addOwnedCountry(Country* countryToAdd) {

	bool countryAlreadyOwned = false;

	// first checks if the country is already owned
	for (list<Country*>::iterator i = ownedCountries->begin(); i != ownedCountries->end(); i++) {
		if ((*i)->getName() == countryToAdd->getName()) {
			countryAlreadyOwned = true;
		};
	};

	// if the country is not already owned, add it to the list of owned countries
	if (!countryAlreadyOwned) {
		ownedCountries->push_back(countryToAdd);
	};

}

void Player::addOwnedContinent(Continent* continentToAdd) {

	bool continentAlreadyOwned = false;

	// first check if continent is already owned
	for (list<Continent*>::iterator i = ownedContinents->begin(); i != ownedContinents->end(); ++i) {
		if ((*i)->getName() == continentToAdd->getName()) {
			continentAlreadyOwned = true;
		};
	};

	// if the continent is not already owned, add it to the list of owned continents
	if (!continentAlreadyOwned) {
		ownedContinents->push_back(continentToAdd);
	};

}

void Player::removeOwnedCountry(string countryName) {

	Country* countryNode = NULL;

	// find the country in the list
	for (list<Country*>::iterator i = ownedCountries->begin(); i != ownedCountries->end(); ++i) {
		if ((*i)->getName() == countryName) {
			countryNode = *i;
		};
	};

	// if the country was found, remove it
	if (countryNode != NULL) {
		ownedCountries->remove(countryNode);
	};

}

void Player::removeOwnedContinent(string continentName) {

	Continent* continentNode = NULL;

	// find the continent in the list
	for (list<Continent*>::iterator i = ownedContinents->begin(); i != ownedContinents->end(); ++i) {
		if ((*i)->getName() == continentName) {
			continentNode = *i;
		};
	};

	// if the continent was found, remove it
	if (continentNode != NULL) {
		ownedContinents->remove(continentNode);
	};

}

void Player::addPlayerCard(Card* newCard) {
	if (newCard->getTypeOfCard() == infantry) {
		playersInfantryCards->push_back(newCard);
		numCardsInfantry++;
	}
	else if (newCard->getTypeOfCard() == artillery) {
		playersArtilleryCards->push_back(newCard);
		numCardsArtillery++;
	}
	else if (newCard->getTypeOfCard() == cavalry) {
		playersCavalryCards->push_back(newCard);
		numCardsCavalry++;
	}
	else {
		playersWildCards->push_back(newCard);
		numCardsWild++;
	}

};

void Player::removePlayerCard(Card* removeCard) {
	if (removeCard->getTypeOfCard() == infantry) {
		playersInfantryCards->remove(removeCard);
		numCardsInfantry--;
	}
	else if (removeCard->getTypeOfCard() == artillery) {
		playersArtilleryCards->remove(removeCard);
		numCardsArtillery--;
	}
	else if (removeCard->getTypeOfCard() == cavalry) {
		playersCavalryCards->remove(removeCard);
		numCardsCavalry--;
	}
	else {
		playersWildCards->remove(removeCard);
		numCardsWild--;
	}

};

bool Player::validateCountryIDSelection(int id) {

	for (list<Country*>::iterator i = ownedCountries->begin(); i != ownedCountries->end(); ++i) {
		if ((*i)->getId() == id) {
			return true;
		}
	}

	return false;
}

bool Player::validateCardSelection(string name) {

	string lowercaseName = "";

	// convert to lowercase
	for (int i = 0; i < name.length(); ++i) {
		lowercaseName += name.substr(i, 1);
	}

	// search through artillery cards
	for (list<Card*>::iterator i = playersArtilleryCards->begin(); i != playersArtilleryCards->end(); ++i) {

		string lowercaseCountry = "";
		// convert to lowercase
		for (int j = 0; j < ((*i)->getCountryOnCard()).length(); ++j) {
			lowercaseCountry += (*i)->getCountryOnCard().substr(j, 1);
		}

		if (lowercaseCountry.compare(lowercaseName) == 0) {
			return true;
		}

	}

	//search through cavalry cards
	for (list<Card*>::iterator i = playersCavalryCards->begin(); i != playersCavalryCards->end(); ++i) {

		string lowercaseCountry = "";
		// convert to lowercase
		for (int j = 0; j < ((*i)->getCountryOnCard()).length(); ++j) {
			lowercaseCountry += (*i)->getCountryOnCard().substr(j, 1);
		}

		if (lowercaseCountry.compare(lowercaseName) == 0) {
			return true;
		}

	}

	//search through infantry cards
	for (list<Card*>::iterator i = playersInfantryCards->begin(); i != playersInfantryCards->end(); ++i) {

		string lowercaseCountry = "";
		// convert to lowercase
		for (int j = 0; j < ((*i)->getCountryOnCard()).length(); ++j) {
			lowercaseCountry += (*i)->getCountryOnCard().substr(j, 1);
		}

		if (lowercaseCountry.compare(lowercaseName) == 0) {
			return true;
		}

	}

	//search through wild cards
	for (list<Card*>::iterator i = playersWildCards->begin(); i != playersWildCards->end(); ++i) {

		string lowercaseCountry = "";
		// convert to lowercase
		for (int j = 0; j < ((*i)->getCountryOnCard()).length(); ++j) {
			lowercaseCountry += (*i)->getCountryOnCard().substr(j, 1);
		}

		if (lowercaseCountry.compare(lowercaseName) == 0) {
			return true;
		}

	}


	return false;
}

// this function displays to the screen all the cards owned by the player
void Player::displayCards(cardType type) {

	if (type == infantry) {
		cout << "INFANTRY CARDS: ";
		if (playersInfantryCards->size() == 0) {
			cout << "NONE" << endl;
		}
		else {
			for (list<Card*>::iterator i = playersInfantryCards->begin(); i != playersInfantryCards->end(); ++i) {
				cout << (*i)->getCountryOnCard();

				for (list<Country*>::iterator j = ownedCountries->begin(); j != ownedCountries->end(); ++j) {
					if ((*i)->getCountryOnCard() == (*j)->getName()) {
						cout << "# ";
					}
					else {
						cout << " ";
					}
				}
			}
			cout << endl;
		}
	}
	else if (type == cavalry) {
		cout << "CAVALRY CARDS: ";
		if (playersCavalryCards->size() == 0) {
			cout << "NONE" << endl;
		}
		else {
			for (list<Card*>::iterator i = playersCavalryCards->begin(); i != playersCavalryCards->end(); ++i) {
				cout << (*i)->getCountryOnCard() << " ";

				for (list<Country*>::iterator j = ownedCountries->begin(); j != ownedCountries->end(); ++j) {
					if ((*i)->getCountryOnCard() == (*j)->getName()) {
						cout << "# ";
					}
					else {
						cout << " ";
					}
				}
			}
			cout << endl;
		}
	}
	else if (type == artillery) {
		cout << "ARTILLERY CARDS: ";
		if (playersArtilleryCards->size() == 0) {
			cout << "NONE" << endl;
		}
		else {
			for (list<Card*>::iterator i = playersArtilleryCards->begin(); i != playersArtilleryCards->end(); ++i) {
				cout << (*i)->getCountryOnCard() << " ";

				for (list<Country*>::iterator j = ownedCountries->begin(); j != ownedCountries->end(); ++j) {
					if ((*i)->getCountryOnCard() == (*j)->getName()) {
						cout << "# ";
					}
					else {
						cout << " ";
					}
				}
			}
			cout << endl;
		}
	}
	else if (type == wild) {
		cout << "WILD CARDS: ";
		if (playersWildCards->size() == 0) {
			cout << "NONE" << endl;
		}
		else {
			for (list<Card*>::iterator i = playersWildCards->begin(); i != playersWildCards->end(); ++i) {
				cout << (*i)->getCountryOnCard() << " ";
			}
			cout << endl;
		}
	}

}

// this function drives the reinforcement phase. It calculates the number of armies that can be placed, and allows the user to select where the armies are added
void Player::reinforceCountries() {

	// step 1: determine total number of armies
	// ============================================================================

	int totalNumArmies = 0;

	// at the baseline, the number of armies available for reinforcement is equal to the floor of the number of countries owned divided by 3
	totalNumArmies += static_cast<int>(floor(numOfOwnedCountries / 3));
	if (totalNumArmies < 3) {
		totalNumArmies = 3;
	}

	// next, we check if the player owns any continents
	// if they own any continents, then we add the continent's control value to the number of armies available for reinforcement
	if (ownedContinents->size() != 0) {
		for (list<Continent*>::iterator i = ownedContinents->begin(); i != ownedContinents->end(); ++i) {
			totalNumArmies += (*i)->getControlValue();
		}
	}

	// now we check the player cards
	// if the player has 3 cards of the same type, or 3 cards of different types, or 1 wild card plus two of any other type, then 
	// they can trade the cards in for armies
	Card* cardOne = NULL;
	Card* cardTwo = NULL;
	Card* cardThree = NULL;
	bool startOfReinforcementPhase = true;
	while (numCardsArtillery + numCardsInfantry + numCardsCavalry + numCardsWild >= 3) {


		bool hasSetArtillery = false;
		bool hasSetCavalry = false;
		bool hasSetInfantry = false;
		bool hasSetDifferentTypes = false;
		bool hasWildCardSet = false;

		if (numCardsArtillery >= 3) {
			hasSetArtillery = true;
		};

		if (numCardsCavalry >= 3) {
			hasSetCavalry = true;
		};

		if (numCardsInfantry >= 3) {
			hasSetInfantry = true;
		};

		if (numCardsArtillery >= 1 && numCardsCavalry >= 1 && numCardsInfantry > 1) {
			hasSetDifferentTypes = true;
		};

		if (numCardsWild >= 1 && (numCardsArtillery + numCardsCavalry + numCardsInfantry >= 2)) {
			hasWildCardSet = true;
		};

		if (hasSetArtillery || hasSetCavalry || hasSetInfantry || hasSetDifferentTypes || hasWildCardSet) {

			cout << name << ", you have the following cards (# indicates that you also own that country): " << endl;
			displayCards(infantry);
			displayCards(cavalry);
			displayCards(artillery);
			displayCards(wild);

			// as per Risk rules, if the number of cards in a player's possession at the beginning of the reinforcement
			// phase is 5 ot 6, then they MUST exchange at least 3 of their cards for armies
			if (!(startOfReinforcementPhase &&
				(numCardsArtillery + numCardsCavalry + numCardsInfantry + numCardsWild == 6 ||
					numCardsArtillery + numCardsCavalry + numCardsInfantry + numCardsWild == 5))) {
				cout << "Would you like to exchange cards for armies (Y or N)? ";
				char exchangeForArmies;
				cin >> exchangeForArmies;
				if (exchangeForArmies == 'N' || exchangeForArmies == 'n') {
					cout << "You chose to not exchange cards for armies." << endl;
					break;
				}
			}


			bool validSetSelected = false;
			while (!validSetSelected) {

				cout << endl;
				cout << "Enter the country name of the cards you would like to exchange. Do not include the # symbol if present. Note that cards "
					<< " with # next to them are worth 2 extra armies, which will be automatically placed on that country." << endl;
				cout << "Card 1: ";
				string card1, card2, card3;
				cin >> card1;

				while (!validateCardSelection(card1)) {
					cout << "ERROR: Card entered not valid. Please enter card name again: ";
					cin >> card1;
				}
				cardOne = getCard(card1);

				cout << "Card 2: ";
				cin >> card2;
				while (!validateCardSelection(card2)) {
					cout << "ERROR: Card entered not valid. Please enter card name again: ";
					cin >> card2;
				}
				cardTwo = getCard(card2);

				cout << "Card 3: ";
				cin >> card3;
				while (!validateCardSelection(card3)) {
					cout << "ERROR: Card entered not valid. Please enter card name again: ";
					cin >> card3;
				}
				cardThree = getCard(card3);

				// now validate that the cards belog to one of the following sets:
				// 1 - all cards of the same type
				// 2 - all cards are of a different type
				// 3 - one wild card plus two cards of any type


				if (cardOne->getTypeOfCard() == cardTwo->getTypeOfCard() && cardTwo->getTypeOfCard() == cardThree->getTypeOfCard()) {
					validSetSelected = true;
				}
				else if (cardOne->getTypeOfCard() != cardTwo->getTypeOfCard() && cardTwo->getTypeOfCard() != cardThree->getTypeOfCard()) {
					validSetSelected = true;
				}
				else if (cardOne->getTypeOfCard() == wild || cardTwo->getTypeOfCard() == wild || cardThree->getTypeOfCard() == wild) {
					validSetSelected = true;
				}

				if (!validSetSelected) {
					cout << "ERROR: Invalid set of cards selected. You must select three cards of the same card type, or " << endl;
					cout << "three cards of different card types, or one wild card and two cards of any type." << endl;
					cout << "Please select your cards again." << endl;
				}

			}

		}
		else {
			cout << "Sorry, you have no exchangable card sets right now!" << endl;
			break;
		}

		// now that we have a valid selection, we will exchange the cards for armies 

		// first we need to check if any other players have exchanged cards yet. As per Risk rules, the number of armies that a 
		// player will get for cards is first 5, then increases by 5 every time any player exchanges cards

		totalNumArmies += 5;
		totalNumArmies += 5 * getNumCardSetsTradedIn();
		setNumCardSetsTradedIn(getNumCardSetsTradedIn() + 1);
		cout << "Exchanging the following cards for " << 5 * getNumCardSetsTradedIn() << " armies: " << endl;
		cout << "CARD 1: " << cardOne->getCountryOnCard() << endl;
		cout << "CARD 2: " << cardTwo->getCountryOnCard() << endl;
		cout << "CARD 3: " << cardThree->getCountryOnCard() << endl;
		removePlayerCard(cardOne);
		removePlayerCard(cardTwo);
		removePlayerCard(cardThree);

		// now, determine if the player owns any of the countries that appear on the cards that they just traded in 
		// as per Risk rules, if the player owns any of the countries that appear on the the cards, then they get +2 armies,
		// which must be placed on the country in question

		for (list<Country*>::iterator i = ownedCountries->begin(); i != ownedCountries->end(); ++i) {
			if (cardOne->getCountryOnCard() == (*i)->getName()) {
				(*i)->setArmies(((*i)->getArmies() + 2));
				cout << "Automatically adding 2 armies to " << (*i)->getName() << endl;
			}
			if (cardTwo->getCountryOnCard() == (*i)->getName()) {
				(*i)->setArmies(((*i)->getArmies() + 2));
				cout << "Automatically adding 2 armies to " << (*i)->getName() << endl;
			}
			if (cardThree->getCountryOnCard() == (*i)->getName()) {
				(*i)->setArmies(((*i)->getArmies() + 2));
				cout << "Automatically adding 2 armies to " << (*i)->getName() << endl;
			}
		}


		cout << "Would you like to exchange more card sets for armies (Y/N)? ";
		char exchangeMore;
		cin >> exchangeMore;
		if (exchangeMore == 'y' || exchangeMore == 'Y') {
			continue;
		}
		else {
			break;
		}

		startOfReinforcementPhase = false;

	}

	if (numCardsArtillery + numCardsInfantry + numCardsCavalry + numCardsWild <3) {
		cout << "Sorry, you have no exchangable card sets right now." << endl;
	}

	// Step 2: user-driven placement of armies


	placeArmiesOnCountriesLoop(totalNumArmies);

	cout << "Completed reinforcement phase for " << getName() << endl;
	cout << "The number of armies on each country for " << getName() << " is as follows: " << endl;
	cout << "COUNTRY ID\tCOUNTRY NAME\tCURRENT # OF ARMIES" << endl;
	for (list<Country*>::iterator i = ownedCountries->begin(); i != ownedCountries->end(); ++i) {
		cout << (*i)->getId() << "\t\t" << (*i)->getName() << "\t\t" << (*i)->getArmies() << endl;
	}



};



void Player::placeArmiesOnCountriesLoop(int totalNumArmies) {

	while (totalNumArmies != 0) {
		cout << "You have " << totalNumArmies << " armies to place on any of the following countries: " << endl;
		cout << "COUNTRY ID\tCOUNTRY NAME\tCURRENT # OF ARMIES" << endl;
		for (list<Country*>::iterator i = ownedCountries->begin(); i != ownedCountries->end(); ++i) {
			cout << (*i)->getId() << "\t\t" << (*i)->getName() << "\t\t" << (*i)->getArmies() << endl;
		}
		cout << endl;
		cout << "Type the ID of the country you would like to place armies on: " << endl;
		int countryID = -1;
		int numArmiesToPlaceOnCountry = -1;
		cin >> countryID;

		while (!validateCountryIDSelection(countryID)) {
			cout << "ERROR: Invalid country ID entered. Please enter the ID of the country again: ";
			cin >> countryID;
		}
		cout << endl;
		cout << "Type the number of armies that you would like to place on the selected country: " << endl;
		cin >> numArmiesToPlaceOnCountry;
		while (numArmiesToPlaceOnCountry > totalNumArmies || numArmiesToPlaceOnCountry < 0) {
			cout << "ERROR: The number of armies is invalid. Please enter the number of armies again: ";
			cin >> numArmiesToPlaceOnCountry;
		}

		Country* country = getCountry(countryID);
		country->setArmies(country->getArmies() + numArmiesToPlaceOnCountry);
		totalNumArmies -= numArmiesToPlaceOnCountry;
		cout << numArmiesToPlaceOnCountry << " armies have been placed on " << country->getName() << endl;
	}

}

Country* Player::getCountryById(int id) {
	for (list<Country*>::iterator i = ownedCountries->begin(); i != ownedCountries->end(); ++i) {
		if ((*i)->getId() == id)
			return (*i);
	}
	return NULL;
}
