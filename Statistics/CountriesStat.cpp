#include "CountriesStat.h"



CountriesStat::CountriesStat(Statistic * s) : StatisticDecorator(s)
{
}


CountriesStat::~CountriesStat()
{
	delete stat;
}
/*
	CountryStat specific update function
	Appends Country statistics to resulting
	statistic string and calls update from previous
decorated statistic
*/
void CountriesStat::update(string s) {
	cout << "Country Updated: " << players.size() << endl;
	for (int i = 0; i < players.size(); i++) {
		s += "Countries Owned: " + to_string(players[i]->getNumOfOwnedCountries()) + "\t\t|\t";
	}
	s += "\n\n";
	stat->update(s);
}
