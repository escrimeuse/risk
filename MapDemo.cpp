// Assignment #2 - COMP345 - Section DI - Fall 2015
// Author: Jennifer Sunahara (27590628)
//
//This is the implementation file MapDemo.cpp of the class MapDemo.
//The interface of this class is in the header file Map.h.

#include<string>
#include<iostream>
#include<vector>
using namespace std;

#include "Country.h"
#include "Continent.h"
#include "Map.h"
#include "MapDemo.h"


//Constructor makes demo map with 6 countries and 3 continents
MapDemo::MapDemo(string n): Map(n, DEMO_MAP_NUM_COUNTRIES, DEMO_MAP_NUM_CONTINENTS){
	//type
	setType("MAPDEMO");
	//making the continents
	for (int i = 0; i < Map::getNumContinents(); i++) {
		Continent *newContinent = new Continent();
		addContinent(newContinent);
	}
	//making the countries
	for (int i = 0; i < Map::getNumCountries(); i++) {
		Country *newCountry = new Country();
		addCountry(newCountry);

		//adding the countries to continents
		if (i == 0 || i == 1)
			((*Map::getContinents())[0])->addCountry(newCountry);
		else if (i == 2 || i == 3)
			((*Map::getContinents())[1])->addCountry(newCountry);
		else if (i == 4 || i == 5)
			((*Map::getContinents())[2])->addCountry(newCountry);

	}

	//building the country adjacency matrix
	//Note that the adjacency matrix indices represent countries relationship to one another.
	//Note that the indexes represent the country number -1.
	//For example, countriesAdj[0][2] is the relationship between country 1 and country 3.
	for (int i = 0; i < Map::getNumCountries(); i++) {
		for (int j = 0; j < Map::getNumCountries(); j++) {
			if (i == j)
				countriesAdj[i][j] = true;//making sure a country is adjacent to itself
			else
				countriesAdj[i][j] = false;
		}
	}

}

bool MapDemo::checkIsAdjacentByIndex(int c1, int c2) {
	if((countriesAdj)[c1][c2] == true)
		return true;
	return false;
}

bool MapDemo::checkContinentsValid() {
	
	for (int i = 0; i < Map::getNumContinents(); i++) {
		Continent *current = (*Map::getContinents())[i];// set current to continent i
		bool contCountriesAdj[DEMO_MAP_NUM_CONT_COUNTRIES][DEMO_MAP_NUM_CONT_COUNTRIES]; // create adjacencymatrix for continent i

		for (int j = 0; j < DEMO_MAP_NUM_CONT_COUNTRIES; j++) {//explicitly setting the matrix to false
			for (int k = 0; k < DEMO_MAP_NUM_CONT_COUNTRIES; k++) {
				contCountriesAdj[j][k]=false;
			}
		}


		vector<Country*> *contCountries = current->getCountries();// get list of countries for continent i

		for (int j = 0; j != (contCountries->size()); j++) {//going through the list of countries of continent i

			int target1 = ((*contCountries)[j])->getId()-1; // target1 is id-1 of country j
			for (int k = 0; k != (contCountries->size()); k++) {

				int target2 = ((*contCountries)[k])->getId()-1;//target2 is  id-1 of country k
				if (countriesAdj[target1][target2] == true) // if country j is adjacent to country k
					contCountriesAdj[j][k] = true; //set j as adjacent to k in the visitedContinent matrix
			}
		}//countriesAdj is filled

		//making sure that the visited continent array is reset
		for (int j = 0; j < DEMO_MAP_NUM_CONT_COUNTRIES; j++) {
			visitedContinent[j] = 0;
		}
		int x = 0;

		visitingContinent(x, contCountriesAdj);

		//checking if all the countries have been visited
		for (int j = 0; j < DEMO_MAP_NUM_CONT_COUNTRIES; j++) {
			if (visitedContinent[j] == 0)
				return false; //should only get here if one of the countries was not visited
		}
		//should only reach this point if all the countries in the continent have been visited

	}
	return true;
}

void MapDemo::visitingContinent(int x, bool b[][DEMO_MAP_NUM_CONT_COUNTRIES]) {
	//visit country x
	cout << "Currently visiting country" << x << endl;
	visitedContinent[x] = 1;
	for (int i = 0; i < DEMO_MAP_NUM_CONT_COUNTRIES; i++) {
		cout << "visitedContinent[i]: " << visitedContinent[i] << endl;
		if (((b)[x][i] == true) && (visitedContinent[i] == 0))//if country x is adjacent to country i and it has not been visited, then visit country i
			visitingContinent(i, b);
	}
}


