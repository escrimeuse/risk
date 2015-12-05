#pragma once

#include <iostream>
#include "../ObserverPattern/Observer.h"
#include <vector>
#include "../Player/Player.h"

using namespace std;

class Statistic : public Observer
{
protected:
	vector<Player*> players;
	const string fileName = "GameStats.stat";
public:
	virtual std::string getCurrentStats(); // Get Statistics that are being mesured
	Statistic();
	~Statistic();
	virtual void update();
	virtual void update(string s);
	void UpdateStatFile(std::string s);
	virtual void attachPlayer(Player* p);
};

