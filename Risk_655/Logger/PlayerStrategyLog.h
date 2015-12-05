#pragma once

#include"LogDecorator.h"

class PlayerStrategyLog : public LogDecorator {
public:
	PlayerStrategyLog(Log* l);
	~PlayerStrategyLog();
	virtual void update(int code);
};