#pragma once
#include <vector>
class Observer;

using std::vector;

class Subject
{
private:
	vector<Observer*> observers;
public:
	Subject();
	~Subject();
	void notify(int code);
	void attach(Observer* o);
	void detach(Observer* o);
};

