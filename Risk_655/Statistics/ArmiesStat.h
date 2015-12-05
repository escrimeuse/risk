#pragma once
#include "StatisticDecorator.h"
class ArmiesStat :
	public StatisticDecorator
{
public:
	ArmiesStat(Statistic* s);
	~ArmiesStat();
	virtual void update(string s);
};

