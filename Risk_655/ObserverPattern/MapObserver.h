#ifndef MAPOBSERVER_H
#define MAPOBSERVER_H
#include "../Map/Map.h"
#include "Observer.h"
#include <fstream>

using namespace std;

class MapObserver : public Observer{

private:
	Map* subject;
	void displayMap(); 
	
public: 
	MapObserver(); // default constructor
	MapObserver(Map* mapSubject); // constructor that sets the map being observed
	void update(); 
	

};


#endif