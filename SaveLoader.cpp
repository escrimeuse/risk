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
void SaverLoader::save(Map *map) {
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
Map* SaverLoader::load() {

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

