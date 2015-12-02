#include "StatisticDecorator.h"



StatisticDecorator::StatisticDecorator()
{
}


StatisticDecorator::StatisticDecorator(Statistic* s)
{
	this->stat = s;
}

StatisticDecorator::~StatisticDecorator()
{
	delete this->stat;
}
/*
	Attach players to the current stat
	and calls attachPlayer in previous
	decorated stat
*/
void StatisticDecorator::attachPlayer(Player * p)
{
	players.push_back(p);
	stat->attachPlayer(p);
}
