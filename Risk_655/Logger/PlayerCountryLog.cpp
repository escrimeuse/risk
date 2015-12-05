#include "PlayerCountryLog.h"
#include "../Game/Battle.h"
#include <fstream>
#include <iostream>

PlayerCountryLog::PlayerCountryLog(Log * l) :LogDecorator(l) {
}


PlayerCountryLog::~PlayerCountryLog() {
	delete log;
}

void PlayerCountryLog::update(int code) {
	if (code == Player::COUNTRY1_ID || code == Player::COUNTRY2_ID) {
		ofstream outfile;
		outfile.open(fileName, std::ios_base::app);
		if(code == Player::COUNTRY1_ID)
			outfile << "===== Player has add a Country! =====" << endl;
		else
			outfile << "===== Player has lost a Country! =====" << endl;
	}
	else
		log->update(code);
}
