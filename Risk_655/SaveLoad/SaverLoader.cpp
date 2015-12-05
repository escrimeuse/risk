// Assignment #3 - COMP345 - Section DI - Fall 2015
// Author of SAVERLOADER: Caio Paiva, Catryn Griffiths, Jennifer Sunahara
//
//This is the implementation file SaverLoader.cpp of the class SaverLoader.
//The interface of this class is in the header file SaverLoader.h.
#include "../SaveLoad/SaverLoader.h"
#include "../Map/Map.h"
#include "../Map/Country.h"
#include "../GameBuilder/Game.h"
#include "../strategyPattern/Agressive.h"
#include "../strategyPattern/Defensive.h"
#include "../strategyPattern/Random.h"
#include "../strategyPattern/Strategy.h"

using namespace std;
//File extension
const string SaverLoader::extension = ".map";

/**
* Default Constructor
* Name the file unnamed.map
*/
SaverLoader::SaverLoader() {			//Initialize fileName to unnamed.map
	fileName = "";
	fileName.append("unnamed");
	fileName.append(SaverLoader::extension);
}

/**
* Non-default Constructor
* @param fn name of the file
*/
SaverLoader::SaverLoader(string fn) {	// Initialize fileName to GivenName.map
	fileName = "";
	fileName.append(fn);				// Appends file name and extension
	fileName.append(SaverLoader::extension);
}

/**
* Saves a given map into file
*/
void SaverLoader::savingMap(Map *map) {
	ofstream out(fileName.c_str());		//Opens or creates file
	saveMap(out, map);					// Save map info
	saveCountries(out, map);			//Save country list
	saveContinents(out, map);			//Save Continent list
	saveAdjencencies(out, map);			//Save connection between countries
	out.close();						//Close file
}



/**
* Saves map information
* @param out Stream with opened file
* @param map map to be saved
*/
void SaverLoader::saveMap(ofstream& out, Map *map) {
	//out << map->getType() << endl;

	out << map->getName() << "\n\n";
}

/**
* Saves countries
* @param out Stream with opened file
* @param map map whose countries will be saved
*/
void SaverLoader::saveCountries(ofstream& out, Map *map) {

	out << map->getNumCountries() << endl;
	for (int i = 0; i < map->getNumCountries(); i++) {			// For each country
		Country *current = (* map->getCountries())[i];
		string ownerName = "00000000";//default "owner name"
		if (current->getOwner() != NULL) {
			ownerName = current->getOwner()->getName();
		}
		out <<current->getId() << " " << current->getName() // saves id/name/owner/troops
			<< " " << ownerName << " " << current->getArmies() << endl;
	}
	out << "\n";
}

/**
* Saves Continent information
* @param out Stream with opened file
* @param map map whose continents will be saved
*/
void SaverLoader::saveContinents(ofstream& out, Map *map) {

	out << map->getNumContinents() << endl;
	for (int i = 0; i < map->getNumContinents(); ++i) {	// for each continent in the map
		Continent *current = (*map->getContinents())[i];
		out << current->getId()<<" "<< current->getName() << " " << current->getNumCountries() << " "<< current->getControlValue()<<endl; // Continent info
		for (int j = 0; j <current->getNumCountries(); ++j) {	// Each country inside continentload
			Country *currentJ =(* current->getCountries())[j];
			out << currentJ->getId() << endl;			// save country id
		}
	}
	out << "\n";
}

/**
* Saves connections between countries
* @param out Stream with opened file
* @param map map with adjencecies
*/
void SaverLoader::saveAdjencencies(ofstream& out, Map *map) {
	

	for (int i = 0; i < map->getNumCountries(); i++)		// x axis of the
	{
		Country *current = (*map->getCountries())[i];
		out << current->getId() <<  endl;	// current country info
		for (int j = 0; j < map->getNumCountries(); j++)		// y axis
		{
			out << map->checkIsAdjacentByIndex(i,j) << "\t";		// save true or false connection
		}
		out << "\n\n";
	}
}


