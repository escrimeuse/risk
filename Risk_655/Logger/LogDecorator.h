#pragma once

#include "Log.h"

class LogDecorator : public Log {

public:
	LogDecorator(); 
	LogDecorator(Log* l); 
	~LogDecorator(); 
	void attachPlayer(Player* p); 

protected:
	Log* log;

};