#pragma once

#include"LogDecorator.h"
#include "../Game/Battle.h"

class PlayerCountryLog : public LogDecorator {
public:
	PlayerCountryLog(Log* l);
	~PlayerCountryLog();
	virtual void update(int code);
};