#include "Statistic.h"
#include <fstream>




std::string Statistic::getCurrentStats()
{
	return std::string();
}

Statistic::Statistic()
{
}


Statistic::~Statistic()
{
}
/*
	Update the file with all statistics
	the function is called when all the 
	statistics, including decorators, are called.
*/
void Statistic::UpdateStatFile(std::string s) {
	ofstream out(fileName);
	out << s;
}
/*
	First call and Subject notifies statistic
	add the "header" with player's info to the stats
	it then calls class specific update function
*/
void Statistic::update() {
	string s = "";
	for (int i = 0; i < players.size(); i++) {					// For each attached player	
		s += "Player: " + players[i]->getName() + "\t\t\t|\t";	// Write name

	}
	s += "\n";
	update(s);
}
/*
	This is the final function that can be called by update
	It then calls the function that writes the file
*/
void Statistic::update(string s) {
	UpdateStatFile(s);
}
/*
	attach player to the Statistic
*/
void Statistic::attachPlayer(Player* p) {
	players.push_back(p);
}
