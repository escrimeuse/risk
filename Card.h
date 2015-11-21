#pragma once

#include <string>

using namespace std;

enum cardType {
	infantry,
	artillery,
	cavalry,
	wild,
};

class Card {

private:
	string countryOnCard;
	cardType typeOfCard;

public: 
	Card(string country, cardType type);
	string getCountryOnCard() {
		return countryOnCard;
	}
	cardType getTypeOfCard() {
		return typeOfCard;
	}
};