#include <iostream>
#include "Player.h"
#include "Country.h"
#include "Continent.h"

using namespace std;

int main() {
	Country* country1 = new Country();
	Country* country2 = new Country();
	country1->setName("Canada");
	country2->setName("USA");
	country1->setArmies(2);
	country2->setArmies(7);

	Player* player1 = new Player("Rick");
	country1->setOwner(player1);
	country2->setOwner(player1);

	player1->addOwnedContinent(new Continent());
	player1->addOwnedCountry(country1);
	player1->addOwnedCountry(country2);

	player1->addPlayerCard(new Card("Canada", infantry));
	player1->addPlayerCard(new Card("Mexico", infantry));
	player1->addPlayerCard(new Card("China", infantry));
	player1->addPlayerCard(new Card("USA", cavalry));
	player1->addPlayerCard(new Card("Japan", cavalry));
	player1->addPlayerCard(new Card("Australia", cavalry));
	player1->addPlayerCard(new Card("England", artillery));
	player1->addPlayerCard(new Card("France", wild));

	player1->reinforceCountries();

}