///**
/* loads a map
* @return pointer to loaded map
*/
Map* SaverLoader::loadMap() {

	struct CountryL {
		string name;
		string owner;
		int id;
		int numArmies;
		bool* adjacencies;
	};

	struct ContinentL {
		string name;
		int id;
		int numCountries;
		int* countryIds;
		int controlValue;
	};

	//string mapType = "";
	string mapName = "";
	int numberCountries = -1;
	int numberContinents = -1;
	vector<CountryL*>* countryList = new vector<CountryL*>;
	vector<ContinentL*>* continentList = new vector<ContinentL*>;

	ifstream fin;

	fin.open(fileName);
	try {

		// first read in the map type
		//fin >> mapType;
		/*if (fin.fail()) {
			throw 20;
		}
		cout << mapType << endl;*/

		// now read in the map name
		fin >> mapName;
		if (fin.fail()) {
			throw 20;
		}
		

		// read in the number of countries
		fin >> numberCountries;
		if (fin.fail()) {
			throw 20;
		}
		

		
		for (int i = 0; i < numberCountries; ++i) {
			CountryL* newCountry = new CountryL();

			fin >> newCountry->id;
			if (fin.fail()) {
				throw 20;
			}
			

			fin >> newCountry->name;
			if (fin.fail()) {
				throw 20;
			}
			

			fin >> newCountry->owner;
			if (fin.fail()) {
				throw 20;
			}
			

			fin >> newCountry->numArmies;
			if (fin.fail()) {
				throw 20;
			}
			
			

			countryList->push_back(newCountry);
		}

		// check the list to see if we have any countries with the same ID number. Since an ID is unique to a country, 
		// we should not have any duplicate/matching ID numbers in a valid map
		for (int i=0; i < numberCountries; ++i) {
			int countryID = ((*countryList)[i])->id;

			for (int j = i + 1; j < numberCountries;++j) {
				if (((*countryList)[j]->id == countryID)) {
					throw 20;
				}
			}
		}

		// read in the number of continents
		fin >> numberContinents;
		if (fin.fail()) {
			throw 20;
		}
		

		

		for (int i = 0; i < numberContinents; ++i) {
			ContinentL* newContinent = new ContinentL();
			
			fin >> newContinent->id;
			if (fin.fail()) {
				throw 20;
			}
			

			fin >> newContinent->name;
			if (fin.fail()) {
				throw 20;
			}
			

			fin >> newContinent->numCountries;
			if (fin.fail()) {
				throw 20;
			}
			

			fin >> newContinent->controlValue;
			if (fin.fail()) {
				throw 20;
			}
			

			newContinent->countryIds = new int[newContinent->numCountries];

			for (int i = 0; i < newContinent->numCountries; ++i) {
				fin >> (newContinent->countryIds)[i];
				if (fin.fail()) {
					throw 20;
				}
				
			}

			continentList->push_back(newContinent);
		}

		// check the list to see if we have any continents with the same ID number. Since an ID is unique to a continent, 
		// we should not have any duplicate/matching ID numbers in a valid map
		for (int i = 0; i < numberContinents; ++i) {
			int continentID = ((*continentList)[i])->id;

			for (int j = i + 1; j < numberContinents; ++j) {
				if (((*continentList)[j]->id == continentID)) {
					throw 20;
				}
			}
		}

		// now read in the adjacencies of each country
		int tempCountryId = -1;
		for (int i = 0; i < numberCountries; ++i) {
			fin >> tempCountryId;
			if (fin.fail()) {
				throw 20;
			}
			
			CountryL* country = NULL;

			// search country list to find the country corresponding to this ID
			for (vector<CountryL*>::iterator j = countryList->begin(); j != countryList->end(); ++j) {
				if ((*j)->id == tempCountryId) {
					country = *j;
					break;
				}
			}
			if (country == NULL) {
				// if the country is NULL, then that means that the country ID read in from the file does not correspond to a
				// country ID that was previously read in from the file.
				throw 20;
			}

			country->adjacencies = new bool[numberCountries];

			for (int k = 0; k < numberCountries; ++k) {
				fin >> (country->adjacencies)[k];
				if (fin.fail()) {
					throw 20;
				}
				
			}
			
		}

		bool** adjacencyMatrix = new bool*[numberCountries];
		int j = 0;
		for (vector<CountryL*>::iterator i = countryList->begin(); i != countryList->end(); ++i, ++j) {
			adjacencyMatrix[j] = (*i)->adjacencies;
		}
		




	}
	catch (...) {
		cout << "ERROR:" << endl;
		cout << "The map file you are trying to load has been corrupted!" << endl;
		cout << "It is to RISKy to load it >:-|" << endl;
		return NULL;
	}
	
	

	Map* loadedMap = new Map(mapName,numberCountries,numberContinents, 0);

	// now we add the continents
	for (vector<ContinentL*>::iterator j = continentList->begin(); j != continentList->end(); ++j) {
		Continent* temp = new Continent((*j)->name, (*j)->numCountries, (*j)->id, (*j)->controlValue);
		
		// now we add countries to the continent
		for (int i = 0; i < (*j)->numCountries; ++i) {
			int tempIDholder = (*j)->countryIds[i];
			for (vector<CountryL*>::iterator k = countryList->begin(); k != countryList->end(); ++k) {
				if ((*k)->id == tempIDholder) {
					Country* tempCountry = new Country((*k)->name, (*k)->id, (*k)->numArmies, false, NULL);
					loadedMap->addCountry(tempCountry);
					temp->addCountry(tempCountry);
					(temp->numCountries)--;//to correct for the incrementing happening in method addCountry(..)
				}
				
			}
		}
		loadedMap->addContinent(temp);
	}

	// now we create the adjacency matrix for the countries

	bool** adjMatrix;
	adjMatrix = new bool*[numberCountries];
	for (int i = 0; i < numberCountries; i++) {
		adjMatrix[i] = new bool[numberCountries];
	}

	int j = 0;
	for (vector<CountryL*>::iterator i = countryList->begin(); i != countryList->end(); ++i, ++j) {
		for (int k = 0; k < numberCountries; ++k) {
			adjMatrix[j][k] = (*i)->adjacencies[k];
		}

	}

	// pass the adjacency matrix so it can be copied to the adjacency matrix in the map
	loadedMap->setAdjacency(adjMatrix);


	bool valid = loadedMap->getIsConnected();
	bool connected = loadedMap->getContinentsValid();

	fin.close();

	if (valid && connected) {
		return loadedMap;
	}
	return NULL;

}


