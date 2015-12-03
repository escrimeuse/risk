#include "FortificationLog.h"
#include "../Game/Fortification.h"
#include <fstream>
#include <iostream>

FortificationLog::FortificationLog(Log * l) :LogDecorator(l) {
}


FortificationLog::~FortificationLog() {
	delete log;
}

void FortificationLog::update(int code) {
	if (code == Fortification::FORTIFICATION_ID) {
		ofstream outfile;
		cout << "Fortification Logged" << endl;
		outfile.open(fileName, std::ios_base::app);
		outfile << "Done Fortification Phase" << endl;
	}
	else
		log->update(code);
}