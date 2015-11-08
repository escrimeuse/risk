// Assignment #1 - COMP345 - Section DI - Fall 2015
// Author: Jennifer Sunahara (27590628)
//
//This is the implementation file Map.cpp of the class Map.
//The interface of this class is in the header file Map.h.

#include<string>
#include<iostream>
#include<vector>
using namespace std;

#include "Country.h"
#include "Continent.h"
#include "Map.h"


Map::Map(string n, int ctry, int ctnt) {
	name = n;
	numCountries = ctry;
	numContinents = ctnt;
	continents = new vector<Continent*>;
	countries = new vector<Country*>;
	
	//making the continents
	for (int i = 0; i < numContinents; i++) {
		Continent *newContinent = new Continent();
		addContinent(newContinent);
	}
	//making the countries
	for (int i = 0; i < numCountries; i++) {
		Country *newCountry = new Country();
		addCountry(newCountry);

		//adding the countries to continents
		if(i == 0 || i == 1 || i == 2)
			((*continents)[0])->addCountry(newCountry);
		else if (i == 3 || i == 4 || i == 5)
			((*continents)[1])->addCountry(newCountry);
		else if (i == 6 || i == 7 || i == 8)
			((*continents)[2])->addCountry(newCountry);
	}
	
	
	//building the country adjacency matrix
	//Note that the adjacency matrix indices represent countries relationship to one another.
	//Note that the indexes represent the country number -1.
	//For example, countriesAdj[0][2] is the relationship between country 1 and country 3.
	for (int i = 0; i < numCountries; i++) {
		for (int j = 0; j < numCountries; j++) {
			if (i == j)
				countriesAdj[i][j] = true;//making sure a country is adjacent to itself
			else
				countriesAdj[i][j] = false;
		}
	}
	
}

int Map::getNumCountries() const{
	return numCountries;
}

int Map::getNumContinents() const {
	return numContinents;
}

//returns a string with the name of the map
string Map::getName() const {
	return name;
}

//returns a string with the names of the continents of the map, seperated by a space
string Map::getContinentNames() const {
	if (numContinents > 0) {
		string names = "";
		for (int i = 0; i < numContinents; i++)
			names += ((*continents)[i])->getName() + " ";
		return names;
	}
	else
		return "No continents";
}

//returns a string with the names of the countries of the map, seperated by a space
string Map::getCountryNames() const {
	if (numCountries > 0) {
		string names = "";
		for (int i = 0; i < numCountries; i++)
			names += ((*countries)[i])->getName() + " ";
		return names;
	}
	else
		return "No countries";
}

//setting the names of the countries of the map
void Map::setCountryNames() {
	string n = "";
	if (numCountries > 0) {
		for (int i = 0; i < numCountries; i++) {
			cout << "Country" << (i+1) << " : ";
			cin >> n;
			((*countries)[i])->setName(n);
		}
	}
	else
		cout << "No continents" << endl;
}

//setting the names of the continents of the map
void Map::setContinentNames() {
	string n = "";
	if (numContinents > 0) {
		for (int i = 0; i < numContinents; i++) {
			cout << "Continent" << (i+1) << " : ";
			cin >> n;
			((*continents)[i])->setName(n);
		}
	}
	else
		cout << "No continents" << endl;
}


bool Map::getIsConnected() {
	//before returning isConnected, perform a check
	setIsConnected(checkIsConnected());
	return isConnected;
}

//this set should only be called by getIsConnected
void Map::setIsConnected(bool b) {
	isConnected = b;
}

bool Map::checkIsConnected() {
	//making sure that the visited array is reset
	for (int i = 0; i < numCountries; i++) {
		visited[i] = 0;
	}

	//starting the travesal at country0
	int x = 0;
	visiting(x);

	//checking if all the countries have been visited
	for (int i = 0; i < numCountries; i++) {
		if (visited[i] == 0)
			return false; //should only get here if one of the countries was not visited
	}
	return true;//should only get here if all countries were visited
}

void Map::visiting(int x) {
	//visit country x
	cout << "Currently visiting country" << x << endl;
	visited[x] = 1;
	for (int i = 0; i < numCountries; i++) {
		if ((countriesAdj)[x][i] == true && visited[i] == 0)//if country x is adjacent to country i, then visit country i
			visiting(i);
	}
}
//adding a continent to the map (should only be called at the initialization of the map)
void Map::addContinent(Continent* c) {
	continents->push_back(c);
}