vector<Player*>* SaverLoader::loadPlayers() {
	int numberOfPlayers = -1;
	vector<Player*>* gamePlayers = new vector<Player*>();

	ifstream fin;
	fin.open(fileName);
	try {

		// search for the word PLAYERS in the file, because all the player info will be written after that word

		string playersHeading = "";
		while (playersHeading.compare("PLAYERS") != 0) {
			fin >> playersHeading;
		}

		// now that we know where the player information is, we'll read in the number of players
		fin >> numberOfPlayers;
		if (fin.fail()) {
			throw 20;
		}
		

		// now we're going to do a loop to read the information for each player
		for (int r = 0; r < numberOfPlayers; ++r) {
			
			
			
			// these are temporary holders for information that we will feed to the data members of the player
			string playerName = "";
			int strategy;
			int numBattlesWon;
			int armies;
			int numArtillery;
			int numCavalry;
			int numInfantry;
			int numWild;
			int numContinents;
			int numCountries;
			list<Country*>* countryList = NULL;
			list<Continent*>* continentList = NULL;
			list<Card*> *infantryCards = new list<Card*>();	
			list<Card*> *cavalryCards = new list<Card*>();
			list<Card*> *artilleryCards = new list<Card*>();
			list<Card*> *wildCards = new list<Card*>();

			fin >> playerName;
			if (fin.fail()) {
				throw 20;
			}
			
			fin >> strategy;
			if (fin.fail()) {
				throw 20;
			}

			Player* newPlayer = NULL;
			if (strategy == 0) {
				newPlayer = new Player(playerName);
			}
			else {
				// create a player using the name and strategy
				Player* newPlayer = new Player(playerName, strategy);
			}
			

			fin >> numBattlesWon;
			if (fin.fail()) {
				throw 20;
			}

			newPlayer->setNumberBattlesWon(numBattlesWon);


			fin >> armies;
			if (fin.fail()) {
				throw 20;
			}
			
			newPlayer->setTotalNumArmies(armies);

			fin >> numArtillery;
			if (fin.fail()) {
				throw 20;
			}
			
			newPlayer->setNumCardsArtillery(numArtillery);

			fin >> numCavalry;
			if (fin.fail()) {
				throw 20;
			}
			
			newPlayer->setNumCardsCavalry(numCavalry);

			fin >> numInfantry;
			if (fin.fail()) {
				throw 20;
			}
			
			newPlayer->setNumCardsInfantry(numInfantry);

			fin >> numWild;
			if (fin.fail()) {
				throw 20;
			}
			
			newPlayer->setNumCardsWild(numWild);

			fin >> numContinents;
			if (fin.fail()) {
				throw 20;
			}
			
			newPlayer->setNumOwnedContinents(numContinents);

			fin >> numCountries;
			if (fin.fail()) {
				throw 20;
			}
			
			newPlayer->setNumOwnedCountries(numCountries);
			
			// let's create our owned continents. Right now, we're
			// going to create continents that ONLY have a name
			continentList = new list<Continent*>();
			if (numContinents > 0) {
				
				for (int j = 0; j < numContinents; ++j) {
					Continent* newContinent = new Continent();
					fin >> newContinent->name;
					
					if (fin.fail()) {
						throw 20;
					}
					continentList->push_back(newContinent);
				}
			}
			
			newPlayer->setOwnedContinents(continentList);
			
			// let's create our owned countries. Right now, we're
			// going to create countries that ONLY have a name
			countryList = new list<Country*>();
			if (numCountries > 0) {
				
				for (int j = 0; j < numCountries; ++j) {
					Country* newCountry = new Country();
					fin >> newCountry->name;
				
					if (fin.fail()) {
						throw 20;
					}
					countryList->push_back(newCountry);
				}
			}
			newPlayer->setOwnedCountries(countryList);

			// now let's create our player cards
			// starting with artillery cards

			for (int a = 0; a < numArtillery; ++a) {
				string countryOnCard = "";
				fin >> countryOnCard; 
				
				Card* newCard = new Card(countryOnCard, artillery);
				artilleryCards->push_back(newCard);
			}
			newPlayer->setPlayersArtilleryCards(artilleryCards);
			

	
			for (int a = 0; a < numCavalry; ++a) {
				string countryOnCard = "";
				fin >> countryOnCard;
				
				Card* newCard = new Card(countryOnCard, cavalry);
				cavalryCards->push_back(newCard);
			}
			
			newPlayer->setPlayersCavalryCards(cavalryCards);

			
			for (int a = 0; a < numInfantry; ++a) {
				string countryOnCard = "";
				fin >> countryOnCard;
				
				Card* newCard = new Card(countryOnCard, infantry);
				infantryCards->push_back(newCard);
			}
			newPlayer->setPlayersInfantryCards(infantryCards);
			

			
			for (int a = numWild; a < numWild; ++a) {
				string countryOnCard = "";
				fin >> countryOnCard;
				Card* newCard = new Card(countryOnCard, wild);
				infantryCards->push_back(newCard);
			}
			newPlayer->setPlayersWildCards(wildCards);

			
			gamePlayers->push_back(newPlayer);
		}
	}
	catch (const std::runtime_error& re)
	{
		// speciffic handling for runtime_error
		std::cerr << "Runtime error: " << re.what() << std::endl;
		return NULL;
	}

	fin.close(); 

	return gamePlayers;
}


