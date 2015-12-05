#include "Subject.h"
#include "Observer.h"
#include "../Logger/Log.h"

#include <iostream>

using namespace std;

Subject::Subject()
{
}


Subject::~Subject()
{
}
/*
	Notify all attached observers to update
*/
void Subject::notify(int code)
{
	for (int i = 0; i < observers.size(); i++) {
		Log *l = dynamic_cast<Log*> (observers[i]);
		if (l == NULL) {
			observers[i]->update();
		}
		else {
			l->update(code);
		}
	}
}

/*
	Attach observer to subject
*/
void Subject::attach(Observer* o) {
	observers.push_back(o);
}
void Subject::detach(Observer* o) {
	for (int i = 0; i < observers.size(); i++) {
		if (observers[i] == o)
			delete observers[i];
	}
}
