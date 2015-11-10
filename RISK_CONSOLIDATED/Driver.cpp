#include <iostream>
#include "Player.h"
#include "Country.h"
#include "Continent.h"
#include <string>
#include <fstream>
#include <list>
#include <sstream>
#include "Map.h"

using namespace std;

bool readInContentsOfMapFile();

int main() {
	//Country* country1 = new Country();
	//Country* country2 = new Country();
	//country1->setName("Canada");
	//country2->setName("USA");
	//country1->setArmies(2);
	//country2->setArmies(7);

	//Player* player1 = new Player("Rick");
	//country1->setOwner(player1);
	//country2->setOwner(player1);

	//player1->addOwnedContinent(new Continent());
	//player1->addOwnedCountry(country1);
	//player1->addOwnedCountry(country2);

	//player1->addPlayerCard(new Card("Canada", infantry));
	//player1->addPlayerCard(new Card("Mexico", infantry));
	//player1->addPlayerCard(new Card("China", infantry));
	//player1->addPlayerCard(new Card("USA", cavalry));
	//player1->addPlayerCard(new Card("Japan", cavalry));
	//player1->addPlayerCard(new Card("Australia", cavalry));
	//player1->addPlayerCard(new Card("England", artillery));
	//player1->addPlayerCard(new Card("France", wild));

	//player1->reinforceCountries();

	readInContentsOfMapFile();
}

bool readInContentsOfMapFile() {
	string mapType = "";
	string mapName = "";
	int numberCountries = -1;
	int numberContinents = -1; 

	struct CountryL {
		string name;
		string owner;
		int id;
		int numArmies;
		bool* adjacencies;
	};

	struct ContinentL {
		string name;
		int numCountries;
		int* countryIds;
	};

	ifstream fin;
	fin.open("test.txt");

	try {

		// first read in the map type
		fin >> mapType;
		if (fin.fail()) {
			throw 20;
		}
		cout << mapType << endl;

		// now read in the map name
		fin >> mapName;
		if (fin.fail()) {
			throw 20;
		}
		cout << mapName << endl;

		// read in the number of countries
		fin >> numberCountries;
		if (fin.fail()) {
			throw 20;
		}
		cout << numberCountries << endl;

		// create a list to store the country data
		vector<CountryL*>* countryList = new vector<CountryL*>;
		for (int i = 0; i < numberCountries; ++i) {
			CountryL* newCountry = new CountryL();

			fin >> newCountry->id;
			if (fin.fail()) {
				throw 20;
			}
			cout << newCountry->id << " ";

			fin >> newCountry->name;
			if (fin.fail()) {
				throw 20;
			}
			cout << newCountry->name << " ";

			fin >> newCountry->owner;
			if (fin.fail()) {
				throw 20;
			}
			cout << newCountry->owner << " ";

			fin >> newCountry->numArmies;
			if (fin.fail()) {
				throw 20;
			}
			cout << newCountry->numArmies << " ";
			cout << endl;

			countryList->push_back(newCountry);
		}

		// check the list to see if we have any countries with the same ID number. Since an ID is unique to a country, 
		// we should not have any duplicate/matching ID numbers in a valid map
		for (vector<CountryL*>::iterator i=countryList->begin(); i != countryList->end(); ++i) {
			int countryID = (*i)->id;

			for (vector<CountryL*>::iterator j = countryList->begin(); j != countryList->end(); ++j) {
				if ((*j)->id == countryID) {
					throw 20;
				}
			}
		}

		// read in the number of continents
		fin >> numberContinents;
		if (fin.fail()) {
			throw 20;
		}
		cout << numberContinents << endl;

		// create a list to store the continent data
		vector<ContinentL*>* continentList = new vector<ContinentL*>;

		for (int i = 0; i < numberContinents; ++i) {
			ContinentL* newContinent = new ContinentL();

			fin >> newContinent->name;
			if (fin.fail()) {
				throw 20;
			}
			cout << newContinent->name << " ";

			fin >> newContinent->numCountries;
			if (fin.fail()) {
				throw 20;
			}
			cout << newContinent->numCountries << " ";

			newContinent->countryIds = new int[newContinent->numCountries];

			for (int i = 0; i < newContinent->numCountries; ++i) {
				fin >> (newContinent->countryIds)[i];
				if (fin.fail()) {
					throw 20;
				}
				cout << (newContinent->countryIds)[i] << endl;
			}

			continentList->push_back(newContinent);
		}

		// now read in the adjacencies of each country
		int tempCountryId = -1;
		for (int i = 0; i < numberCountries; ++i) {
			fin >> tempCountryId; 
			if (fin.fail()) {
				throw 20;
			}
			cout << tempCountryId << endl;
			CountryL* country = NULL;

			// search country list to find the country corresponding to this ID
			for (vector<CountryL*>::iterator j = countryList->begin(); j!=countryList->end(); ++j) {
				if ((*j)->id == tempCountryId) {
					country = *j;
					break;
				}
			}
			if (country == NULL) {
				// if the country is NULL, then that means that the country ID read in from the file does not correspond to a
				// country ID that was previously read in from the file.
				throw 20;
			}

			country->adjacencies = new bool[numberCountries];

			for (int k = 0; k < numberCountries; ++k) {
				fin >> (country->adjacencies)[k];
				if (fin.fail()) {
					throw 20;
				}
				cout << (country->adjacencies)[k] << " ";
			}
			cout << endl;
		}

		bool** adjacencyMatrix = new bool*[numberCountries];
		for (vector<CountryL*>::iterator i = countryList->begin(), int j=0; i != countryList->end();++i,++j) {
			adjacencyMatrix[j] = (*i)->adjacencies;
		}



	
	} catch (...) {
		cout << "ERROR:" << endl;
		cout << "The map file you are trying to load has been corrupted!" << endl;
		cout << "It is to RISKy to load it >:-|" << endl;
		return false;
	}

	fin.close();

	
	return true;
}