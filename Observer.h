#ifndef OBS_H
#define OBS_H
#include "Subject.h"
#include "Player.h"


class Subject;
class Player;

class Observer {

public:

	Observer();
	~Observer();
	virtual void Update(Subject* sbj) = 0;
	virtual void Update(GamePlayers* gp) = 0;

};

#endif
