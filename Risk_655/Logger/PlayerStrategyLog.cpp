#include "PlayerStrategyLog.h"
#include "../Game/Battle.h"
#include <fstream>
#include <iostream>

PlayerStrategyLog::PlayerStrategyLog(Log * l) :LogDecorator(l) {
}


PlayerStrategyLog::~PlayerStrategyLog() {
	delete log;
}

void PlayerStrategyLog::update(int code) {
	if (code == Player::ARMIES_ID) {
		ofstream outfile;
		outfile.open(fileName, std::ios_base::app);
		outfile << "===== Player's Strategy Changed! =====" << endl;
	}
	else
		log->update(code);
}