bool MapDemo::checkIsConnected() {
	//making sure that the visited map array is reset
	for (int i = 0; i < Map::getNumCountries(); i++) {
		visitedMap[i] = 0;
	}

	//starting the travesal at country0
	int x = 0;
	visitingMap(x);

	//checking if all the countries have been visited
	for (int i = 0; i < Map::getNumCountries(); i++) {
		if (visitedMap[i] == 0)
			return false; //should only get here if one of the countries was not visited
	}
	return true;//should only get here if all countries were visited
}

void MapDemo::visitingMap(int x) {
	//visit country x
	cout << "Currently visiting country" << x << endl;
	visitedMap[x] = 1;
	for (int i = 0; i < Map::getNumCountries(); i++) {
		if ((countriesAdj)[x][i] == true && visitedMap[i] == 0)//if country x is adjacent to country i and it has not been visited, then visit country i
			visitingMap(i);
	}
}

//making two countries adjacent, based on their names
//if one of the names is not associated with a country, an error message is displayed
void MapDemo::makeAdjacent(string c1, string c2) {
	bool exists1 = false;
	bool exists2 = false;
	int target1;
	int target2;
	for (int i = 0; i < Map::getNumCountries(); i++) {
		if (((*Map::getCountries())[i]->getName()) == c1) {
			exists1 = true;//first country name is found
			target1 = (*Map::getCountries())[i]->getId();
		}
	}
	for (int i = 0; i < Map::getNumCountries(); i++) {
		if (((*Map::getCountries())[i]->getName()) == c2) {
			exists2 = true;//second country name is found
			target2 = (*Map::getCountries())[i]->getId();
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
void MapDemo::printAdjacentCountryNames(string n) {
	bool exists = false;
	int target;
	//making sure that the string is a valid country name
	for (int i = 0; i < Map::getNumCountries(); i++) {
		if (((*Map::getCountries())[i]->getName()) == n) {
			exists = true;
			target = (*Map::getCountries())[i]->getId();
		}
	}
	//if it is a valid country name
	if (exists) {
		cout << "The following countries are adjacent to " << n << ": ";
		for (int i = 0; i < Map::getNumCountries(); i++) {
			if (countriesAdj[target - 1][i] == true) {
				cout << (*Map::getCountries())[i]->getName() << " ";
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
void MapDemo::printAdjacentCountryNamesById(int n) {
	cout << "The following countries are adjacent to " << (*Map::getCountries())[n - 1]->getName() << ": ";
	for (int i = 0; i < Map::getNumCountries(); i++) {
		if (countriesAdj[n - 1][i] == true) {
			cout << (*Map::getCountries())[i]->getName() << " ";
		}
	}
	cout << " " << endl;
}

//Preconditon: valid id numbers only
//This is a helper method mainly for the purpose of the demo
void MapDemo::printContinentsCountries(int n) {
	cout << "The following countries belong to " << (*Map::getContinents())[n - 1]->getName() << ": ";
	cout << (*Map::getContinents())[n - 1]->getCountryNames() << " " << endl;
}

void MapDemo::demoMap() {
	// country 1 is adjacent to country 2, 6
	countriesAdj[0][1] = true;
	countriesAdj[0][5] = true;
	printAdjacentCountryNamesById(1);

	// country 2 is adjacent to country 1, 3, 6
	countriesAdj[1][0] = true;
	countriesAdj[1][2] = true;
	countriesAdj[1][5] = true;
	printAdjacentCountryNamesById(2);

	// country 3 is adjacent to country 2, 4, 5
	countriesAdj[2][1] = true;
	countriesAdj[2][3] = true;
	countriesAdj[2][4] = true;
	printAdjacentCountryNamesById(3);

	// country 4 is adjacent to country 3, 6
	countriesAdj[3][2] = true;
	printAdjacentCountryNamesById(4);

	// country 5 is adjacent to country 3, 6
	countriesAdj[4][2] = true;
	countriesAdj[4][5] = true;
	printAdjacentCountryNamesById(5);

	// country 6 is adjacent to country 1, 2, 5
	countriesAdj[5][0] = true;
	countriesAdj[5][1] = true;
	countriesAdj[5][4] = true;
	printAdjacentCountryNamesById(6);

}