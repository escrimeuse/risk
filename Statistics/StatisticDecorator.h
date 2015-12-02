#pragma once
#include "Statistic.h"
class StatisticDecorator :
	public Statistic
{
protected:
	Statistic * stat;
public:
	StatisticDecorator();
	StatisticDecorator(Statistic* s);
	~StatisticDecorator();
	void attachPlayer(Player* p);
};

