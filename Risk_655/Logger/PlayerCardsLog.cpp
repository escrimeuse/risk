#include "PlayerCardsLog.h"
#include "../Game/Battle.h"
#include <fstream>
#include <iostream>

PlayerCardsLog::PlayerCardsLog(Log * l) :LogDecorator(l) {
}


PlayerCardsLog::~PlayerCardsLog() {
	delete log;
}

void PlayerCardsLog::update(int code) {
	if (code == Player::CARDS_ID) {
		ofstream outfile;
		outfile.open(fileName, std::ios_base::app);
		outfile << "===== Player's Cards Changed! =====" << endl;
	}
	else
		log->update(code);
}