vector<Card*>* SaverLoader::loadCards(cardType card) {
	ifstream fin;
	int numCards;
	string heading;
	vector<Card*>* cardList = new vector<Card*>();

	if (card==artillery) heading = "ARTILLERY";
	else if (card==infantry) heading = "INFANTRY";
	else if (card==cavalry) heading = "CAVALRY";
	else heading = "WILD";

	fin.open(fileName);

	try {
		
		string cardHeading = "";
		while (cardHeading.compare(heading) != 0) {
			fin >> cardHeading;
		}

		fin >> numCards;
		if (fin.fail()) {
			throw 20;
		}

		for (int i = 0; i < numCards; ++i) {
			string cardName = "";
			fin >> cardName; 
			if (fin.fail()) {
				throw 20;
			}
			cardList->push_back(new Card(cardName, card));
		}

	}
	catch (...) {
		cout << "ERROR LOADING ARTILLERY CARDS" << endl;
		return NULL;
	}

	return cardList;

};

string SaverLoader::loadCurrentPlayer() {
	ifstream fin;
	string currentPlayerName = "";
	fin.open(fileName);

	try {

		string currentPlayerHeading = "";
		while (currentPlayerHeading.compare("CURRENTPLAYER") != 0) {
			fin >> currentPlayerHeading;
		}

		fin >> currentPlayerName;
		if (fin.fail()) {
			throw 20;
		}
	}
	catch (...) {
		cout << "ERROR LOADING CURRENT PLAYER" << endl;
		return "";
	}
	return currentPlayerName;
}

