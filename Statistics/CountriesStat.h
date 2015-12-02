#pragma once
#include "StatisticDecorator.h"
class CountriesStat :
	public StatisticDecorator
{
public:
	CountriesStat(Statistic* s);
	~CountriesStat();
	virtual void update(string s);
};

