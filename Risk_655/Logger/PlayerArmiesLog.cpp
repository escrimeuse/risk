#include "PlayerArmiesLog.h"
#include "../Game/Battle.h"
#include <fstream>
#include <iostream>

PlayerArmiesLog::PlayerArmiesLog(Log * l) :LogDecorator(l) {
}


PlayerArmiesLog::~PlayerArmiesLog() {
	delete log;
}

void PlayerArmiesLog::update(int code) {
	if (code == Player::ARMIES_ID) {
		ofstream outfile;
		outfile.open(fileName, std::ios_base::app);
		outfile << "===== Player's Armies Changed! =====" << endl;
	}
	else
		log->update(code);
}
