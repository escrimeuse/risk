#include "PlayerView.h"
#include <iostream>
#include <fstream>

using namespace std;

PlayerView::PlayerView(): subject(NULL) {

}

PlayerView::PlayerView(Player* player) : subject(player) {
	//subject->attach(this);
};

void PlayerView::displayCountries(ofstream& fout) {
	list<Country*> *tempList = subject->getOwnedCountries();

	if (tempList->size() != 0) {
		

		for (list<Country*>::iterator iterate = tempList->begin(); iterate != tempList->end(); ++iterate) {
			fout << (*iterate)->getName() << " (armies: " << (*iterate)->getArmies() << ") ";
		}
	}
	else {
		fout << "NONE";
	}

	

}

void PlayerView::displayContinents(ofstream& fout) {
	list<Continent*> *tempList = subject->getOwnedContinents();

	if (tempList->size() != 0) {
		

		for (list<Continent*>::iterator iterate = tempList->begin(); iterate != tempList->end(); ++iterate) {
			fout << (*iterate)->getName() << " ";
		}
	}
	else {
		fout << "NONE";
	}
	

}

void PlayerView::displayCards(ofstream& fout) {

	// display artillery cards
	fout << "ARTILLERY: ";
	for (list<Card*>::iterator i = subject->getPlayersArtilleryCards()->begin(); i != subject->getPlayersArtilleryCards()->end(); ++i) {
		fout << (*i)->getCountryOnCard() << " ";
	}
	fout << endl;

	// display cavalry cards
	fout << "CAVALRY: ";
	for (list<Card*>::iterator i = subject->getPlayersCavalryCards()->begin(); i != subject->getPlayersCavalryCards()->end(); ++i) {
		fout << (*i)->getCountryOnCard() << " ";
	}
	fout << endl;

	// display infantry cards
	fout << "INFANTRY: ";
	for (list<Card*>::iterator i = subject->getPlayersInfantryCards()->begin(); i != subject->getPlayersInfantryCards()->end(); ++i) {
		fout << (*i)->getCountryOnCard() << " ";
	}
	fout << endl;

	// display wild cards
	fout << "WILD: ";
	for (list<Card*>::iterator i = subject->getPlayersWildCards()->begin(); i != subject->getPlayersWildCards()->end(); ++i) {
		fout << (*i)->getCountryOnCard() << " ";
	}
	fout << endl;
}

void PlayerView::displayPlayerInfo() {
	ofstream fout;
	fout.open("playerobs.txt", ios::app);

	fout << "------------------" << endl;
	fout << "PLAYER INFORMATION: " << subject->getName() << endl;
	fout << "------------------" << endl;
	fout << "Countries owned: ";
	displayCountries(fout);
	fout << endl;
	fout << "Continents owned: ";
	displayContinents(fout);
	fout << endl;
	fout << "Cards owned: ";
	fout << endl;
	displayCards(fout);
	fout << "Number of battles won: " << subject->getNumberBattlesWon() << endl;

	fout << endl;
	fout.close();
}

void PlayerView::update() {
	displayPlayerInfo();
}