// Assignment #2 - COMP345 - Section DI - Fall 2015
// Author: Jennifer Sunahara (27590628)
//
//This is the implementation file Country.cpp for the class Country.
//The interface for the class Country is in the header file Country.h.

#include "Player.h"
#include<string>
#include<iostream>
using namespace std;

#include "Country.h"

int Country::countryCount=0;

Country::Country() {
	cout << "Non-Default country constructor\n";
	id = ++countryCount;
	owner = NULL;
	isOwned = false;
	armies = 0;
}

Country::Country(string aname, int aid, int aarmies, bool aowned, Player* o):name(aname) {
	cout << "Non-Default country constructor\n";
	id = aid;
	armies = aarmies;
	isOwned = aowned;
	owner = o;
	++countryCount;
}
//accessors used to be inline, but it caused a problem with the linker.
string Country::getName() const {
	return name;
}

Player* Country::getOwner() const {
	return owner;
}

bool Country::getIsOwned() const {
	return isOwned;
}

int Country::getArmies() const {
	return armies;
}

int Country::getCount() {
	return countryCount;
}

int Country::getId() const {
	return id;
}

void Country::setName(string n) {
	name = n;
}

void Country::setOwner(Player* o) {
	owner = o;
	setIsOwned(true);
}

void Country::setIsOwned(bool o) {
	isOwned= o;
}

void Country::setArmies(int a) {
	armies = a;
}

//this method only exists for demo purposes (to reset the countryCount to 0 when a new menu option is selected)
void Country::resetCount() {
	countryCount = 0;
}


