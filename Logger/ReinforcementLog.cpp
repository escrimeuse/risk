#include "ReinforcementLog.h"
#include "../Player/Player.h"
#include <fstream>
#include <iostream>

ReinforcementLog::ReinforcementLog(Log * l) :LogDecorator(l) {
}


ReinforcementLog::~ReinforcementLog() {
	delete log;
}

void ReinforcementLog::update(int code) {
	if (code == Player::REINFORCEMENT_ID) {
		ofstream outfile;
		cout << "reinforcement Logged" << endl;
		outfile.open(fileName, std::ios_base::app);
		outfile << "Done Battle Phase" << endl;
	}
	else
		log->update(code);
}