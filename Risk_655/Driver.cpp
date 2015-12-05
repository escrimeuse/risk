#include "Map/Map.h"
#include "Player/Player.h"
#include "Map/Country.h"
#include "Game/Startphase.h"
#include "Game/Fortification.h"
#include "SaveLoad/SaverLoaderTwoWayAdapter.h"
#include "Game/Battle.h"
#include "GameBuilder\ExistingGameBuilder.h"
#include "GameBuilder\GameDirector.h"
#include "GameBuilder\GameBuilder.h"
#include "GameSaver/SaveGame.h"
#include "GameSaver/SaveDirector.h"
#include "GameSaver/SaveGameBuilder.h"
#include "ObserverPattern\MapObserver.h"
#include "ObserverPattern\PlayerView.h"

#include <string>
#include <iostream>

#include <iostream>
#include<sstream>
#include<list>

using namespace std;

namespace mapDemo {

	static int adjAction(int choice, Map *myMap) {
		switch (choice) {
		case 1: {
			cout << "\nLet's make 2 countries adjacent."
				<< "\nWhich two countries would you like to make adjacent?\n"
				<< "First country: ";
			string c1, c2;
			cin >> c1;
			cout << "Second country: ";
			cin >> c2;
			myMap->makeAdjacent(c1, c2);
			myMap->printAdjacentCountryNames(c1);
			myMap->printAdjacentCountryNames(c2);
			return 0;
		}
		case 2: {
			cout << "\nLet's make 2 countries NOT adjacent."
				<< "\nWhich two countries would you like to make NOT adjacent?\n"
				<< "First country: ";
			string c1, c2;
			cin >> c1;
			cout << "Second country: ";
			cin >> c2;
			myMap->makeNotAdjacent(c1, c2);
			myMap->printAdjacentCountryNames(c1);
			myMap->printAdjacentCountryNames(c2);
			return 0;
		}
		case 3: {
			bool continentsValid = false;
			bool mapConnected = false;

			//Continent validity test
			cout << "\n Let's test the map for continent validity (1 if valid, 0 otherwise)." << endl;
			string check = "";
			continentsValid = myMap->getContinentsValid();//test if the map's continents are valid
			if (continentsValid)
				check = "true";
			else
				check = "false";
			cout << "\nContinents Valid?: " << check << endl;

			//Connectivity test
			cout << "\n Let's test the map for connectivity (1 if valid, 0 otherwise)." << endl;
			check = ""; // precaution...
			mapConnected = myMap->getIsConnected(); //test if the map is connected
			if (mapConnected)
				check = "true";
			else
				check = "false";
			cout << "\nAll countries connected?: " << check << endl;

			//Saving (if both tests pass)
			if (continentsValid && mapConnected) {
				cout << "We will save the map. Which format (conquest or normal)?" << endl;
				string saveType = "";
				cin >> saveType;
				while (saveType != "conquest" && saveType != "normal") {
					cout << "That is not an valid choice. Which format (conquest or normal)?" << endl;
					cin >> saveType;
				}
				if (saveType == "normal") {
					SaverLoader *s = new SaverLoader("TestMapNormal");
					SaverLoaderTwoWayAdapter *SLadapter = new SaverLoaderTwoWayAdapter(s);
					SLadapter->saveNormalMap(myMap);
					cout << "Saved map as 'TestMapConquest.map'\n"
						<< "Returning to main menu!\n" << endl;
					delete s;
					delete SLadapter;
					Continent *sacrificialContinent = (*(myMap->getContinents()))[0];
					sacrificialContinent->resetCount();
					Country *sacrificialCountry = (*(myMap->getCountries()))[0];
					sacrificialCountry->resetCount();
					delete myMap;
					return 500;
				}
				else if (saveType == "conquest") {
					ConquestSaverLoader *cs = new ConquestSaverLoader("TestMapConquest");
					SaverLoaderTwoWayAdapter *SLadapter = new SaverLoaderTwoWayAdapter(cs);
					SLadapter->saveConquestMap(myMap);
					cout << "Saved map as 'TestMapConquest.map'\n"
						<< "Returning to main menu!\n" << endl;
					delete cs;
					delete SLadapter;
					Continent *sacrificialContinent = (*(myMap->getContinents()))[0];
					sacrificialContinent->resetCount();
					Country *sacrificialCountry = (*(myMap->getCountries()))[0];
					sacrificialCountry->resetCount();
					delete myMap;
					return 500;
				}

			}
			else {
				cout << "Cannot save the map in its current state..." << endl;
				return 0;
			}
		}
		}
		return 0;

	}

