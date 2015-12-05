#pragma once
#include "../ObserverPattern/Observer.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include <vector>
using namespace std;

class Log : public Observer {

public:
	Log(); 
	~Log();
	virtual string getCurrentPhases(); //get the current phases for each player
	virtual void update(int code);
	void UpdateLogFile(string l);
	virtual void attachPlayer(Player* p);
	virtual void attachMap(Map* map);
	void update();

protected:
	vector<Player*> players;
	const string fileName = "GameLog.log";
	Map* map;

};