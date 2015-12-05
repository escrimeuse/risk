#include "ArmiesStat.h"


ArmiesStat::ArmiesStat(Statistic * s) : StatisticDecorator(s)
{
}

ArmiesStat::~ArmiesStat()
{
	delete stat;
}

/*
ArmiesStat specific update function

Appends Army statistics to resulting
statistic string and calls update from previous
decorated statistic
*/

void ArmiesStat::update(string s) {
	for (int i = 0; i < players.size(); i++) {
		s += "Total Number of Armies: " + to_string(players[i]->getTotalNumArmies()) + "\t|\t";
	}
	s += "\n";
	stat->update(s);
}
