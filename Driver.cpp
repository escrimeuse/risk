#include "Map.h"
#include "MapDemo.h"	
#include "Player.h"
#include "Country.h"
#include "Startphase.h"
#include "Fortification.h"
#include "SaveLoader.h"
#include "Game.h"
#include <string>
#include <iostream>
#include "GameDirector.h"
#include "GameBuilder.h"
#include "ExistingGameBuilder.h"

#include <iostream>
#include<sstream>
#include<list>

using namespace std;

int main() {
	cout << "**************************************" << endl;
	cout << " LOADING A GAME FROM A FILE USING THE " << endl;
	cout << "           BUILDER PATTERN            " << endl;
	cout << "**************************************" << endl;

	cout << "Creating the GameBuilder object..." << endl;
	SaverLoader* newgametoload = new SaverLoader("gametoload");
	GameBuilder* thegamebuilder = new ExistingGameBuilder(newgametoload);

	cout << "Creating the GameDirector object..." << endl;
	GameDirector* themainbuilder = new GameDirector(thegamebuilder);

	cout << "Constructing the game..." << endl;
	themainbuilder->constructGame();
	Game* newGame = themainbuilder->returnGame();
	cout << "Game successfully loaded!" << endl;


}