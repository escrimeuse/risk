#pragma once

#include"LogDecorator.h"
#include "../Game/Battle.h"

class PlayerCardsLog : public LogDecorator {
public:
	PlayerCardsLog(Log* l);
	~PlayerCardsLog();
	virtual void update(int code);
};