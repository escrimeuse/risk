#pragma once

#include"LogDecorator.h"
#include "../Game/Battle.h"

class BattleLog : public LogDecorator {
public:
	BattleLog(Log* l);
	~BattleLog();
	virtual void update(int code);
};