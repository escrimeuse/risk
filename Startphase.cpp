#include "Startphase.h"
#include "Player.h"
#include "Map.h"
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

Startphase::Startphase() {
}

void Startphase::welcome() {
	for (int i = 0; i < 5; i++)
		cout << endl;
	cout << "                     gggggg      gggg  gggggggggg  ggg     ggg  " << endl;
	cout << "                    ggggggggg    gggg  gggggggggg  ggg    ggg  " << endl;
	cout << "                    gggggggggg   gggg  ggg         ggg   ggg   " << endl;
	cout << "                    gggg   ggg   gggg  ggg         ggg  ggg    " << endl;
	cout << "                    gggg   ggg   gggg  gggggggggg  ggggggg     " << endl;
	cout << "                    gggggggg     gggg         ggg  ggg  ggg    " << endl;
	cout << "                    gggg  ggg    gggg         ggg  ggg   ggg   " << endl;
	cout << "                    gggg   ggg   gggg  gggggggggg  ggg    ggg  " << endl;
	cout << "                    gggg   ggg   gggg  gggggggggg  ggg     ggg  " << endl;
	for (int i = 0; i < 11; i++)
		cout << endl;
	system("pause");
	system("cls");
}

int Startphase::mainMenu() {
	int option = -1;
	do{
		cout << "Welcome to risk! \nChoose an option:\n\n" << endl;
		cout << "0. Map Editor" << endl;
		cout << "1. Start Game" << endl;
		cout << "2. Exit\n" << endl;
		cout << "Option: ";
		cin >> option;
	} while (option < 0 || option > 2);

	return option;
}


int Startphase::initializeNumOfGamePlayers(vector<Player*>& gamePlayers){
	try {
		cout << "Enter the number of players as an integer\n"
			<< "(The number of players should be at least 2 and at most 6) : ";
		int numOfGamePlayers;
		cin >> numOfGamePlayers;

		if ((numOfGamePlayers < 2) || (numOfGamePlayers > 6))
			throw numOfGamePlayers;
		return numOfGamePlayers;
	}
	catch (int numOfGamePlayers) {
		cout << "Illegal number of players.Try again.";
		cin >> numOfGamePlayers;

		if ((numOfGamePlayers < 2) || (numOfGamePlayers > 6)) {
			cout << "The entered number of players is not valid.Game over.";
			exit(1);
		}
		return numOfGamePlayers;
	}
}//end of initializeNumOfGamePlayers function definition


	void Startphase::createPlayers(vector<Player*>& gamePlayers, int numOfGamePlayers){

		for (unsigned int i = 0; i < numOfGamePlayers; i++) {
			cout << "Enter players name : ";
			string name;
			cin >> name;

			//Initialize each players name, and id, and temporarily set the players turn to zero until they each roll the dice.
			Player* newPlayer = new Player(name);
			gamePlayers.push_back(newPlayer);

		}

	}// end of createPlayers function definition


	void Startphase::initializePlayersTurn(vector<Player*>& gamePlayers) {
		srand(time(0));
		int size = gamePlayers.size();
		int* rollValues = new int[size];
		
		for (int i = 0; i < size; i++) {
			rollValues[i] = roll();
		}
		//Sort the array of roll values in a descending order
		Player* tempPlayer;
		int temp;

		for (int i = 0; i < size-1; i++) {
			for (int j = i + 1; j < size; j++) {
				if (rollValues[i] > rollValues[j]) {
					temp = rollValues[i];
					rollValues[i] = rollValues[j];
					rollValues[j] = temp;

					tempPlayer = gamePlayers[i];
					gamePlayers[i] = gamePlayers[j];
					gamePlayers[j] = tempPlayer;
				}
			}
		}
	}//end of initializePlayersTurn function definition



	void Startphase::assignCountries(vector<Player*>& gamePlayers, Map* map) {
		int numCountries = map->getNumCountries();
		int numPlayers = gamePlayers.size();
		vector<Country*> *countriesInMap = map->getCountries();
		cout << "Assigning Countries, loading.";
		for (int i = numPlayers-1; i >= 0; i--) {
			int numCountriesPlayer = numCountries / (i+1);
			numCountries -= numCountriesPlayer;
			for (int j = 0; j < numCountriesPlayer;) {
				srand(time(NULL));
				int index = (rand() % map->getNumCountries());
				if (!(countriesInMap->at(index)->getIsOwned())) {
					cout << ".";
					(gamePlayers.at(i))->addOwnedCountry(countriesInMap->at(index));
					countriesInMap->at(index)->setOwner(gamePlayers.at(i));	// Just Pointer Later
					j++;
				}
				
			}
			gamePlayers.at(i)->setNumOwnedCountries(numCountriesPlayer);
		}
		cout << endl;
	}//end of assignCountries function definition


	int Startphase::roll() {
		int num = (1 + rand() % 6);
		return num;
	}