int SaverLoader::loadCurrentPhase() {
	ifstream fin;
	int currentphase = -1;
	fin.open(fileName);

	try {

		string currentPhaseHeading = "";
		while (currentPhaseHeading.compare("CURRENTPHASE") != 0) {
			fin >> currentPhaseHeading;
		}

		fin >> currentphase;
		if (fin.fail()) {
			throw 20;
		}
	}
	catch (...) {
		cout << "ERROR LOADING CURRENT PHASE" << endl;
		return 999;
	}
	return currentphase;
}

int SaverLoader::loadNumCardSetsTradedIn() {
	ifstream fin;
	int numTradedIn = -1;
	fin.open(fileName);

	try {

		string numTradedHeading = "";
		while (numTradedHeading.compare("NUMCARDSETSTRADED") != 0) {
			fin >> numTradedHeading;
		}

		fin >> numTradedIn;
		if (fin.fail()) {
			throw 20;
		}
	}
	catch (...) {
		cout << "ERROR LOADING NUM CARDS TRADED IN" << endl;
		return 999;
	}
	return numTradedIn;
}

string SaverLoader::loadGameName() {
	ifstream fin;
	string name = "";
	fin.open(fileName);

	try {

		string gameNameHeading = "";
		while (gameNameHeading.compare("GAMENAME") != 0) {
			fin >> gameNameHeading;
		}

		fin >> name;
		if (fin.fail()) {
			throw 20;
		}
	}
	catch (...) {
		cout << "ERROR LOADING GAME NAME" << endl;
		return "";
	}
	return name;
}