	//finalizing map (creating and removing adjacencies before saving)
	static void finalize(Map *myMap) {

		while (true) {
			cout << "\nWhat would you like to do?:\n"
				<< "[ 1 ] Create adjacency\n"
				<< "[ 2 ] Remove adjacency\n"
				<< "[ 3 ] Save map\n"
				<< "[ 4 ] Exit\n" << endl;
			string input = "";
			getline(cin, input);

			// This code converts from string to number safely.
			stringstream myStream(input);
			int userChoice = 0;
			if (myStream >> userChoice) {
				if (userChoice == 4)
					return;
				int adj = adjAction(userChoice, myMap);
				if (adj == 500)
					return;
			}
			else
				cout << "Not a valid choice. Please try again" << endl;
		}
		return;//shouldn't reach this
	}

	//demonstration of the map-creation
	static void makeMap() {
		string mapName;
		int numberOfCountries;
		int numberOfContinents;
		bool isValid = false;
		string userIn;
		cout << "\nWhat is the name of the map you want to make?: ";
		cin >> mapName;

		do {
			cout << "\nWhat is the number of continents in " << mapName << "?: ";
			string input = "";
			int userChoice = 0;
			getline(cin, input);

			// This code converts from string to number safely.
			stringstream myStream(input);
			if (myStream >> userChoice) {
				numberOfContinents = userChoice;
				isValid = true;
			}
			else
				cout << "Not a valid choice. Please try again" << endl;

		} while (!isValid);

		isValid = false;//reseting it here because we are about to reuse it

		do {
			cout << "\nWhat is the number of countries in " << mapName << "?: ";
			string input = "";
			int userChoice = 0;
			getline(cin, input);

			// This code converts from string to number safely.
			stringstream myStream(input);
			if (myStream >> userChoice) {
				if (userChoice >= numberOfContinents) {
					numberOfCountries = userChoice;
					isValid = true;
				}
				else
					cout << "Cannot have fewer countries than continents. Please try again" << endl;
			}
			else
				cout << "Not a valid choice. Please try again" << endl;

		} while (!isValid);

		Map *newMap = new Map(mapName, numberOfCountries, numberOfContinents);

		cout << "\n" << newMap->getName() << " has "
			<< newMap->getNumContinents() << " continents and "
			<< newMap->getNumCountries() << " countries.\n\n"
			<< "Please name your continents: " << endl;
		newMap->setContinentNames();

		cout << "All continents have been named. The names are: " << newMap->getContinentNames() << "\n"
			<< "Please name your countries: " << endl;
		newMap->setCountryNames();

		cout << "\nAll countries have been named. The names are: " << newMap->getCountryNames() << "\n\n"
			<< "Now, please assign your countries to continents." << endl;
		newMap->setContinentCountries();

		cout << endl;

		//printing the countries per continent
		for (int i = 0; i < numberOfContinents; i++) {
			newMap->printContinentsCountries(i + 1);
		}

		cout << endl;

		//allow user to create or remove adjacencies and save
		finalize(newMap);

		std::cin.ignore();
		return;
	}
	//making changes to the map
	static int mapEditAction(int choice, Map *m) {
		switch (choice) {
		case 1: {cout << "The map's current name is " << m->getName() << ". What is its new name?: ";
			string input = "";
			getline(cin, input);
			m->setName(input);
			cout << "The map's name is " << m->getName() << ".\n";
			return 0;
		}
		case 2: {cout << "CONTINENTS: " << m->getContinentNames() << "\n"
			<< "Which continent's name do you want to change?: ";
			string toChange = "";
			string changeTo = "";
			cin >> toChange;
			cout << "What do you want to change it to?: ";
			cin >> changeTo;
			Continent *target = m->getContinentByName(toChange);
			if (target != NULL) {
				target->setName(changeTo);
				cout << "Continent name is " << target->getName() << ".\n";
			}
			else {
				cout << toChange << " is not a valid continent name. \n";
			}
			return 0;
		}
		case 3: {cout << "COUNTRIES: " << m->getCountryNames() << "\n"
			<< "Which country's name do you want to change?: ";
			string toChange = "";
			string changeTo = "";
			getline(cin, toChange);
			cout << "What do you want to change it to?: ";
			getline(cin, changeTo);
			Country *target = m->getCountryByName(toChange);
			if (target != NULL) {
				target->setName(changeTo);
				cout << "Country name is " << target->getName() << ".\n";
			}
			else {
				cout << toChange << " is not a valid country name. \n";
			}
			return 0;
		}
		case 4: {
			//allow user to create adjacency
			cout << "\nWhich two countries would you like to make adjacent?\n"
				<< "First country: ";
			string c1, c2;
			cin >> c1;
			cout << "Second country: ";
			cin >> c2;
			m->makeAdjacent(c1, c2);
			m->printAdjacentCountryNames(c1);
			m->printAdjacentCountryNames(c2);
			return 0;
		}
		case 5: {//allow user to make two countries NOT adjacent
			cout << "\nWhich two countries would you like to make NOT adjacent?\n"
				<< "First country: ";
			string c1, c2;
			cin >> c1;
			cout << "Second country: ";
			cin >> c2;
			m->makeNotAdjacent(c1, c2);
			m->printAdjacentCountryNames(c1);
			m->printAdjacentCountryNames(c2);
			return 0;
		}
		case 6: { return 500; }//return to main menu
		}
		return 0;
	}

