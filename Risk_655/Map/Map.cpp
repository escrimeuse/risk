// Assignment #3 - COMP345 - Section DI - Fall 2015
// Author: Jennifer Sunahara (27590628)
//
//This is the implementation file Map.cpp of the class Map
//The interface of this class is in the header file Map.h.

#include<string>
#include<iostream>
#include<vector>
#include <fstream>
using namespace std;

#include "../Map/Country.h"
#include "../Map/Continent.h"
#include "../Map/Map.h"

//Map non-default constructor (no default constructor)
Map::Map(string n, int ctry, int ctnt) {

	name = n;
	numCountries = ctry;
	numContinents = ctnt;
	continents = new vector<Continent*>;
	countries = new vector<Country*>;
	countriesAdj = new bool*[numCountries];

	//making the empty continents
	for (int i = 0; i < getNumContinents(); i++) {

		Continent *newContinent = new Continent();
		addContinent(newContinent);
	}

	//making the countries
	for (int i = 0; i < Map::getNumCountries(); i++) {

		Country *newCountry = new Country();
		addCountry(newCountry); //adding countries to the map (assignment to continents will happen outside constuctor)
	}

	//preparing the country adjacency matrix
	for (int i = 0; i < numCountries; i++) {
		countriesAdj[i] = new bool[numCountries];
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

//The dummy int is to have a secondary constructor for the use of the saverloader
Map::Map(string n, int ctry, int ctnt, int dummy) {

	name = n;
	numCountries = ctry;
	numContinents = ctnt;
	continents = new vector<Continent*>;
	countries = new vector<Country*>;
	countriesAdj = new bool*[numCountries];

	//note that the constructor does not create the empty countries

	//preparing the country adjacency matrix
	for (int i = 0; i < numCountries; i++) {
		countriesAdj[i] = new bool[numCountries];
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
//Map destructor
Map::~Map() {

	for (int i = 0; i < (*countries).size(); i++) {
		delete (*countries)[i];
	}
	delete countries;

	for (int i = 0; i < (*continents).size(); i++) {
		delete (*continents)[i];
	}

	delete continents;
	
	for (int i = 0; i < numCountries; i++) {
		delete[] countriesAdj[i];
	}

	delete[] countriesAdj;

}

//returns an the number of countries of the map
int Map::getNumCountries() const{
	return numCountries;
}

//returns an the number of continents of the map
int Map::getNumContinents() const {
	return numContinents;
}

//returns a string with the name of the map
string Map::getName() const {
	return name;
}

//returns a pointer to the vector with the continents of the map
vector<Continent*>* Map::getContinents() const {
	return continents;
}

//returns a pointer to the vector with the countries of the map
vector<Country*>* Map::getCountries() const {
	return countries;
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

bool Map::getIsConnected(){
	//before returning isConnected, perform a check
	setIsConnected(checkIsConnected());
	return isConnected;
}

bool Map::getContinentsValid() {
	//before returning continentsValid, perform a check
	setContinentsValid(checkContinentsValid());
	return continentsValid;
}

Continent* Map::getContinentByName(string n) {

	//making sure that the string is a valid country name
	for (int i = 0; i < numContinents; ++i) {

		if (((*Map::getContinents())[i]->getName()).compare(n)==0) {
			return (*Map::getContinents())[i];
		}
	}
	cout << "No such continent could be found." << endl;

	return NULL;
}

Country* Map::getCountryByName(string n) {

	//making sure that the string is a valid country name
	for (int i = 0; i < Map::getNumCountries(); i++) {

		if (((*Map::getCountries())[i]->getName()) == n) {
			return (*Map::getCountries())[i];
		}
	}

	cout << "No such country could be found." << endl;
	return NULL;
}

void Map::setName(string n) {
	name = n;
}

//this set should only be called by getContinentsValid
void Map::setContinentsValid(bool b) {
	continentsValid = b;
}

//this set should only be called by getIsConnected
void Map::setIsConnected(bool b) {
	isConnected = b;
}

//assigning the countries to continents, one country at a time
//PRECONDITION: The countries and continents must be named already or this function will ask the user to assign 
//each unamed country to a continent by name
//POSTCONDITION: The countries will all be assigned to continents and there will be no empty continents
void Map::setContinentCountries() {

	//creating a new vector of countries-to-be-assigned so that we don't ruin the actual Map countries vector
	list<Country*> *toBeAssigned = new list<Country*>;

	for (vector<Country*>::iterator i = countries->begin(); i != countries->end(); ++i) {
		toBeAssigned->push_back(*i);
	}

	string n = "";

	//assigning one country to each continent to avoid having empty continents
	cout << "First, please assign one country to each continent." << endl;
	for (int i = 0; i < numContinents; i++) {
		cout<<"Which country would you like to assign to Continent"<<(i+1)<< " (" << ((*continents)[i])->getName() << ")?:";
		cin >> n;
		Country* target = getCountryByName(n);//note: getCountryByName would return null if the user's name choice is invalid
		
		//checking if the target is in the list of countries to be assigned
		bool inToBeAssignedList = false;
		if (target != NULL) {
			for (list<Country*>::iterator j = toBeAssigned->begin(); j != toBeAssigned->end(); ++j) {
				if (target->getId() == (*j)->getId())
					inToBeAssignedList = true;
			}
		}
		while (target == NULL || !inToBeAssignedList) {//checking to see if the user's name choice is valid

			cout << "\nThis is not a valid country name. Please input a valid country name.:";
			cin >> n;
			target = getCountryByName(n);
			//checking if the target is in the list of countries to be assigned
			if (target != NULL) {
				for (list<Country*>::iterator j = toBeAssigned->begin(); j != toBeAssigned->end(); ++j) {
					if (target->getId() == (*j)->getId())
						inToBeAssignedList = true;
				}
			}
		}//should only exit this loop once we have a valid country

		((*continents)[i])->addCountry(target);//adding target country to the ith continent
		toBeAssigned->remove(target);//removing target country from countries-to-be-assigned
	}//each continent should now have at least one country
	
	 //assigning the rest of the countries
	cout << "Now please assign the rest of the countries to a continent." << endl;

	for (list<Country*>::iterator i = toBeAssigned->begin(); i != toBeAssigned->end(); ++i) {//iterating through the conutries left to be assigned
		cout << "Which continent does " << (*i)->getName() << " belong to?:";
		cin >> n;
		Continent* target = getContinentByName(n);//note: getContinentByName would return null if the user's name choice is invalid
		
		while (target == NULL ) {//checking to see if the user's choice is valid

			cout << "Not a valid continent name. Which continent does " << (*i)->getName() << " belong to?:";
			cin >> n;
			target = getContinentByName(n);
		}//should only exit this loop once we have a valid continent

		target->addCountry(*i);//adding the ith country to the target continent
		*i=NULL; 
	}//all countries assigned now

	delete toBeAssigned;
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


//adding a continent to the map (should only be called at the initialization of the map)
void Map::addContinent(Continent* c) {
	continents->push_back(c);
}

//adding a conutry to the map (should only be called at the initialization of the map)
void Map::addCountry(Country* c) {
	countries->push_back(c);
}

//Preconditon: valid id numbers only
//This is a helper method mainly for the purpose of the demo
void Map::printContinentsCountries(int n) {
	cout << "The following countries belong to " << (*continents)[n - 1]->getName() << ": ";
	cout << (*continents)[n - 1]->getCountryNames() << " "<< endl;
}

void Map::setAdjacency(bool** matrix) {
	for (int i = 0; i < numCountries; ++i) {
		for (int j = 0; j < numCountries; ++j) {
			countriesAdj[i][j] = matrix[i][j];
		}
	}
}

bool Map::checkIsAdjacentByIndex(int c1, int c2) {
	if ((countriesAdj)[c1][c2] == true)
		return true;
	return false;
}
bool Map::checkContinentsValid() {

	for (int i = 0; i < numContinents; i++) {
		Continent *current = (*continents)[i];// set current to continent i
		int currentNumCountries= current->getNumCountries();

		// create adjacencymatrix of countries for continent i
		bool **currentAdj = new bool*[currentNumCountries]; 
		
		for (int j = 0; j < currentNumCountries; j++) {
			currentAdj[j] = new bool[currentNumCountries];















		}




		for (int j = 0; j < currentNumCountries; j++) {//explicitly setting the matrix to false
			for (int k = 0; k < currentNumCountries; k++) {
				currentAdj[j][k] = false;











			}
		}
		
		vector<Country*> *contCountries = current->getCountries();// get list of countries for continent i




		for (int j = 0; j != (contCountries->size()); j++) {//going through the list of countries of continent i

			int target1 = ((*contCountries)[j])->getId() - 1; // target1 is id-1 of country j
			for (int k = 0; k != (contCountries->size()); k++) {

				int target2 = ((*contCountries)[k])->getId() - 1;//target2 is  id-1 of country k
				if (countriesAdj[target1][target2] == true) // if country j is adjacent to country k
					currentAdj[j][k] = true; //set j as adjacent to k in continent i's adjacency matrix (the index represents the countries' positino in continent's list of countries)
			}
		}//currentAdj is filled

		int *visitedContinent = new int[currentNumCountries]; //create an array to "visit" each country of continent i
		
		//making sure every country of continent i is unvisited
		for (int j = 0; j < currentNumCountries; j++) {
			visitedContinent[j] = 0;
		}
		int x = 0;

		visitingContinent(x, currentAdj, visitedContinent, currentNumCountries);

		//checking if all the countries have been visited
		for (int j = 0; j < currentNumCountries; j++) {
			if (visitedContinent[j] == 0)
				return false; //should only get here if one of the countries was not visited
		}
		//should only reach this point if all the countries in the continent have been visited

	}
	return true;
}

void Map::visitingContinent(int x, bool **b, int *a, int aSize) {
	//visit country x
	//cout << "Currently visiting country" << x << endl;
	a[x] = 1;
	for (int i = 0; i < aSize; i++) {
		//cout << "visitedContinent[i]: " << visitedContinent[i] << endl;
		if (((b)[x][i] == true) && (a[i] == 0))//if country x is adjacent to country i and it has not been visited, then visit country i
			visitingContinent(i, b, a, aSize);
	}
}

bool Map::checkIsConnected() {

	int *visitedMap = new int[numCountries];
	//making sure that the visited map array is reset
	for (int i = 0; i < numCountries; i++) {
		visitedMap[i] = 0;
	}

	//starting the travesal at country0
	int x = 0;
	visitingMap(x, visitedMap);

	//checking if all the countries have been visited
	for (int i = 0; i < numCountries; i++) {
		if (visitedMap[i] == 0){
			delete[] visitedMap;
			visitedMap = NULL;
			return false; //should only get here if one of the countries was not visited
		}
	}
	delete[] visitedMap;
	visitedMap = NULL;
	return true;//should only get here if all countries were visited
}

void Map::visitingMap(int x, int *a) {
	//visit country x
	//cout << "Currently visiting country" << x << endl;
	a[x] = 1;
	for (int i = 0; i <numCountries; i++) {
		if ((countriesAdj)[x][i] == true && a[i] == 0)//if country x is adjacent to country i and it has not been visited, then visit country i
			visitingMap(i, a);
	}
}


vector<Country*> Map::getCountriesConnectedTo(Country* c) {
	vector<Country*> *countries = getCountries();
	vector<Country*> connectedCountriesSamePlayer;
	if (c == NULL)
	{
		return connectedCountriesSamePlayer;
	}
	for (int i = 0; i < countries->size(); i++) {
		if (countries->at(i)->getId() != c->getId()) {
			if (countries->at(i)->getOwner()->getName() == c->getOwner()->getName()) {
				if (checkIsAdjacentByIndex(countries->at(i)->getId() - 1, c->getId() - 1)) {
					connectedCountriesSamePlayer.push_back(countries->at(i));
					cout << countries->at(i)->getId() << "\t\t" << countries->at(i)->getName() << "\t\t" << countries->at(i)->getArmies() << endl;
				}
			}
		}
	}
	return connectedCountriesSamePlayer;
}
/*
	Returns vector of countries connected to given country and 
	owned by the same player
*/
vector<Country*> Map::getAllyCountries(Country* c) {
	vector<Country*> *countries = getCountries();
	vector<Country*> connectedCountriesSamePlayer;
	for (int i = 0; i < countries->size(); i++) {
		if (countries->at(i)->getId() != c->getId()) {
			if (countries->at(i)->getOwner()->getName() == c->getOwner()->getName()) {
				if (checkIsAdjacentByIndex(countries->at(i)->getId() - 1, c->getId() - 1)) {
					connectedCountriesSamePlayer.push_back(countries->at(i));
					cout << countries->at(i)->getId() << "\t\t" << countries->at(i)->getName() << "\t\t" << countries->at(i)->getArmies() << endl;
				}
			}
		}
	}
	return connectedCountriesSamePlayer;
}


vector<Country*> Map::getEnemyCountries(Country* c) {
	vector<Country*> *countries = getCountries();
	vector<Country*> enemy;
	for (int i = 0; i < countries->size(); i++) {
		if (countries->at(i)->getId() != c->getId()) {
			if (countries->at(i)->getOwner()->getName() != c->getOwner()->getName()) {
				if (checkIsAdjacentByIndex(countries->at(i)->getId() - 1, c->getId() - 1)) {
					enemy.push_back(countries->at(i));
					cout << countries->at(i)->getId() << "\t\t" << countries->at(i)->getName() << "\t\t" << countries->at(i)->getArmies() << endl;
				}
			}
		}
	}
	return enemy;
}

























bool Map::checkIsAdjacent(Country *c1, Country *c2) {
	if (c2 == NULL)
		return false;
	return checkIsAdjacentByIndex((c1->getId() - 1), (c2->getId() - 1));
}

//making two countries adjacent, based on their names
//if one of the names is not associated with a country, an error message is displayed
void Map::makeAdjacent(string c1, string c2) {
	bool exists1 = false;
	bool exists2 = false;
	int target1;
	int target2;
	for (int i = 0; i < numCountries; i++) {
		if (((*countries)[i]->getName()) == c1) {
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


//making two countries NOT adjacent, based on their names
//if one of the names is not associated with a country, an error message is displayed
void Map::makeNotAdjacent(string c1, string c2) {
	bool exists1 = false;
	bool exists2 = false;
	int target1;
	int target2;
	for (int i = 0; i < numCountries; i++) {
		if (((*countries)[i]->getName()) == c1) {
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
		if (c1.compare(c2) != 0) {//make sure the user isn't trying to make a country NOT adjacent to itself... rascals...
			countriesAdj[target1 - 1][target2 - 1] = false;//modifying the adjacency matrix
			countriesAdj[target2 - 1][target1 - 1] = false;
			cout << c1 << " and " << c2 << " are now NOT adjacent." << endl;
		}
		else
			cout << c1 << " and " << c2 << " are the same country and it MUST remain adjacent to itself." << endl;
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
	for (int i = 0; i < getNumCountries(); i++) {
		if (((*countries)[i]->getName()) == n) {
			exists = true;
			target = (*countries)[i]->getId();
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

void Map::printAdjacentCountryNames(ofstream& fout, string n) {
	bool exists = false;
	int target;
	//making sure that the string is a valid country name
	for (int i = 0; i < getNumCountries(); i++) {
		if (((*countries)[i]->getName()) == n) {
			exists = true;
			target = (*countries)[i]->getId();
		}
	}
	//if it is a valid country name
	if (exists) {
		fout << "The following countries are adjacent to " << n << ": ";
		for (int i = 0; i < numCountries; i++) {
			if (countriesAdj[target - 1][i] == true) {
				fout << (*countries)[i]->getName() << " ";
			}
		}
		fout << " " << endl;
	}
	else {
		fout << "No such country could be found." << endl;
	}

}


//Preconditon: valid id numbers only
//This is a helper method mainly for the purpose of the demo
void Map::printAdjacentCountryNamesById(int n) {
	cout << "The following countries are adjacent to " << (*countries)[n - 1]->getName() << ": ";
	for (int i = 0; i < numCountries; i++) {
		if (countriesAdj[n - 1][i] == true) {
			cout << (*countries)[i]->getName() << " ";
		}
	}
	cout << " " << endl;
}


void Map::attach(Observer* obs) {






































	// first attach the observer to the map
	Subject::attach(obs);

	// now attach the observer to the countries
	for (vector<Country*>::iterator i = getCountries()->begin(); i != getCountries()->end(); ++i) {
		(*i)->attach(obs);
	}

	// now attach the observer to the continents
	for (vector<Continent*>::iterator i = getContinents()->begin(); i != getContinents()->end(); ++i) {
		(*i)->attach(obs);
	}

}