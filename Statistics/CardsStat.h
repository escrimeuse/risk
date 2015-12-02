#pragma once
#include "StatisticDecorator.h"
class CardsStat :
	public StatisticDecorator
{
public:
	CardsStat(Statistic* s);
	~CardsStat();
	virtual void update(string s);
};

