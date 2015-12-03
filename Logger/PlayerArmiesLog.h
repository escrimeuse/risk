#pragma once

#include"LogDecorator.h"
#include "../Game/Battle.h"

class PlayerArmiesLog : public LogDecorator {
public:
	PlayerArmiesLog(Log* l);
	~PlayerArmiesLog();
	virtual void update(int code);
};