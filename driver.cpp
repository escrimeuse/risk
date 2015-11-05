/*
 * driver.cpp
 *
 *  Created on: Oct 23, 2015
 *      Author: cclp94
 */
#include <iostream>
#include "map.h"
#include "saverLoader.h"

#define PREDEFINED_MAPS 3

using namespace std;

static int countryCounter = 0;

Country c1, c2, c3;
Continent continent1, continent2;
Map map;

void setCountry(Country& country, string name, int troups, int owner);
void initializeMap(const string name);
void createMap(string name);

int main(){
	const std::string predefinedMaps[PREDEFINED_MAPS] = {"Canada", "Brazil", "United States"};		// Predefined countries hard coded
	SaverLoader *s;
	char option;
	int mapOption;
	cout << "Would you like to save or load a file (s/l): ";
	cin >> option;
	if(option == 's'){			// if save option selected
		cout << "select one of the predefined maps to save: " << endl;
		cout << "0. Canada" << endl;
		cin >> mapOption;
		switch (mapOption){
		case 0:
			s = new SaverLoader(predefinedMaps[mapOption]);		// initialize saverLoader obj with selected file name
			createMap(predefinedMaps[mapOption]);				// create selected map

			s->save(map);										// save map
			MapAPI::displayMap(&map);							// display map
			//Deallocate Space											// deallocates
			delete [] continent1.countries;
			delete [] continent2.countries;
			for(int i =0; i < map.numCountries;i++)
			    delete [] map.adjencecies[i];
			delete [] map.adjencecies;
		}
	}else{					// load option selected
		cout << "select one of the predefined maps to load: " << endl;
		for(int i = 0; i < PREDEFINED_MAPS; i++)
			cout << i <<". " << predefinedMaps[i] << endl;		// choose predefined maps
		cin >> mapOption;
		s = new SaverLoader(predefinedMaps[mapOption]);			// creates saverLoader obj with file name
		Map* map2 = s->load();									// load map from selected file
		MapAPI::displayMap(map2);								// displays map
		MapAPI::deleteMap(map2);								// deallocated map
	}
    delete s;													// delete saverLoader obj
    return 0;
}
/**
 * Hard coded implementation of a map creation
 */
void createMap(const string name){
	// creates countries
	setCountry(c1, "Montreal", 3, 1);
	setCountry(c2, "Quebec City", 2, 3);
	setCountry(c3, "Toronto", 5, 1);
	//Creates continents
	continent1.name = "Quebec";
	continent1.countries = new int[2];
	continent2.countries = new int[1];
	continent1.countries[0] = c1.id;
	continent1.numCountries++;
	continent1.countries[1] = c2.id;
	continent1.numCountries++;
	continent2.name = "Ontario";
	continent2.countries[0] = c3.id;
	continent2.numCountries++;
	// fill map
	initializeMap(name);
}


/**
 * Sets values to country attributes
 */
void setCountry(Country& country, string name, int troups, int owner){
    countryCounter++;
    country.name = name;
    country.troops = troups;
    country.owner = owner;
    country.id = countryCounter;
}
/**
 * fill map with countries and continents and its connections
 * @param name name of the map
 */
void initializeMap(const string name){
    map.name = name;
    map.countries = new Country[countryCounter];
    map.countries[0] = c1;
    map.countries[1] = c2;
    map.countries[2] = c3;
    map.numCountries = countryCounter;
    map.continents = new Continent[2];
    map.continents[0] = continent1;
    map.continents[1] = continent2;
    map.numContinents = 2;
    map.adjencecies = new bool*[countryCounter];
    for (int i = 0; i < countryCounter; ++i)
    {
        map.adjencecies[i] = new bool[countryCounter];
    }


    map.adjencecies[0][0] = true;
    map.adjencecies[0][1] = true;
    map.adjencecies[0][2] = true;

    map.adjencecies[1][0] = true;
    map.adjencecies[1][1] = true;
    map.adjencecies[1][2] = false;

    map.adjencecies[2][0] = true;
    map.adjencecies[2][1] = false;
    map.adjencecies[2][2] = true;
}



