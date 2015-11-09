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
	static string uName;
	static void welcome() {
		cout << "=======================================================\n"
			<<  "Welcome to Jennifer's Map Creation and Editing program!\n"
			<<  "=======================================================\n"
			<< "What is your first name?: ";
		cin >> uName;
		cout << "\nWelcome, " << uName << "." << endl;
		std::cin.ignore();
	}

	//demonstration of the country-creation
	static Country* makeCountry() {
		string userIn;
		int userNum = 0;
		cout << "\nWhat is the name of the country you want to make?: ";
		cin >> userIn;
		Country *newCountry = new Country();
		newCountry->setName(userIn);
		cout <<"Current country count is: " << newCountry->getCount() << ".\n\n"
			<< "There is no owner for " << newCountry->getName() <<". Who owns it?: ";
		cin >> userIn;
		newCountry->setOwner(userIn);
		cout << "\n" << newCountry->getOwner() << " is the owner of " << newCountry->getName() << ".\n" << endl;
		std::cin.ignore();
		//making sure user inputs an int
		while (true) {
			cout << "There are " << newCountry->getArmies() << " armies in " << newCountry->getName() << ".\n"
				<< "How many armies do you wish to put in " << newCountry->getName() << "?: ";
			getline(cin, userIn);

			// This code converts from string to number safely.
			stringstream myStream(userIn);
			if (myStream >> userNum) {
				newCountry->setArmies(userNum);
				cout << "There are " << newCountry->getArmies() << " armies in " << newCountry->getName() << ".\n\n"
					<< "Congratulations, " << newCountry->getName() <<" is offcially a country!" << endl;
				return newCountry;
				break;
			}
			else
				cout << "Not a valid choice. Please try again." << endl;
		}

		delete newCountry;
		newCountry = NULL;
		return newCountry; //shouldn't actually get here though
		
	}

	//demonstration of the continent-creation
	static Continent* makeContinent() {
		string userIn;
		int userNum = 0;
		cout << "\nWhat is the name of the continent you want to make?: ";
		cin >> userIn;
		Continent *newContinent = new Continent();
		newContinent->setName(userIn);
		cout << "Current continent count is: " << newContinent->getCount() << ".\n\n"
			<< "There are no countries in " << newContinent->getName() << "." << endl;
		std::cin.ignore();//needed so getLine can function properly later

		//making sure user inputs an int
		while (true) {
			cout << "How many countries do you wish to add to " << newContinent->getName() << "? (must be greater than 1): ";
				getline(cin, userIn);

			// This code converts from string to number safely.
			stringstream myStream(userIn);
			if (myStream >> userNum && userNum>1) {
				for (int i = 0; i < userNum; i++) {
					newContinent->addCountry(makeCountry()); //add the newly made country to the continent
				}
				cout << "\nAll countries had been made!" << endl;
				break;
			}
			else
				cout << "Not a valid choice. Please try again." << endl;
		}
		
		cout << "The following countries are in " << newContinent->getName() << ": " << newContinent->getCountryNames() + ".\n"
			 << "Congratulations, " << newContinent->getName() << " is a continent.\n\n"
			 << "Please note: the concept of CONNECTIVITY is implemented in the Map option of the main menu." << endl;

		return newContinent;
	}

	//demonstration of the map-creation
	static MapDemo* makeMap() {
		string mapName;
		string userIn;
		cout << "\nWhat is the name of the map you want to make?: ";
		cin >> mapName;
		MapDemo *newMap = new MapDemo(mapName);
		cout << "\nCurrently, there is only one size of map available. " << newMap->getName() << " will have 3 continents, with 2 countries in each.\n\n"
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

		newMap->demoMap(); //function creates adjacencies between countries

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
		
		

		//test if the map's continents are valid
		cout << "\nNow to check if the map's continents are valid." << endl;
		cout << newMap->getContinentsValid() << endl;
		cout << "If the number on the line above is 1, the map's continents are valid, if it is 0, they are not valid." << endl;

		//test if the map is connected
		cout << "\nNow to check if the map is connected." << endl;
		cout << newMap->getIsConnected() << endl;
		cout << "If the number on the line above is 1, the map is connected, if it is 0, it is not connected." << endl;

		std::cin.ignore();
		return newMap;
		
	}

	//choices of the user from the main menu
	static void userAction(int choice) {
		switch (choice) {
		case 1: {
			Country* c = makeCountry();
			c->resetCount();
			delete c;
			break; 
		}
		case 2: {
			Continent * c = makeContinent();
			c->resetCount();
			delete c;
			break;
		}
		case 3: {
			cout << "Please note that after this section is completed, the program will end. If you wish to get back to the main menu, please restart the program." << endl;
			Map* m = makeMap();
			cout << endl;
			cout << "Saving the map as 'TestMap.map'..." << endl;
			SaverLoader *s = new SaverLoader("TestMap");
			s->save(m);
			cout << "Saved map as 'TestMap.map'" << endl;
			delete m;
			cout << "\nThat's it for this demo. To get back to the main menu, please restart the program.\n"
				<< "Goodbye!\n";
			exit(0);
			break;//shouldn't reach this point
		}
		case 4: exit(0);
		}
	}
}

using namespace mapDemo;


int main() {
	
	welcome();

	while (true) {
		cout << "\nWould you like to:\n"
			<< "[ 1 ] Test creating a country?\n"
			<< "[ 2 ] Test creating a continent?\n"
			<< "[ 3 ] Test creating a map?\n"
			<< "[ 4 ] Exit" << endl;
		string input = "";
		getline(cin, input);

		// This code converts from string to number safely.
		stringstream myStream(input);
		int userChoice = 0;
		if (myStream >> userChoice)
			userAction(userChoice);
		else
			cout << "Not a valid choice. Please try again" << endl;
	}
}