	//demonstration of the map-editing
	static int editMap(Map *m) {
		cout << "==========================\n"
			<< "Welcome to the Map Editor!\n"
			<< "==========================\n";

		while (true) {
			cout << "\nWhat do you wish to edit?\n"
				<< "[ 1 ] Map name\n"
				<< "[ 2 ] A continent's name\n"
				//<< "COUNTRIES: " <<m->getCountryNames()<<"\n"
				<< "[ 3 ] A country's name\n"
				<< "[ 4 ] Add country's adjacencies\n"
				<< "[ 5 ] Remove country's adjacencies\n"
				<< "[ 6 ] Exit" << endl;
			string input = "";
			getline(cin, input);

			// This code converts from string to number safely.
			stringstream myStream(input);
			int userChoice = 0;
			if (myStream >> userChoice) {
				int check = mapEditAction(userChoice, m);
				if (check == 500)
					return 500; //if mapCreation returned 500, return to main menu
			}
			else
				cout << "Not a valid choice. Please try again" << endl;
		}
		return 0;//shouldn't reach this
	}


	static int mapEditor(int choice) {

		switch (choice) {
		case 1: {//Edit good Normal map
			cout << "Edit good normal map...\n";
			SaverLoader *s = new SaverLoader("TestMapNormal");
			SaverLoaderTwoWayAdapter *mapAdapter = new SaverLoaderTwoWayAdapter(s);
			Map *m = mapAdapter->loadNormalMap();
			if (m != NULL) {
				editMap(m);
				if (m->getIsConnected() && m->getContinentsValid())
					mapAdapter->saveNormalMap(m);
				else
					cout << "Map not valid. Cannot save map." << endl;
				delete s;
				delete mapAdapter;

				Continent *sacrificialContinent = (*(m->getContinents()))[0];
				sacrificialContinent->resetCount();
				Country *sacrificialCountry = (*(m->getCountries()))[0];
				sacrificialCountry->resetCount();
				delete m;

				return 0;
			}
			else {

				cout << "Invalid map! SHAME!" << endl;
				delete s;
				delete mapAdapter;
				return 0;
			}
		}

		case 2: {//Edit good Conquest map
			cout << "Edit good conquest map...\n";
			ConquestSaverLoader *cs = new ConquestSaverLoader("TestMapConquest");
			SaverLoaderTwoWayAdapter *mapAdapter = new SaverLoaderTwoWayAdapter(cs);
			Map *m = mapAdapter->loadConquestMap();

			if (m != NULL) {
				editMap(m);
				if (m->getIsConnected() && m->getContinentsValid())
					mapAdapter->saveConquestMap(m);

				else
					cout << "Map not valid. Cannot save map." << endl;
				delete cs;
				delete mapAdapter;

				Continent *sacrificialContinent = (*(m->getContinents()))[0];
				sacrificialContinent->resetCount();
				Country *sacrificialCountry = (*(m->getCountries()))[0];
				sacrificialCountry->resetCount();
				delete m;

				return 0;
			}
			else {
				cout << "Invalid map! SHAME!" << endl;
				delete cs;
				delete mapAdapter;
				return 0;
			}

		}
		case 3: {//Edit bad1 map
			cout << "Attempting to load map...";
			ConquestSaverLoader *cs = new ConquestSaverLoader("MyBadMap1");

			Map *m = cs->loadMap();
			if (m != NULL) {
				editMap(m);
				if (m->getIsConnected() && m->getContinentsValid())
					cs->savingMap(m);
				else
					cout << "Map not valid. Cannot save map." << endl;
				return 0;
			}
			else {
				cout << "Invalid map! SHAME!" << endl;
				return 0;
			}
		}
		case 4: {//Edit bad2 map
			cout << "Attempting to load map...";
			SaverLoader *s = new SaverLoader("BadMap2");
			Map *m = s->loadMap();
			if (m != NULL) {
				editMap(m);
				if (m->getIsConnected() && m->getContinentsValid())
					s->savingMap(m);
				else
					cout << "Map not valid. Cannot save map." << endl;
				return 0;
			}
			else {
				cout << "Invalid map! SHAME!" << endl;
				return 0;
			}
		}
		case 5: {//Edit bad3 map
			cout << "Attempting to load map...";
			SaverLoader *s = new SaverLoader("BadMap3");
			Map *m = s->loadMap();
			if (m != NULL) {
				editMap(m);
				if (m->getIsConnected() && m->getContinentsValid())
					s->savingMap(m);
				else
					cout << "Map not valid. Cannot save map." << endl;
				return 0;
			}
			else {
				cout << "Invalid map! SHAME!" << endl;
				return 0;
			}
			return 0;
		}
		case 6: { return 500; }//return to main menu
		}
		return 0;	//should not reach
	}

