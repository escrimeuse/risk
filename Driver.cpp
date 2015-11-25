/*
COMP345 - Assignment 3
Section D DI
Author: Cathryn Griffiths (29108777)
Description: This is Part 2 (Game Save/Load Builder Pattern). Note that since the assignment requires
a lot of code that is part of the Risk project that has been written by my teammates previously to
this assignment, I would like to point on which classes/functions were written by me for the purposes
of this assignment:

Driver (.cpp)
GameDirector (.h and .cpp)
GameBuilder (.h and .cpp)
ExistingGameBuilder (.h and .cpp)
SaveDirector (.h and .cpp)
SaveGameBuilder (.h and .cpp)
SaveGame (.h and .cpp)

within SaverLoader, the following functions were written by me:
vector<Player*>* loadPlayers();
list<Card*>* loadCards(cardType card);
string loadCurrentPlayer();
int loadCurrentPhase();
int loadNumCardSetsTradedIn();
void savePlayersAndCards(Game* game);
void saveState(Game* game);
(small changes were also made to the savingMap(Map) function

*/

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
#include <sstream>
#include <list>

using namespace std;

int main() {

	// demonstrating loading a game from a file
	cout << "**************************************" << endl;
	cout << " LOADING A GAME FROM A FILE USING THE " << endl;
	cout << "           BUILDER PATTERN            " << endl;
	cout << "**************************************" << endl;
	cout << endl;
	cout << "Creating the GameBuilder object..." << endl;
	SaverLoader* newgametoload = new SaverLoader("gametoload");
	GameBuilder* thegamebuilder = new ExistingGameBuilder(newgametoload);

	cout << "Creating the GameDirector object..." << endl;
	GameDirector* themainbuilder = new GameDirector(thegamebuilder);
	cout << "Constructing the game..." << endl;
	themainbuilder->constructGame();
	Game* newGame = themainbuilder->returnGame();
	cout << "Game successfully loaded!" << endl;
	cout << endl;

	// demonstrating saving a game
	cout << "**************************************" << endl;
	cout << "   SAVING A GAME TO A FILE USING THE  " << endl;
	cout << "           BUILDER PATTERN            " << endl;
	cout << "**************************************" << endl;
	cout << endl;
	cout << "This program will now demonstrate the saving of a game in progress." << endl;
	cout << "Note that for the purposes and scope of this assignment, " << endl;
	cout << "saving of a game in progress will only be demonstrated for the " << endl;
	cout << "country reinforcement stage. Note however that the code for " << endl;
	cout << "saving the game can be called at any point in the actual " << endl;
	cout << "playing of the game. " << endl << endl;
	

	// the game can be saved at any time. To demonstrate this, we will do through the initial reinforcement phase
	// and ask the user if they want to save the game

	for (vector<Player*> ::iterator i = newGame->gamePlayers->begin(); i != newGame->gamePlayers->end(); ++i) {
		(*i)->placeArmiesOnCountriesLoop(10);

		cout << "Do you want to save the game? (Y or N) ";
		char save = ' ';
		cin >> save; 
		if (save == 'Y' || save == 'y') {
			// Note that to save a game at any point during a game in progress, 
			// we would just need to insert the folowing lines into the code: 

			cout << "Creating the SaveBuilder object..." << endl;
			SaverLoader* mysaver = new SaverLoader("gamesaved");
			SaveGameBuilder* mysavebuilder = new SaveGame(newGame, mysaver);
			cout << "Creating the SaveDirector object..." << endl;
			SaveDirector* savechef = new SaveDirector(mysavebuilder);
			savechef->saveGame();
			cout << "Successfully saved the game" << endl;
		}
	}


	cout << endl << endl;
	
}