// Assignment #3 - COMP345 - Section DI - Fall 2015
// Author of SAVERLOADER: Caio Paiva, Catryn Griffiths, Jennifer Sunahara
//
//This is the implementation file ConquestSaverLoader.cpp of the class ConquestSaverLoader.
//The interface of this class is in the header file ConquestSaverLoader.h.

#include "ConquestSaverLoader.h"
#include "../Map/Map.h"
#include "../Map/Country.h"
#include "../GameBuilder/Game.h"

using namespace std;
//File extension
const string ConquestSaverLoader::extension = ".map";

/**
* Default Constructor
* Name the file unnamed.map
*/
ConquestSaverLoader::ConquestSaverLoader() {			//Initialize fileName to unnamed.map
	fileName = "";
	fileName.append("unnamed");
	fileName.append(ConquestSaverLoader::extension);
}

/**
* Non-default Constructor
* @param fn name of the file
*/
ConquestSaverLoader::ConquestSaverLoader(string fn) {	// Initialize fileName to GivenName.map
	fileName = "";
	fileName.append(fn);				// Appends file name and extension
	fileName.append(ConquestSaverLoader::extension);
}

/**
* Saves a given map into file
*/
void ConquestSaverLoader::savingMap(Map *map) {
	ofstream out(fileName.c_str());		//Opens or creates file
	saveMap(out, map);					// Save map info
	saveContinents(out, map);			//Save Continent list
	saveTerritories(out, map);			//Save connection between countries
	out.close();						//Close file
}

/**
* Saves map information
* @param out Stream with opened file
* @param map map to be saved
*/
void ConquestSaverLoader::saveMap(ofstream& out, Map *map) {
	out << "["<< map->getName()<<"]\n"
		<< "author=00000000\n"
		<< "warn=yes\n"
		<< "image=00000000\n"
		<< "wrap=no\n"
		<< "scroll=horizontal\n\n";
	//note use of dummy value 00000000, as out game does not have author names or images of the map
}

void ConquestSaverLoader::saveContinents(ofstream& out, Map *map) {
	out << "[Continents]\n";
	for (int i = 0; i < map->getNumContinents(); ++i) {	// for each continent in the map
		Continent *current = (*map->getContinents())[i];
		out << current->getName() << " " << current->getControlValue() << endl; // Continent info
		//note use of white-space to delimit the continent name and control value, 
		//as our game allows the "=" character, but not whitespace in continent names
	}
	out << "\n";
}

void ConquestSaverLoader::saveTerritories(ofstream& out, Map *map) {
	out << "[Territories]\n";
	for (int i = 0; i < map->getNumContinents(); ++i) {	// for each continent in the map
		Continent *currentContinent = (*map->getContinents())[i];
		for (int j = 0; j < (currentContinent->getNumCountries()); j++) {//for each country in that continent
			Country *currentCountry = (*currentContinent->getCountries())[j];
			out << currentCountry->getName() << " 000 000 " << currentContinent->getName(); // Country info, with dummy value of 000 as coordinates, as our game does not make use of coordinates
			for (int k = 0; k < map->getNumCountries(); ++k) {	// compare currentCountry to each country in the map
				Country *targetCountry = (*map->getCountries())[k];
				if (currentCountry->getId()!= targetCountry->getId() && map->checkIsAdjacent(currentCountry, targetCountry)) {
					out << " " << targetCountry->getName();
				}
			}
			out << "\n";
		}
		out << "\n";
		//Note again the use of whitespace to delimit the country name from the dummy coordinates, the continent name and the adjacent countries
		//This is because we permit the use of the comma in the name strings, but we do not permit whitespace.
	}
}


