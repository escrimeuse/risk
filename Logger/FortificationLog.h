#pragma once

#include "LogDecorator.h"
#include "../Game/Fortification.h"
#include "../Map/Map.h"

class FortificationLog : public LogDecorator {
public:
	FortificationLog(Log* l);
	~FortificationLog();
	virtual void update(int code);
};