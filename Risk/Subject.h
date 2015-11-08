#pragma once

#include "Observer.h"
#include <list>
using namespace std;

class Observer;
class GamePlayers;


class Subject {

public:

	Subject();
	~Subject();
	virtual void Attach(Observer* ob);
	virtual void Detach(Observer* ob);
	virtual void Notify();
	virtual void Notify(Subject* sbj);
	virtual void Notify(GamePlayers* gp);

private:

	list<Observer*> *observers;

};