Map* ConquestSaverLoader::loadMap() {
	struct CountryL {
		string name;
		int id;
		string continentName;
		vector<string> *adjCountries;
		};

	struct ContinentL {
		string name;
		int id;
		int controlValue;
	};

	string mapName = "";
	
	vector<CountryL*>* countryList = new vector<CountryL*>;
	vector<ContinentL*>* continentList = new vector<ContinentL*>;

	ifstream fin;

	fin.open(fileName);
	try {

		//read in the map name
		fin >> mapName;
		if (fin.fail()) {
			throw 20;
		}
		int mapNameSize = mapName.size();
		mapName = mapName.substr(1, mapNameSize - 2);//cutting out the [] symbols from the name string

		//skipping 6 lines from author until the first continent
		string garbage = "";
		fin >> garbage;
		if (fin.fail()) {
			throw 20;
		}
		fin >> garbage;
		if (fin.fail()) {
			throw 20;
		}
		fin >> garbage;
		if (fin.fail()) {
			throw 20;
		}
		fin >> garbage;
		if (fin.fail()) {
			throw 20;
		}
		fin >> garbage;
		if (fin.fail()) {
			throw 20;
		}
		fin >> garbage;
		if (fin.fail()) {
			throw 20;
		}

		//reading in the continents now
		int i = 0;
		string check = "";
		fin >> check;
		if (fin.fail()) {
			throw 20;
		}

		while (check.compare("[Territories]")!=0){//so long as we have not reached the next section
			ContinentL* newContinent = new ContinentL();

			(newContinent->name)=check;
			if (fin.fail()) {
				throw 20;
			}
			
			fin >> newContinent->controlValue;
			if (fin.fail()) {
				throw 20;
			}
			
			//no need to have the id assigned as we can do that later when constructing continents

			continentList->push_back(newContinent);
			i++;

			fin >> check;
			if (fin.fail()) {
				throw 20;
			}

		}//check now holds the string "[Territories]", so it is time to begin reading in countries
				
		//reading in countries now
		string line="a";
		getline(fin, line);
		
		while (getline(fin, line))  // same as: while (getline( myfile, line ).good())-- so basically keep reading until the end of file
		{
			if(line.size()>0)
			{
				CountryL* newCountry = new CountryL();

				//extracting the country name
				for (int i = 0; i < line.size(); i++) {
					if ((line.at(i)) == ' ') {
						newCountry->name = line.substr(0, i);
						line = line.substr(i + 9);// (i is the index of the first whitespace + " 000 000 ", which is 8 char) so next char should be of continent name
						break;
					}
				}

				//extracting continent name
				for (int i = 0; i < line.size(); i++) {
					if ((line.at(i)) == ' ') {
						newCountry->continentName = line.substr(0, i);
						line = line.substr(i + 1);// (i is the index of the first whitespace, so next char should be of an adjacent country name
						break;
					}
				}

				//reading in the adjacent country names
				(newCountry->adjCountries) = new vector<string>;
				bool done = false;
				string spaceChar = " ";
				while (!done) {
					for (int i = 0; i < line.size(); i++) {
						if (line.find(spaceChar) != std::string::npos) {
							if ((line.at(i)) == ' ') {
								string temp = line.substr(0, i);
								(*(newCountry->adjCountries)).push_back(temp);
								line = line.substr(i + 1);// (i is the index of the first whitespace) so next char should be of the next adjacent country name
								break;
							}
						}
						else {
							(*(newCountry->adjCountries)).push_back(line);
							done = true;
							break;
						}
					}
				}
				countryList->push_back(newCountry);//add this countyL to countylist
			}
		}// finished extracting countries
		
		//double check the country section for invalid stuff???--should be ok because it's all string

		Map *loadedMap = new Map(mapName, countryList->size(), continentList->size(),0);//note the use of the dummy int constructor
		
		//iterate through all the continents and add to map
		for (vector<ContinentL*>::iterator i = continentList->begin(); i != continentList->end(); ++i) {
			Continent *continentToAdd = new Continent((*i)->name, (*i)->controlValue);
			loadedMap->addContinent(continentToAdd);
			continentToAdd = NULL;//to be double sure that I am not overwriting my continents
		}

		//iterate through all the countries and add to map
		for (vector<CountryL*>::iterator i = countryList->begin(); i != countryList->end(); ++i) {
			Country *countryToAdd = new Country();
			countryToAdd->setName((*i)->name);
			Continent *target = loadedMap->getContinentByName((*i)->continentName);
			if (target == NULL) {
				throw 20;
			}
			loadedMap->addCountry(countryToAdd);
			target->addCountry(countryToAdd);// should only get here if the target continent exists in the map already
			countryToAdd = NULL;//precaution
			target = NULL;//also precaution
		}

		//set adjacencies
		for (vector<CountryL*>::iterator i = countryList->begin(); i != countryList->end(); ++i) {
			Country *country1 = loadedMap->getCountryByName((*i)->name);
			vector<string> *adjCountryList = (*i)->adjCountries;
			for (vector<string>::iterator j = adjCountryList->begin(); j != adjCountryList->end(); ++j) {
				Country *country2 = loadedMap->getCountryByName(*j);
				if (country1 == NULL || country2 == NULL) {
					cout << "Invalid adjacency list" << endl;
					throw 20;
				}
				loadedMap->makeAdjacent(country1->getName(), country2->getName());//should only get here if both country names are valid
				//problem with country and continent ID numbers...
			}
		}

		bool valid = loadedMap->getIsConnected();
		bool connected = loadedMap->getContinentsValid();

		fin.close();

		if (valid && connected) {
			return loadedMap;
		}
		return NULL;

	}
	catch (...) {
		cout << "ERROR:" << endl;
		cout << "The map file you are trying to load has been corrupted!" << endl;
		cout << "It is to RISKy to load it >:-|" << endl;
		return NULL;
	}
}