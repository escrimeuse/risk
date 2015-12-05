#include "LogDecorator.h"

LogDecorator::LogDecorator()
{
}


LogDecorator::LogDecorator(Log* l)
{
	this->log = l;
}

LogDecorator::~LogDecorator()
{
	delete this->log;
}

void LogDecorator::attachPlayer(Player * p)
{
	players.push_back(p);
	log->attachPlayer(p);
}
