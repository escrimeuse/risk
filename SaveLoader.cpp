// Assignment #2 - COMP345 - Section DI - Fall 2015
// Author of SAVERLOADER: Caio Paiva
//
//This file was made by Caio Paiva for assignment 1 and has been partially modified
//to be integrated in my code. Unfortunately, I have only had time to make changes to 
//the save function and not the load function.

#include "SaveLoader.h"
#include "Map.h"
#include "MapDemo.h"
#include "Country.h"
#include "Game.h"

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
* gets the current date and time
*
* @returns date and time in format yyyy-mm-dd-hh:mm:ss
*/
//char* SaverLoader::getTime() {
//	time_t now = time(0);
//	struct tm  tstruct;
//	char* buf = new char(80);
//	tstruct = *localtime(&now);
//	strftime(buf, sizeof(buf), "%Y-%m-%d-%x", &tstruct);
//
//	return buf;
//}

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
		out <<current->getId() << " " << current->getName() // saves id/name/owner/troops
			<< " " << current->getOwner() << " " << current->getArmies() << endl;
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
//void SaverLoader::saveAdjencencies(ofstream& out, Map *map) {
//	out << "[ADJENCENCIES]" << endl;
//	for (int i = 0; i < map->getNumCountries(); i++)		// x axis of the
//	{
//		Country *current = (*map->getCountries())[i];
//		out << current->getId() << "\t" << current->getName() << endl;	// current country info
//		for (int j = 0; j < map->getNumCountries(); j++)		// y axis
//		{
//			out << map->checkIsAdjacentByIndex(i,j) << "\t";		// save true or false connection
//		}
//		out << "\n\n";
//	}
//}
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
		cout << mapName << endl;

		// read in the number of countries
		fin >> numberCountries;
		if (fin.fail()) {
			throw 20;
		}
		cout << numberCountries << endl;

		
		for (int i = 0; i < numberCountries; ++i) {
			CountryL* newCountry = new CountryL();

			fin >> newCountry->id;
			if (fin.fail()) {
				throw 20;
			}
			cout << newCountry->id << " ";

			fin >> newCountry->name;
			if (fin.fail()) {
				throw 20;
			}
			cout << newCountry->name << " ";

			fin >> newCountry->owner;
			if (fin.fail()) {
				throw 20;
			}
			cout << newCountry->owner << " ";

			fin >> newCountry->numArmies;
			if (fin.fail()) {
				throw 20;
			}
			cout << newCountry->numArmies << " ";
			cout << endl;

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
		cout << numberContinents << endl;

		

		for (int i = 0; i < numberContinents; ++i) {
			ContinentL* newContinent = new ContinentL();
			
			fin >> newContinent->id;
			if (fin.fail()) {
				throw 20;
			}
			cout << newContinent->id << " ";

			fin >> newContinent->name;
			if (fin.fail()) {
				throw 20;
			}
			cout << newContinent->name << " ";

			fin >> newContinent->numCountries;
			if (fin.fail()) {
				throw 20;
			}
			cout << newContinent->numCountries << " ";

			fin >> newContinent->controlValue;
			if (fin.fail()) {
				throw 20;
			}
			cout << newContinent->controlValue << " ";

			newContinent->countryIds = new int[newContinent->numCountries];

			for (int i = 0; i < newContinent->numCountries; ++i) {
				fin >> (newContinent->countryIds)[i];
				if (fin.fail()) {
					throw 20;
				}
				cout << (newContinent->countryIds)[i] << endl;
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
			cout << tempCountryId << endl;
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
				cout << (country->adjacencies)[k] << " ";
			}
			cout << endl;
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
	
	

	Map* loadedMap = new MapDemo(mapName,numberCountries,numberContinents);

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
				}
				
			}
		}
		loadedMap->addContinent(temp);
	}

	// now we create the adjacency matrix for the countries

	bool** adjMatrix;
	adjMatrix = new bool*[6];
	for (int i = 0; i < 6; i++) {
		adjMatrix[i] = new bool[6];
	}

	int j = 0;
	for (vector<CountryL*>::iterator i = countryList->begin(); i != countryList->end(); ++i, ++j) {
		for (int k = 0; k < 6; ++k) {
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
///**
//* loads a map info
//* @param in input stream with opened file
//* @param map map being created
//*/
//void SaverLoader::loadMap(ifstream& in, Map* map) {
//	char s[256];
//	in.getline(s, 256, '\n');
//	in.getline(s, 256, '\n');
//	in.getline(s, 256, '\n');		//Skips first file related lines
//	map->name = s;					// saves map name
//	in.getline(s, 256, '\n');
//	return;
//}
///**
//* loads countries
//* @param in input stream with opened file
//* @param map map being created
//*/
//void SaverLoader::loadCountries(ifstream& in, Map* map) {
//	char s[256];
//	in.getline(s, 256, '\n');
//	in.getline(s, 256, '\n');		// skips file readability lines
//
//	int numCountries;
//	numCountries = atoi(s);			// reads number of countries and parses it to integer
//	Country* countries = new Country[numCountries];	// Creates new array of countries
//	for (int i = 0; i < numCountries; i++) {			// for each country
//		in.getline(s, 256, '/');
//		countries[i].id = atoi(s);					// Read id
//		in.getline(s, 256, '/');
//		countries[i].name = s;						// Read name
//		in.getline(s, 256, '/');
//		countries[i].owner = atoi(s);;				// read owner id
//		in.getline(s, 256, '\n');
//		countries[i].troops = atoi(s);				// read number of troops
//	};
//	in.getline(s, 256, '\n');
//	map->numCountries = numCountries;				// number of countries in map
//	map->countries = countries;						// puts countries array in map
//}
///**
//* loads continents
//* @param in input stream with opened file
//* @param map map being created
//*/
//void SaverLoader::loadContinents(ifstream& in, Map* map) {
//	char s[256];
//	in.getline(s, 256, '\n');			// ski'file redability line
//	in.getline(s, 256, '\n');
//	int numContinents;
//	numContinents = atoi(s);			// reads number of continents
//	cout << numContinents << endl;
//	map->numContinents = numContinents;
//	Continent* continents = new Continent[numContinents];		// creates array of continents
//	for (int i = 0; i < numContinents; i++) {						// for each continent in the file
//		in.getline(s, 256, '/');
//		continents[i].name = s;									// read name
//		in.getline(s, 256, '\n');
//		continents[i].numCountries = atoi(s);;					// number of countries in continent
//		continents[i].countries = new int[continents[i].numCountries];
//		for (int j = 0; j < continents[i].numCountries; j++) {		// for each country in that continent
//			in.getline(s, 256, '\n');
//			continents[i].countries[j] = atoi(s);				// read country id
//		}
//	}
//	map->continents = continents;								// puts array of continents in map
//}
///**
//* loads adjencency matrix
//* @param in input stream with opened file
//* @param map map being created
//*/
//void SaverLoader::loadAdjacencies(ifstream& in, Map* map) {
//	map->adjencecies = new bool*[map->numCountries];
//	char s[256];
//	in.getline(s, 256, '\n');
//	for (int i = 0; i < map->numCountries; i++) {			// for each country in map
//		map->adjencecies[i] = new bool[map->numCountries];		// array of connected countries
//		in.getline(s, 256, '\n');
//		for (int j = 0; j < map->numCountries; j++) {
//			int adj;
//			in.getline(s, 256, '\t');
//			adj = atoi(s);;								// read true connection(1) or not connected (0)
//			if (adj) {
//				map->adjencecies[i][j] = true;
//			}
//			else {
//				map->adjencecies[i][j] = false;
//			}
//		}
//		in.getline(s, 256, '\n');
//	}
//}

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
		cout << numberOfPlayers << endl;

		// now we're going to do a loop to read the information for each player
		for (int r = 0; r < numberOfPlayers; ++r) {
			cout << "Inside reading player loop" << endl;
			// here is an empty player object
			Player* newPlayer = new Player();
			cout << "Creating newPLAYER" << endl;
			// these are temporary holders for information that we will feed to the data members of the player
			string playerName = "";
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
			cout << "PLAYER NAME: " << playerName << endl;
			newPlayer->setName(playerName);

			fin >> armies;
			if (fin.fail()) {
				throw 20;
			}
			cout << "ARMIES: " << armies << endl;
			newPlayer->setTotalNumArmies(armies);

			fin >> numArtillery;
			if (fin.fail()) {
				throw 20;
			}
			cout << "NUMBER ARTILLERY CARDS: " << numArtillery << endl;
			newPlayer->setNumCardsArtillery(numArtillery);

			fin >> numCavalry;
			if (fin.fail()) {
				throw 20;
			}
			cout << "NUMBER CAVALRY CARDS: " << numCavalry << endl;
			newPlayer->setNumCardsCavalry(numCavalry);

			fin >> numInfantry;
			if (fin.fail()) {
				throw 20;
			}
			cout << "NUMBER INFANTRY CARDS: " << numInfantry << endl;
			newPlayer->setNumCardsInfantry(numInfantry);

			fin >> numWild;
			if (fin.fail()) {
				throw 20;
			}
			cout << "NUMBER WILD CARDS: " << numWild << endl;
			newPlayer->setNumCardsWild(numWild);

			fin >> numContinents;
			if (fin.fail()) {
				throw 20;
			}
			cout << "CONTINENTS OWNED: " << numContinents << endl;
			newPlayer->setNumOwnedContinents(numContinents);

			fin >> numCountries;
			if (fin.fail()) {
				throw 20;
			}
			cout << "COUNTRIES OWNED: " << numCountries << endl;
			newPlayer->setNumOwnedCountries(numCountries);
			
			// let's create our owned continents. Right now, we're
			// going to create continents that ONLY have a name
			if (numContinents > 0) {
				cout << "CREATING OWNED CONTINENTS" << endl;
				continentList = new list<Continent*>();
				for (int j = 0; j < numContinents; ++j) {
					Continent* newContinent = new Continent();
					fin >> newContinent->name;
					cout << "CONTINENT: " << newContinent->name << endl;
					if (fin.fail()) {
						throw 20;
					}
					continentList->push_back(newContinent);
				}
			}
			cout << "SETTING OWNED CONTINENTS" << endl;
			newPlayer->setOwnedContinents(continentList);
			
			// let's create our owned countries. Right now, we're
			// going to create countries that ONLY have a name
			cout << "SETTING OWNED COUNTRIES: " << endl;
			if (numCountries > 0) {
				countryList = new list<Country*>();
				for (int j = 0; j < numCountries; ++j) {
					Country* newCountry = new Country();
					fin >> newCountry->name;
					cout << "COUNTRY: " << newCountry->name << endl;
					if (fin.fail()) {
						throw 20;
					}
					countryList->push_back(newCountry);
				}
			}
			newPlayer->setOwnedCountries(countryList);

			// now let's create our player cards
			// starting with artillery cards

			cout << "LOADING ARTILLERY CARDS " << endl;
			for (int a = 0; a < numArtillery; ++a) {
				string countryOnCard = "";
				fin >> countryOnCard; 
				cout << countryOnCard << " ";
				Card* newCard = new Card(countryOnCard, artillery);
				artilleryCards->push_back(newCard);
			}
			newPlayer->setPlayersArtilleryCards(artilleryCards);
			cout << endl;

			cout << "LOADING CAVALRY CARDS " << endl;
			for (int a = 0; a < numCavalry; ++a) {
				string countryOnCard = "";
				fin >> countryOnCard;
				cout << countryOnCard << " ";
				Card* newCard = new Card(countryOnCard, cavalry);
				cavalryCards->push_back(newCard);
			}
			cout << endl;
			newPlayer->setPlayersCavalryCards(cavalryCards);

			cout << "LOADING INFANTRY CARDS" << endl;
			for (int a = 0; a < numInfantry; ++a) {
				string countryOnCard = "";
				fin >> countryOnCard;
				cout << countryOnCard << " ";
				Card* newCard = new Card(countryOnCard, infantry);
				infantryCards->push_back(newCard);
			}
			newPlayer->setPlayersInfantryCards(infantryCards);
			cout << endl; 

			cout << "LOADING WILD CARDS" << endl;
			for (int a = numWild; a < numWild; ++a) {
				string countryOnCard = "";
				fin >> countryOnCard;
				Card* newCard = new Card(countryOnCard, wild);
				infantryCards->push_back(newCard);
			}
			newPlayer->setPlayersWildCards(wildCards);

			cout << "INSERTING PLAYER" << endl;
			gamePlayers->push_back(newPlayer);
		}


	}
	catch (...) {
		cout << "ERROR LOADING PLAYERS" << endl;
		return NULL;
	}

	fin.close(); 

	return gamePlayers;
}


