#include "Startphase.h"
#include "GamePlayers.h"
#include "Countries.h"
#include "Continents.h"
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;


Startphase::Startphase() {
}

void Startphase::welcome() {
	cout << "\t\t\tWelcome to Risk";
}


int Startphase::initializeNumOfGamePlayers(vector<GamePlayers*> gamePlayers){ 
	try {
		cout << "Enter the number of players as an integer\n"
			<< "(The number of players should be at least 2 and at most 6”) : ";
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


	void Startphase::createPlayers(vector<GamePlayers*> gamePlayers){
		int numOfGamePlayers = gamePlayers.size();

		for (unsigned int i = 0; i < numOfGamePlayers; i++) {
			cout << "Enter player’s name : ";
			string name;
			cin >> name;

			//To create 4 digits id for each players.
			int id = (2000 + rand() % 1000);

			//Initialize each players name, and id, and temporarily set the player’s turn to zero until they each roll the dice.
			GamePlayers* newPlayer = new GamePlayers(name, id, 0);
			gamePlayers.push_back(newPlayer);

		}

	}// end of createPlayers function definition


	void Startphase::initializePlayersTurn(vector<GamePlayers*> gamePlayers) {

		int size = gamePlayers.size();
		int* rollValues = new int[size];
		
		for (int i = 0; i < size; i++) {
			rollValues[i] = (gamePlayers.at(i))->roll();
		}

		//Sort the array of roll values in a descending order
		GamePlayers* tempPlayer;
		int temp;

		for (int i = 0; i < size; i++) {
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

		//Set each players turn that was temporarily initialized to 0
		for (unsigned int i = 0; i < size; i++) {
			(gamePlayers.at(i))->setTurn(i + 1);
		}

	}//end of initializePlayersTurn function definition



	void Startphase::assignCountries(vector<GamePlayers*> gamePlayers) {
		int numCountriesPerPlayer = 0;

		if (gamePlayers.size() == 2)
			numCountriesPerPlayer = 7;

		else if (gamePlayers.size() == 3)
			numCountriesPerPlayer = 8;

		else if ((gamePlayers.size() == 4) || (gamePlayers.size() == 5))
			numCountriesPerPlayer = 6;

		else if (gamePlayers.size() == 6)
			numCountriesPerPlayer = 5;

		for (unsigned int i = 0; i < gamePlayers.size(); i++) {
			for (unsigned int j = 1; j < numCountriesPerPlayer; j++) {
				int countryValue = rand() % numCountriesPerPlayer;
				Countries* newCountry = new Countries(countryValue);
				(gamePlayers.at(i))->addCountry(newCountry);
			}
		}

	}//end of assignCountries function definition