	//choices of the user from the map 
	static int mapAction(int choice) {
		switch (choice) {
		case 1: {
			cout << "==========================\n"
				<< "Welcome to the Map Creator!\n"
				<< "==========================\n";

			makeMap();
			cout << endl;

			return 0;
		}

		case 2: {
			cout << "=========================\n"
				<< "Welcome to the Map Editor !\n"
				<< "=========================\n";

			while (true) {
				cout << "\nWhich map would you like to edit:\n"
					<< "[ 1 ] Good1 (normal)\n"
					<< "[ 2 ] Good2 (conquest)\n"
					<< "[ 3 ] Bad1 (Corrupt Conquest File)\n"
					<< "[ 4 ] Bad2 (Continents Invalid)\n"
					<< "[ 5 ] Bad3 (Disconnected Map)\n"
					<< "[ 6 ] Exit" << endl;
				string input = "";
				getline(cin, input);

				// This code converts from string to number safely.
				stringstream myStream(input);
				int userChoice = 0;
				if (myStream >> userChoice) {
					int check = mapEditor(userChoice);
					if (check == 500)
						return 500; //if mapCreation returned 500, return to main menu
				}
				else
					cout << "Not a valid choice. Please try again" << endl;
			}
			return 0;//shouldn't reach this
		}

		case 3: { return 500; }//return to main menu
		}
		return 0; // should not get here
	}
	static void mainMapMenu() {
		cout << "=============================\n"
			<< "Welcome to the Main Map Menu!\n"
			<< "=============================\n";

		while (true) {
			cout << "\nWould you like to:\n"
				<< "[ 1 ] Create new map?\n"
				<< "[ 2 ] Edit existing map?\n"
				<< "[ 3 ] Exit" << endl;
			string input = "";
			getline(cin, input);

			// This code converts from string to number safely.
			stringstream myStream(input);
			int userChoice = 0;
			if (myStream >> userChoice) {
				int check = mapAction(userChoice);
				if (check == 500)
					return; //if userAction returned 5, return to main menu
			}
			else
				cout << "Not a valid choice. Please try again" << endl;
		}
	}

