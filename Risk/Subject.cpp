#include "Subject.h"
#include "Observer.h"


Subject::Subject(){
	 observers = new list<Observer*>;
}

Subject::~Subject() {
	delete observers;
}

void Subject::Attach(Observer* ob){
	observers->push_back(ob);
}

void Subject::Detach(Observer* ob) {
	observers->remove(ob);
}

void Subject::Notify() {
	list<Observer *>::iterator i = observers->begin();
	for (; i != observers->end(); ++i)
		(*i)->Update(this);
}

void Subject::Notify(Subject* sbj) {
	list<Observer *>::iterator i = observers->begin();
	for (; i != observers->end(); ++i)
		(*i)->Update(sbj);
}

void Subject::Notify(GamePlayers* gp) {
	list<Observer *>::iterator i = observers->begin();
	for (; i != observers->end(); ++i)
		(*i)->Update(gp);
}