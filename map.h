/*
 * map.h
 *
 *  Created on: Oct 23, 2015
 *      Author: cclp94
 */
#ifndef MAP_H
#define MAP_H

#include <iostream>

using namespace std;

struct Country {
    string name;
    int troops;
    int owner;
    int id;
};

struct Continent {
    string name;
    int numCountries;
    int* countries;
};

struct Map{
    string name;
    Country* countries;
    int numCountries;
    Continent* continents;
    int numContinents;
    bool** adjencecies;
};

namespace MapAPI{
	void deleteMap(Map* map);
	void infoMap(Map* map);
	void listCountries(Map* map);
	void listContinents(Map* map);
	void displayMap(Map* map);
}

#endif