//adding a conutry to the map (should only be called at the initialization of the map)
void Map::addCountry(Country* c) {
	countries->push_back(c);
}

//making two countries adjacent, based on their names
//if one of the names is not associated with a country, an error message is displayed
void Map::makeAdjacent(string c1, string c2) {
	bool exists1 = false;
	bool exists2 = false;
	int target1;
	int target2;
	for (int i = 0; i < numCountries; i++) {
		if (((*countries)[i]->getName())==c1) {
			exists1 = true;//first country name is found
			target1 = (*countries)[i]->getId();
		}
	}
	for (int i = 0; i < numCountries; i++) {
		if (((*countries)[i]->getName()) == c2) {
			exists2 = true;//second country name is found
			target2 = (*countries)[i]->getId();
		}
	}
	if (exists1 && exists2) {
		countriesAdj[target1 - 1][target2 - 1] = true;//modifying the adjacency matrix
		countriesAdj[target2 - 1][target1 - 1] = true;
		cout << c1 << " and " << c2 << " are now adjacent." << endl;
	}
	else {
		cout << "One or both of those countries do not exist." << endl;
	}

}



//printing to the console the names of the countries adjacent to a country C, based on its name
//if the names is not associated with a country, an error message is displayed
void Map::printAdjacentCountryNames(string n) {
	bool exists = false;
	int target;
	//making sure that the string is a valid country name
	for (int i = 0; i < numCountries; i++) {
		if (((*countries)[i]->getName()) == n) {
			exists = true;
			target=(*countries)[i]->getId();
		}
	}
	//if it is a valid country name
	if (exists) {
		cout << "The following countries are adjacent to " << n << ": ";
		for (int i = 0; i < numCountries; i++) {
			if (countriesAdj[target - 1][i] == true) {
				cout << (*countries)[i]->getName() << " ";
			}
		}
		cout << " " << endl;
	}
	else {
		cout << "No such country could be found." << endl;
	}

}

//Preconditon: valid id numbers only
//This is a helper method mainly for the purpose of the demo
void Map::printAdjacentCountryNamesById(int n) {
	cout << "The following countries are adjacent to " << (*countries)[n-1]->getName() << ": ";
	for (int i = 0; i < numCountries; i++) {
		if (countriesAdj[n-1][i] == true) {
			cout << (*countries)[i]->getName() << " ";
		}
	}
	cout << " " << endl;
}

//Preconditon: valid id numbers only
//This is a helper method mainly for the purpose of the demo
void Map::printContinentsCountries(int n) {
	cout << "The following countries belong to " << (*continents)[n - 1]->getName() << ": ";
	cout << (*continents)[n - 1]->getCountryNames() << " "<< endl;
}

void Map::demoMap() {
	// country 1 is adjacent to country 2
	countriesAdj[0][1] = true;
	printAdjacentCountryNamesById(1);

	// country 2 is adjacent to country 1, 3
	countriesAdj[1][0] = true;
	countriesAdj[1][2] = true;
	printAdjacentCountryNamesById(2);

	// country 3 is adjacent to country 2, 6
	countriesAdj[2][1] = true;
	countriesAdj[2][5] = true;
	printAdjacentCountryNamesById(3);

	// country 4 is adjacent to country 5, 6
	countriesAdj[3][4] = true;
	countriesAdj[3][5] = true;
	printAdjacentCountryNamesById(4);

	// country 5 is adjacent to country 4, 6, 7, 8
	countriesAdj[4][3] = true;
	countriesAdj[4][5] = true;
	countriesAdj[4][6] = true;
	countriesAdj[4][7] = true;
	printAdjacentCountryNamesById(5);

	// country 6 is adjacent to country 3, 4, 5
	countriesAdj[5][2] = true;
	countriesAdj[5][3] = true;
	countriesAdj[5][4] = true;
	printAdjacentCountryNamesById(6);

	// country 7 is adjacent to country 5, 8, 9
	countriesAdj[6][4] = true;
	countriesAdj[6][7] = true;
	countriesAdj[6][8] = true;
	printAdjacentCountryNamesById(7);

	// country 8 is adjacent to country 5, 7
	countriesAdj[7][4] = true;
	countriesAdj[7][6] = true;
	printAdjacentCountryNamesById(8);

	// country 9 is adjacent to country 7
	countriesAdj[8][6] = true;
	printAdjacentCountryNamesById(9);
	
}