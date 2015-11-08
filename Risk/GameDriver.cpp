#include "Startphase.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
	
	vector <GamePlayers*> activePlayers;
	Startphase start;
	start.welcome();
	start.initializeNumOfGamePlayers(activePlayers);
	start.createPlayers(activePlayers);
	start.initializePlayersTurn(activePlayers);
	start.assignCountries(activePlayers);
	
	
return 0;
}

