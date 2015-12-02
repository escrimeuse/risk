#include "Subject.h"
#include "Observer.h"

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
void Subject::notify()
{
	for (int i = 0; i < observers.size(); i++) {
		observers[i]->update();
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