	Game* createNewGame() {
		Startphase start;
		Game* newGame = new Game();

		// MAP predefinedMAPS[]
		int gameMode;
		int numPlayers;
		vector <Player*>* activePlayers = new vector<Player*>();

		// First, let's load the map
		bool validMapSelected = false;
		
		string mapName;
		while (!validMapSelected) {
			
			cout << "Please enter the name of the game you would like to load: ";

			cin >> mapName;
			// check if a file with that name exists
			ifstream fout;
			try {
				fout.open(mapName + ".map");

				validMapSelected = true;
			}
			catch (...) {
				cout << "ERROR: map file does not exist. Please try again." << endl;
				validMapSelected = false;
			}

		}
		SaverLoader *s = new SaverLoader(mapName);
		newGame->map = s->loadMap();

		if (newGame->map == NULL) {
			cout << "Map not valid. Cannot load map." << endl;
			return 0;
		}

		// Now we name the game
		cout << "Please enter a name for this game: ";
		string name;
		cin >> name;
		newGame->gameName = name;

		// Now we create the players
		numPlayers = start.initializeNumOfGamePlayers(activePlayers);
		start.createPlayers(activePlayers, numPlayers);
		newGame->gamePlayers = activePlayers;

		// Now we assign the turn order to the players
		// start.initializePlayersTurn(newGame->gamePlayers);

		// Now we set the player statistics
		start.setStatistics(newGame->gamePlayers);
		
		start.setLogger(newGame->gamePlayers);

		// Now we randomly assign the countries
		start.assignCountries(newGame->gamePlayers, newGame->map);


		for (int i = 0; i < newGame->gamePlayers->size(); i++) {
			cout << "------------------------------------" << endl;
			cout << newGame->gamePlayers->at(i)->getName() << endl;
			cout << "Countries: " << endl;
			list<Country*> *countries = newGame->gamePlayers->at(i)->getOwnedCountries();
			for (list<Country*>::iterator i = countries->begin();
			i != countries->end(); ++i) {
				cout << (*i)->getName() << endl;
			}
		}
		cout << "Finished assigning countries!" << endl;
		return newGame;
	};

	Game* gameMenu() {
		cout << "=============================\n"
			<< "Welcome to the Game  Menu!\n"
			<< "=============================\n";

		while (true) {
			cout << "\nWould you like to:\n"
				<< "[ 1 ] Create new game?\n"
				<< "[ 2 ] Load existing game?\n"
				<< endl;
			string input = "";
			getline(cin, input);

			// This code converts from string to number safely.
			stringstream myStream(input);
			int userChoice = 0;
			myStream >> userChoice; 
			if (userChoice == 1) {
				// create new game
				Game* theGame = createNewGame();
				theGame->cardsInitialized = false;
				theGame->phase = -1;
				theGame->currentPlayer = NULL;
				theGame->initializeCards();
				return theGame;
			}
			else if (userChoice == 2) {
				

				
				Startphase start;
				bool validGameSelected = false;
				string theNameOfTheGame;
				while (!validGameSelected) {
					cout << "Please enter the name of the game you would like to load: ";
					
					cin >> theNameOfTheGame;
					// check if a file with that name exists
					ifstream fout;
					try {
						fout.open(theNameOfTheGame + ".map");
						validGameSelected = true;
					}
					catch (...) {
						cout << "ERROR: game file does not exist. Please try again." << endl;
						validGameSelected = false;
					}
				}
				

				SaverLoader* newgametoload = new SaverLoader(theNameOfTheGame);
				GameBuilder* thegamebuilder = new ExistingGameBuilder(newgametoload);
				GameDirector* themainbuilder = new GameDirector(thegamebuilder);
				themainbuilder->constructGame();
				Game* newGame = themainbuilder->returnGame();
				Player::setNumCardSetsTradedIn(newGame->numCardSetsTradedIn);
				// Now we set the player statistics
				start.setStatistics(newGame->gamePlayers);
				start.setLogger(newGame->gamePlayers);

				return newGame;

			}
			else
				cout << "Not a valid choice. Please try again" << endl;
		}
	}
	
}

using namespace mapDemo;

