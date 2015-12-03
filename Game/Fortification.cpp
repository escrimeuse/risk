#include "Fortification.h"
#include<vector>

Fortification::Fortification() {

}

void Fortification::fortify(Player* gamePlayer, Map* map) {
	cout << endl;
	cout << gamePlayer->getName() << ": FORTIFY!" << endl;

	string answer;
	/*do {*/
		cout << "COUNTRY ID\tCOUNTRY NAME\tCURRENT # OF ARMIES" << endl;
		for (list<Country*>::iterator i = gamePlayer->getOwnedCountries()->begin(); i != gamePlayer->getOwnedCountries()->end(); ++i) {
			cout << (*i)->getId() << "\t\t" << (*i)->getName() << "\t\t" << (*i)->getArmies() << endl;
		}
		cout << "Enter the id of the country you want to move your armies from, or -1 to pass turn: ";
		int initialCountryID;
		cin >> initialCountryID;
		if (initialCountryID == -1)
			return;
		vector<Country*> possibleFortication = map->getAllyCountries(gamePlayer->getCountryById(initialCountryID));
		if (possibleFortication.size() == 0) {
			cout << "This country has no connections to your other countries!" << endl;
		}
		else {
			bool isValid = false;
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
				cout << "Invalid ID try again: ";
				cin >> finalCountryID;
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

				gamePlayer->setArmiesInCountry((gamePlayer->getCountryById(initialCountryID)), finalCountryArmies);

				cout << "Armies moved successfully!" << endl;
				notify(FORTIFICATION_ID);
				cout << "COUNTRY ID\tCOUNTRY NAME\tCURRENT # OF ARMIES" << endl;
				cout << "---------------------------------------------------------------------" << endl;
				for (list<Country*>::iterator i = gamePlayer->getOwnedCountries()->begin(); i != gamePlayer->getOwnedCountries()->end(); ++i) {
					cout << (*i)->getId() << "\t\t" << (*i)->getName() << "\t\t" << (*i)->getArmies() << endl;
				}
				

			}
			else {
				cout << "You can only fortify adjacent countries." << endl;
			}
		}
	/*} while (true);*/
}