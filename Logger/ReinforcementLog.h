#pragma once

#include"LogDecorator.h"

class ReinforcementLog :public LogDecorator {
public:
	ReinforcementLog(Log* l);
	~ReinforcementLog();
	virtual void update(int code);
};