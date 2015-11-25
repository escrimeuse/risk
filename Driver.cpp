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
#include "SaveDirector.h"
#include "SaveGameBuilder.h"
#include "SaveGame.h"


#include <iostream>
#include<sstream>
#include<list>

using namespace std;

int main() {

	// demonstrating loading a game from a file
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

	// demonstrating saving a game
	cout << "**************************************" << endl;
	cout << "   SAVING A GAME TO A FILE USING THE  " << endl;
	cout << "           BUILDER PATTERN            " << endl;
	cout << "**************************************" << endl;

	cout << "Creating the SaveBuilder object..." << endl;
	SaverLoader* mysaver = new SaverLoader("gamesaved");
	SaveGameBuilder* mysavebuilder = new SaveGame(newGame, mysaver);

	cout << "Creating the SaveDirector object..." << endl;
	SaveDirector* savechef = new SaveDirector(mysavebuilder);

	// the game can be saved at any time. To demonstrate this, we will do through the initial reinforcement phase
	// and ask the user if they want to save the game

	for (vector<Player*> ::iterator i = newGame->gamePlayers->begin(); i != newGame->gamePlayers->end(); ++i) {
		(*i)->placeArmiesOnCountriesLoop(10);

		cout << "Do you want to save the game? (Y or N) ";
		char save = ' ';
		cin >> save; 
		if (save == 'Y' || save == 'y') {
			cout << "Saving the game..." << endl;
			savechef->saveGame();
		}
	}



	cout << "**************************************" << endl;
	cout << " LOADING A GAME FROM A FILE USING THE " << endl;
	cout << "           BUILDER PATTERN            " << endl;
	cout << "**************************************" << endl;

	cout << "Creating the GameBuilder object..." << endl;
	SaverLoader* newgametoload2 = new SaverLoader("gamesaved");
	GameBuilder* thegamebuilder2 = new ExistingGameBuilder(newgametoload2);

	cout << "Creating the GameDirector object..." << endl;
	GameDirector* themainbuilder2 = new GameDirector(thegamebuilder2);

	cout << "Constructing the game..." << endl;
	themainbuilder2->constructGame();
	Game* newGame2 = themainbuilder2->returnGame();
	cout << "Game successfully loaded!" << endl;
}