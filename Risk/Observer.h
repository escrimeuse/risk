#pragma once

#include "Subject.h"
#include"GamePlayers.h"

class Subject;
class GamePlayers;

class Observer {

public:

	Observer();
	~Observer();
	virtual void Update(Subject* sbj) = 0;
	virtual void Update(GamePlayers* gp) = 0;

};
