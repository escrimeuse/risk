#include "CardsStat.h"



CardsStat::CardsStat(Statistic * s) : StatisticDecorator(s)
{
}


CardsStat::~CardsStat()
{
	delete stat;
}
/*
CardStat specific update function
Appends Cards statistics to resulting
statistic string and calls update from previous
decorated statistic
*/
void CardsStat::update(string s) {
	cout << "Cards Updated: " << endl;
	for (int i = 0; i < players.size(); i++) {
		s += "Number of Artillery Cards: " + to_string(players[i]->getNumCardsArtillery()) + "\t|\t";
	}
	s += "\n";
	for (int i = 0; i < players.size(); i++) {
		s += "Number of Cavalry Cards: " + to_string(players[i]->getNumCardsCavalry()) + "\t|\t";
	}
	s += "\n";
	for (int i = 0; i < players.size(); i++) {
		s += "Number of Infantry Cards: " + to_string(players[i]->getNumCardsInfanty()) + "\t|\t";
	}
	s += "\n\n";
	stat->update(s);
}
