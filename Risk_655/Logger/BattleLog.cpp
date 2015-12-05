#include "BattleLog.h"
#include "../Game/Battle.h"
#include <fstream>
#include <iostream>

BattleLog::BattleLog(Log * l) :LogDecorator(l) {
}


BattleLog::~BattleLog() {
	delete log;
}

void BattleLog::update(int code) {
	cout << "Battle Logged" << endl;
	if (code == Battle::BATTLE_ID) {
		ofstream outfile;
		cout << "Battle Logged" << endl;
		outfile.open(fileName, std::ios_base::app);
		outfile << "Done Battle Phase" << endl;
	}
	else
		log->update(code);
}