void SaverLoader::savePlayersAndCards(Game* game) {
	 ofstream fout; 

	 fout.open(fileName, ios::app);

	 fout << "PLAYERS " << endl;
	 fout << game->gamePlayers->size() << endl;
	 for (vector<Player*>::iterator i = (game->gamePlayers)->begin(); i != (game->gamePlayers)->end(); ++i) {
		 fout << (*i)->getName() << " ";

		 // print out the strategy
		 Agressive* strat1 = dynamic_cast<Agressive*>((*i)->getStrategy());
		 Defensive* strat2 = dynamic_cast<Defensive*>((*i)->getStrategy());
		 Random* strat3 = dynamic_cast<Random*>((*i)->getStrategy());
		 
		 if (strat1 != NULL) {
			 // player is agressive strategy
			 fout << 1 << " ";
		 }
		 else if (strat2 != NULL) {
			 // player is defensive strategy
			 fout << 2 << " ";
		 }
		 else if (strat3 != NULL) {
			 // player is random strategy
			 fout << 3 << " ";
		 }
		 else {
			 // player does not have a strategy
			 fout << 0 << " ";
		 }


		 fout << (*i)->getNumberBattlesWon() << " " << (*i)->getTotalNumArmies() << " " << (*i)->getNumCardsArtillery() << " ";
		 fout << (*i)->getNumCardsCavalry() << " " << (*i)->getNumCardsInfanty() << " " << (*i)->getNumCardsWild() << endl;
		 fout << (*i)->getNumOfOwnedContinents() << endl;
		 fout << (*i)->getNumOfOwnedCountries() << endl;
		 
		 // write out the owned continents name
		 list<Continent*>* continentList = (*i)->getOwnedContinents();

		 for (list<Continent*>::iterator j = continentList->begin(); j != continentList->end(); ++j) {
			 fout << (*j)->getName() << " ";
		 }
		 fout << endl;

		 // write out the owned countries names
		 list<Country*>* countryList = (*i)->getOwnedCountries();

		 for (list<Country*>::iterator j = countryList->begin(); j != countryList->end(); ++j) {
			 fout << (*j)->getName() << " ";
		 }
		 fout << endl;

		 // write out the artillery card names
		 
		 list<Card*>* artilleryCards = (*i)->getPlayersArtilleryCards();

		 for (list<Card*>::iterator j = artilleryCards->begin(); j != artilleryCards->end(); ++j) {
			 fout << (*j)->getCountryOnCard() << " ";
		 }
		 fout << endl;

		 // write out the cavalry card names
		 
		 list<Card*>* cavalryCards = (*i)->getPlayersCavalryCards();

		 for (list<Card*>::iterator j = cavalryCards->begin(); j != cavalryCards->end(); ++j) {
			 fout << (*j)->getCountryOnCard() << " ";
		 }
		 fout << endl;

		 // write out the infantry card names
		 
		 list<Card*>* infantryCards = (*i)->getPlayersInfantryCards();

		 for (list<Card*>::iterator j = infantryCards->begin(); j != infantryCards->end(); ++j) {
			 fout << (*j)->getCountryOnCard() << " ";
		 }
		 fout << endl;

		 // write out the wild card names
		 
		 list<Card*>* wildCards = (*i)->getPlayersWildCards();

		 for (list<Card*>::iterator j = wildCards->begin(); j != wildCards->end(); ++j) {
			 fout << (*j)->getCountryOnCard() << " ";
		 }
		 fout << endl;


	 }
}

void SaverLoader::saveState(Game* game) {
	ofstream fout;

	fout.open(fileName, ios::app);

	// write out the artillery cards
	fout << "ARTILLERY ";
	fout << game->gameArtilleryCards->size() << " ";
	
	if (game->gameArtilleryCards->size() > 0) {
		for (vector<Card*>::iterator i = game->gameArtilleryCards->begin(); i != game->gameArtilleryCards->end(); ++i) {
			fout << (*i)->getCountryOnCard() << " ";
		}
	}
	fout << endl;

	// write out the infantry cards
	fout << "INFANTRY ";
	fout << game->gameInfantryCards->size() << " ";

	if (game->gameInfantryCards->size() > 0) {
		for (vector<Card*>::iterator i = game->gameInfantryCards->begin(); i != game->gameInfantryCards->end(); ++i) {
			fout << (*i)->getCountryOnCard() << " ";
		}
	}
	fout << endl;

	// write out the cavalry cards
	fout << "CAVALRY ";
	fout << game->gameCavalryCards->size() << " ";

	if (game->gameCavalryCards->size() > 0) {
		for (vector<Card*>::iterator i = game->gameCavalryCards->begin(); i != game->gameCavalryCards->end(); ++i) {
			fout << (*i)->getCountryOnCard() << " ";
		}
	}
	fout << endl;

	// write out the wild cards
	fout << "WILD ";
	fout << game->gameWildCards->size() << " ";

	if (game->gameWildCards->size() > 0) {
		for (vector<Card*>::iterator i = game->gameWildCards->begin(); i != game->gameWildCards->end(); ++i) {
			fout << (*i)->getCountryOnCard() << " ";
		}
	}
	fout << endl;

	fout << "NUMCARDSETSTRADED " << (game->numCardSetsTradedIn) << endl;
	if (game->currentPlayer == NULL) {
		fout << "CURRENTPLAYER NULL" << endl;
	}
	else {
		fout << "CURRENTPLAYER " << (game->currentPlayer)->getName() << endl;
	}
	fout << "CURRENTPHASE " << (game->phase) << endl;

	fout << "GAMENAME " << (game->gameName) << endl;
}