list<Card*>* SaverLoader::loadCards(cardType card) {
	ifstream fin;
	int numCards;
	string heading;
	list<Card*>* cardList = new list<Card*>();

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

void SaverLoader::savePlayersAndCards(Game* game) {
	 ofstream fout; 

	 fout.open(fileName, ios::app);

	 fout << "PLAYERS " << endl;
	 fout << game->gamePlayers->size() << endl;
	 for (vector<Player*>::iterator i = (game->gamePlayers)->begin(); i != (game->gamePlayers)->end(); ++i) {
		 fout << (*i)->getName() << " " << (*i)->getTotalNumArmies() << " " << (*i)->getNumCardsArtillery() << " ";
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
		 fout << "ARTILLERY ";
		 list<Card*>* artilleryCards = (*i)->getPlayersArtilleryCards();

		 for (list<Card*>::iterator j = artilleryCards->begin(); j != artilleryCards->end(); ++j) {
			 fout << (*j)->getCountryOnCard() << " ";
		 }
		 fout << endl;

		 // write out the cavalry card names
		 fout << "CAVALRY ";
		 list<Card*>* cavalryCards = (*i)->getPlayersCavalryCards();

		 for (list<Card*>::iterator j = cavalryCards->begin(); j != cavalryCards->end(); ++j) {
			 fout << (*j)->getCountryOnCard() << " ";
		 }
		 fout << endl;

		 // write out the infantry card names
		 fout << "INFANTRY ";
		 list<Card*>* infantryCards = (*i)->getPlayersInfantryCards();

		 for (list<Card*>::iterator j = infantryCards->begin(); j != infantryCards->end(); ++j) {
			 fout << (*j)->getCountryOnCard() << " ";
		 }
		 fout << endl;

		 // write out the wild card names
		 fout << "WILD ";
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
		for (list<Card*>::iterator i = game->gameArtilleryCards->begin(); i != game->gameArtilleryCards->end(); ++i) {
			fout << (*i)->getCountryOnCard() << " ";
		}
	}
	fout << endl;

	// write out the infantry cards
	fout << "INFANTRY ";
	fout << game->gameInfantryCards->size() << " ";

	if (game->gameInfantryCards->size() > 0) {
		for (list<Card*>::iterator i = game->gameInfantryCards->begin(); i != game->gameInfantryCards->end(); ++i) {
			fout << (*i)->getCountryOnCard() << " ";
		}
	}
	fout << endl;

	// write out the cavalry cards
	fout << "CAVALRY ";
	fout << game->gameCavalryCards->size() << " ";

	if (game->gameCavalryCards->size() > 0) {
		for (list<Card*>::iterator i = game->gameCavalryCards->begin(); i != game->gameCavalryCards->end(); ++i) {
			fout << (*i)->getCountryOnCard() << " ";
		}
	}
	fout << endl;

	// write out the wild cards
	fout << "WILD ";
	fout << game->gameWildCards->size() << " ";

	if (game->gameWildCards->size() > 0) {
		for (list<Card*>::iterator i = game->gameWildCards->begin(); i != game->gameWildCards->end(); ++i) {
			fout << (*i)->getCountryOnCard() << " ";
		}
	}
	fout << endl;

	fout << "NUMCARDSETSTRADED " << (game->numCardSetsTradedIn) << endl;
	fout << "CURRENTPLAYER " << (game->currentPlayer)->getName() << endl;
	fout << "CURRENTPHASE " << (game->phase) << endl;
}

