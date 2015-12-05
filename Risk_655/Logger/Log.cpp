#include "Log.h"
#include <iostream>
#include <fstream>
using namespace std;

Log::Log() {
}

Log::~Log() {
}

string Log::getCurrentPhases() {
	return string();
}
/*updates the file*/
void Log::UpdateLogFile(std::string s) {
	ofstream out(fileName);
	cout << "File Created" << endl;
	out << s;
}

void Log::update() {
}

void Log::update(int code) {
}

void Log::attachPlayer(Player* p) {
	players.push_back(p);
}

void Log::attachMap(Map* map) {
	map = map;
}
