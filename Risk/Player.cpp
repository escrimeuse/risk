#include "Player.h"

using namespace std;


// Constructors
Player::Player() {

}

Player::Player(string aName) : name(aName) {

}

Player::Player(string aName, Country** countries, int num) : name(aName), ownedCountries(countries), numOfOwnedCountries(num) {

}


// Mutators

void Player::setOwnedCountries(Country** countries) {
	ownedCountries = countries;
}

void Player::setName(string aName) {
	name = aName;
}

void Player::setNumOwnedCountries(int num) {
	numOfOwnedCountries = num;
}


// Accessors

string Player::getName() {
	return name;
}

Country** Player::getOwnedCountries() {
	return ownedCountries;
}

int Player::getNumOfOwnedCountries() {
	return numOfOwnedCountries;
}




