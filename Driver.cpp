// Assignment #2 - COMP345 - Section DI - Fall 2015
// Author: Jennifer Sunahara (27590628)
//
//This is the map demo-driver. It is designed to show off the functionality of the 
//Map, Continent and Country classes.

#include <iostream>
#include<sstream>
#include<string>
#include<list>

using namespace std;

#include "Country.h"
#include "Continent.h"
#include "MapDemo.h"
#include "SaveLoader.h"

//organised the functions needed for the demo into its own namespace to avoid the global namespace
namespace mapDemo {
	
	
	//demonstration of the map-creation
	static MapDemo* makeMap() {
		string mapName;
		string userIn;
		cout << "\nWhat is the name of the map you want to make?: ";
		cin >> mapName;
		MapDemo *newMap = new MapDemo(mapName);
		cout << "\n" << newMap->getName() << " will have 3 continents, with 2 countries in each.\n\n"
			<< "Please name your 3 continents: " << endl;
		newMap->setContinentNames();
		cout << "All continents have been named. The names are: " << newMap->getContinentNames() << "\n"
			<< "Please name your 6 countries: " << endl;
		newMap->setCountryNames();
		
		cout << "\nAll countries have been named. The names are: " << newMap->getCountryNames() << "\n" << endl;
		
		//printing the countries per continent
		newMap->printContinentsCountries(1);
		newMap->printContinentsCountries(2);
		newMap->printContinentsCountries(3);
		cout << endl;

		//DEMO1 phase
		cout << "\n DEMO1: Creating an incompletely connected map..." << endl;
		newMap->demoMap1(); //function creates adjacencies between countries

		string check = "";
		if (newMap->getContinentsValid())//test if the map's continents are valid
			check = "true";
		else
			check = "false";
		cout << "\nContinents Valid?: "<< check << endl;

		check = ""; // precaution...
		if (newMap->getIsConnected())//test if the map is connected
			check = "true";
		else
			check = "false";
		cout << "\nAll countries connected?: " << check << endl;
		
		//DEMO2 phase
		cout << "\n DEMO2: Adding adjacencies to have valid continents..." << endl;
		newMap->demoMap2(); //function creates more adjacencies between countries
		if (newMap->getContinentsValid())//test if the map's continents are valid
			check = "true";
		else
			check = "false";
		cout << "\nContinents Valid?: " << check << endl;

		check = ""; // precaution...
		if (newMap->getIsConnected())//test if the map is connected
			check = "true";
		else
			check = "false";
		cout << "\nAll countries connected?: " << check << endl;

		//DEMO3 phase
		cout << "\n DEMO3: Adding adjacencies to have connected map..." << endl;
		newMap->demoMap3(); //function creates more adjacencies between countries
		if (newMap->getContinentsValid())//test if the map's continents are valid
			check = "true";
		else
			check = "false";
		cout << "\nContinents Valid?: " << check << endl;

		check = ""; // precaution...
		if (newMap->getIsConnected())//test if the map is connected
			check = "true";
		else
			check = "false";
		cout << "\nAll countries connected?: " << check << endl;

		//allow user to create adjacency
		cout << "\nLet's make 2 more countries adjacent."
			 << "\nWhich two countries would you like to make adjacent?\n"
			 << "First country: ";
		string c1, c2;
		cin >> c1;
		cout << "Second country: ";
		cin >> c2;
		newMap->makeAdjacent(c1, c2);
		newMap->printAdjacentCountryNames(c1);
		newMap->printAdjacentCountryNames(c2);

		std::cin.ignore();
		return newMap;
		
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
					cout << "Continent name is " << target->getName()<<".\n";
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

	static int mapCreator(int choice) {
		switch (choice) {
		case 1: {
			Map* m = makeMap();
			cout << endl;
			cout << "Saving the map as 'TestMap.map'..." << endl;
			SaverLoader *s = new SaverLoader("TestMap");
			s->save(m);
			cout << "Saved map as 'TestMap.map'" << endl;
			return 0;
		}
		case 2: case 3: case 4: {
			cout << "\n[ FEATURE CURRENTLY UNAVAILABLE :( ]\n";
			return 0;//return to map creation menu
		}
		case 5: { return 500; }//return to main menu
		}
		return 0;//shouldnt' reach here, but will return to main menu
	}

	static int mapEditor(int choice) {
		switch (choice) {
			case 1: {//Edit good map
				cout << "Edit good map";
				SaverLoader *s = new SaverLoader("TestMap");
				Map *m = s->load();
				if (m != NULL) {
					editMap(m);
					if (m->getIsConnected() && m->getContinentsValid())
						s->save(m);
					else
						cout << "Map not valid. Cannot save map." << endl;
					return 0;
				}
				else {
					cout << "Invalid map! SHAME!" << endl;
					return 0;
				}
								
			}
			case 2: {//Edit bad1 map
				cout << "Attempting to load map...";
				SaverLoader *s = new SaverLoader("MyBadMap1");
				Map *m = s->load();
				if (m != NULL) {
					editMap(m);
					if (m->getIsConnected() && m->getContinentsValid())
						s->save(m);
					else
						cout << "Map not valid. Cannot save map." << endl;
					return 0;
				}
				else {
					cout << "Invalid map! SHAME!" << endl;
					return 0;
				}
			}
			case 3: {//Edit bad2 map
				cout << "Attempting to load map...";
				SaverLoader *s = new SaverLoader("BadMap2");
				Map *m = s->load();
				if (m != NULL) {
					editMap(m);
					if (m->getIsConnected() && m->getContinentsValid())
						s->save(m);
					else
						cout << "Map not valid. Cannot save map." << endl;
					return 0;
				}
				else {
					cout << "Invalid map! SHAME!" << endl;
					return 0;
				}
			}
			case 4: {//Edit bad3 map
				cout << "Attempting to load map...";
				SaverLoader *s = new SaverLoader("BadMap3");
				Map *m = s->load();
				if (m != NULL) {
					editMap(m);
					if (m->getIsConnected() && m->getContinentsValid())
						s->save(m);
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
			case 5: { return 500; }//return to main menu
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

			while (true) {
				cout << "\nWhat size map would you like to create:\n"
					<< "[ 1 ] Demo (2 players)\n"
					<< "[ 2 ] Small (2-3 players)\n"
					<< "[ 3 ] Medium (3-4 players)\n"
					<< "[ 4 ] Large (5-6 players)\n"
					<< "[ 5 ] Exit" << endl;
				string input = "";
				getline(cin, input);

				// This code converts from string to number safely.
				stringstream myStream(input);
				int userChoice = 0;
				if (myStream >> userChoice) {
					int check = mapCreator(userChoice);
					if (check == 500)
						return 500; //if mapCreation returned 500, return to main menu
				}
				else
					cout << "Not a valid choice. Please try again" << endl;
			}
			return 0;//shouldn't reach this
		}
		case 2: {
			cout << "=========================\n"
				<< "Welcome to the Map Editor !\n"
				<< "=========================\n";

			while (true) {
				cout << "\nWhich map would you like to edit:\n"
					<< "[ 1 ] Good\n"
					<< "[ 2 ] Bad1 (Corrupt File)\n"
					<< "[ 3 ] Bad2 (Continents Invalid)\n"
					<< "[ 4 ] Bad3 (Disconnected Map)\n"
					<< "[ 5 ] Exit" << endl;
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
		cout <<"=============================\n"
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

}

using namespace mapDemo;

int  main() {
	mainMapMenu();
}