int main() {
	int gameMode;
	Startphase start;
	start.welcome();
	do {
		gameMode = start.mainMenu();
		switch (gameMode) {
		case 0: //Map Editor goes here
			mainMapMenu();
			break;
		case 1: // Game starts
			Game* theGame = gameMenu();


			// attach the map observer
			MapObserver* theObserver = new MapObserver(theGame->map);
			theGame->map->attach(theObserver);

			// attach the player observer
			for (vector<Player*>::iterator i = theGame->gamePlayers->begin(); i != theGame->gamePlayers->end(); ++i) {
				(*i)->attach(new PlayerView((*i)));
			}
			
			// Ask player if they would like to save the game
			cout << "Before playing, do you want to save the game? (Y or N) ";
			char save = ' ';
			cin >> save;
			if (save == 'Y' || save == 'y') {

				SaverLoader* mysaver = new SaverLoader(theGame->gameName);
				SaveGameBuilder* mysavebuilder = new SaveGame(theGame, mysaver);
				SaveDirector* savechef = new SaveDirector(mysavebuilder);
				savechef->saveGame();
				cout << "Successfully saved the game" << endl;
			}

			if (theGame->phase == -1) {
				// then the game has not yet started, so we'll need to go through the initial reinforcement phase
				// Initial reenforcement
				cout << "Starting intial reinforcement" << endl;
				theGame->phase = 0;
				// first we're going to add 1 army to each country
				for (vector<Country*>::iterator i = (theGame->map)->getCountries()->begin(); i != (theGame->map)->getCountries()->end(); ++i) {
					(*i)->setArmies(1);
				}

				// now we'll let the players place armies
				for (int i = 0; i < theGame->gamePlayers->size(); i++) {
					theGame->gamePlayers->at(i)->placeArmiesOnCountriesLoop(10);
					list<Country*> *countries = theGame->gamePlayers->at(i)->getOwnedCountries();
					for (list<Country*>::iterator i = countries->begin(); i != countries->end(); ++i) {
						cout << "Country: " << (*i)->getName() << " | Armies: " << (*i)->getArmies() << endl;
					}
				}

				cout << "Initial reinforcement Complete" << endl;

			}


			char doPlayerTurns = 'Y';
			bool firstEntry = true;

			while (doPlayerTurns=='Y' || doPlayerTurns=='y') {

				vector<Player*>::iterator i;
				if (firstEntry) {
					firstEntry = false;
					
					if (theGame->currentPlayer == NULL) {
						i = theGame->gamePlayers->begin();
					}
					else {
						// iterate through the game players until you find the current player
						for (vector<Player*>::iterator j = theGame->gamePlayers->begin(); j != theGame->gamePlayers->end(); ++j) {
							if ((*j) == theGame->currentPlayer) {
								i = j;
								break;
							}
						}
					}
				}
				else {
					i = theGame->gamePlayers->begin();
				}
				

				for (; i != theGame->gamePlayers->end(); ++i) {
					

					cout << "************************************" << endl;
					cout << "PLAYER TURN: " << (*i)->getName() << endl;
					theGame->currentPlayer = *i;
					// Ask player if they would like to save the game
					theGame->phase = 4;
					cout << "Do you want to save the game? (Y or N) ";
					char save = ' ';
					cin >> save;
					if (save == 'Y' || save == 'y') {

						SaverLoader* mysaver = new SaverLoader(theGame->gameName);
						SaveGameBuilder* mysavebuilder = new SaveGame(theGame, mysaver);
						SaveDirector* savechef = new SaveDirector(mysavebuilder);
						savechef->saveGame();
						cout << "Successfully saved the game" << endl;
					}

					
					int numBattlesWonOriginal = (*i)->getNumberBattlesWon();
				

					// reinforce countries phase
					
					(*i)->reinforceCountries();

					// battle phase
					
					attackPhase(*(theGame->gamePlayers),*i, theGame->map);

					// fortification phase
					
					Fortification fortification;
					fortification.fortify((*i), theGame->map);

					
					int numBattlesWonNew = (*i)->getNumberBattlesWon();
					if (numBattlesWonNew - numBattlesWonOriginal > 0) {
						// then the player won a battle this round
						// so we need to give them a random Risk card from the game
						int cardTypeToSelectFrom = (rand() % 4) + 1;
						if (cardTypeToSelectFrom == 1) {
							int cardToChoose = (rand() % theGame->gameArtilleryCards->size());
							(*i)->addPlayerCard(theGame->gameArtilleryCards->at(cardToChoose));
						} else if (cardTypeToSelectFrom == 2) {
							int cardToChoose = (rand() % theGame->gameCavalryCards->size());
							(*i)->addPlayerCard(theGame->gameArtilleryCards->at(cardToChoose));
						} else if (cardTypeToSelectFrom == 3) {
							int cardToChoose = (rand() % theGame->gameInfantryCards->size());
							(*i)->addPlayerCard(theGame->gameArtilleryCards->at(cardToChoose));
						} else if (cardTypeToSelectFrom == 4) {
							int cardToChoose = (rand() % theGame->gameWildCards->size());
							(*i)->addPlayerCard(theGame->gameArtilleryCards->at(cardToChoose));
						}

					}

					
				}

				cout << "Do you want to continue? Y/N "; 
				cin >> doPlayerTurns; 
			}
		
			delete theGame->map;
		}

	} while (gameMode != 2); // Exit option
	
	return 0;
}

