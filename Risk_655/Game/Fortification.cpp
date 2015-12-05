#include "Fortification.h"
#include <vector>
Fortification::Fortification() {

}


void Fortification::fortify(Player* gamePlayer, Map* map) {
	cout << endl;
	//cout << gamePlayer->getName() << ": FORTIFY!" << endl;

	string answer;
	bool isValid = false;
	cout << "COUNTRY ID\tCOUNTRY NAME\tCURRENT # OF ARMIES" << endl;
	for (list<Country*>::iterator i = gamePlayer->getOwnedCountries()->begin(); i != gamePlayer->getOwnedCountries()->end(); ++i) {
		cout << (*i)->getId() << "\t\t" << (*i)->getName() << "\t\t" << (*i)->getArmies() << endl;
	}
	int initialCountryID;
	do {
		cout << "Enter the id of the country you want to move your armies from, or -1 to pass turn: ";
		cin >> initialCountryID;
		if (initialCountryID == -1)
			return;
		for (list<Country*>::iterator i = gamePlayer->getOwnedCountries()->begin(); i != gamePlayer->getOwnedCountries()->end(); ++i) {
			if (initialCountryID == (*i)->getId()) {
				isValid = true;
				break;
			}
		}
	} while (!isValid);
	isValid = false;
	vector<Country*> possibleFortication;
	while (!isValid) {
		possibleFortication = map->getCountriesConnectedTo(gamePlayer->getCountryById(initialCountryID));
		if (possibleFortication.size() == 0) {
			string answer;
			cout << "This country has no connections to your other countries!\n" << endl;
			cout << "Would you like to fortify another country (enter y for yes and n for no): " << endl;

			do {
				cin >> answer;
				if (answer == "y" || answer == "Y") {
					cout << "Enter the id of the country you want to move your armies from, or -1 to pass turn: ";
					cin >> initialCountryID;
					if (initialCountryID == -1)
						return;
					for (list<Country*>::iterator i = gamePlayer->getOwnedCountries()->begin(); i != gamePlayer->getOwnedCountries()->end(); ++i) {
						if (initialCountryID == (*i)->getId()) {
							isValid = true;
							break;
						}
					}

				}
				else
					return;
			} while (answer != "n" && answer != "N" && answer != "y" && answer != "N");
			isValid = false;
		}
		else {
			isValid = true;
		}
	}
	isValid = false;
	cout << "Enter the id of the country you want to move your armies to : ";
	int finalCountryID;
	cin >> finalCountryID;
	do {
		for (int i = 0; i < possibleFortication.size(); i++) {
			if (possibleFortication[i]->getId() == finalCountryID) {
				isValid = true;
				break;
			}
		}
		if (!isValid) {
			cout << "Invalid ID try again: ";
			cin >> finalCountryID;
		}
	} while (!isValid);
	isValid = map->checkIsAdjacent(gamePlayer->getCountryById(initialCountryID), gamePlayer->getCountryById(finalCountryID));

	if (isValid) {

		cout << "Enter the number of armies you want to move: ";
		int movingArmies;
		cin >> movingArmies;

		int playersArmies = gamePlayer->getCountryById(initialCountryID)->getArmies();


		while ((playersArmies - 1) < movingArmies) {
			cout << "You should not move all your armies to an adjacent country. Try again :";
			cin >> movingArmies;
		}

		int initialCountryArmies = playersArmies - movingArmies;
		int finalCountryArmies = gamePlayer->getCountryById(finalCountryID)->getArmies() + movingArmies;

		gamePlayer->setArmiesInCountry((gamePlayer->getCountryById(initialCountryID)), initialCountryArmies);
		gamePlayer->setArmiesInCountry((gamePlayer->getCountryById(finalCountryID)), finalCountryArmies);
		cout << "Armies moved successfully!" << endl;
		cout << "COUNTRY ID\tCOUNTRY NAME\tCURRENT # OF ARMIES" << endl;
		cout << "---------------------------------------------------------------------" << endl;
		for (list<Country*>::iterator i = gamePlayer->getOwnedCountries()->begin(); i != gamePlayer->getOwnedCountries()->end(); ++i) {
			cout << (*i)->getId() << "\t\t" << (*i)->getName() << "\t\t" << (*i)->getArmies() << endl;
			}
	}
}