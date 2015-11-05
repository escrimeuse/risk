#include "map.h"

using namespace std;

namespace MapAPI{
/**
 * Delallocates spaces dynamically allocated by Map
 * @param map to be deallocated
 */
	void deleteMap(Map* map){
		delete [] map->countries;
		delete [] map->continents;
		for(int i = 0; i < map->numCountries; i++)
			delete [] map->adjencecies[i];
		delete []map->adjencecies;
	}
	/**
	 * Displays the map information, list of countries in the map
	 * and a list of continents
	 * @param map to be diplayed
	 *
	 */
	void displayMap(Map* map){
		infoMap(map);
		listCountries(map);
		listContinents(map);
	}
	/**
	 * Displays the map name, number of countries and continents
	 * @param map to be diplayed
	 *
	 */
	void infoMap(Map* map){
		cout << "Map Name: " << map->name << endl;
		cout << "Countries: " << map->numCountries << endl;
		cout << "Continents " << map->numContinents << endl;
	}
	/**
	 * Displays a list of countries in a map
	 * @param map to be diplayed
	 *
	 */
	void listCountries(Map* map){
		cout << "__________________________________________________________" << endl;
		cout << "Country ID\tName\t\tOwner Id\tTroops" << endl;
		cout << "----------------------------------------------------------"<< endl;
		for(int i = 0; i < map->numCountries; i++){
			cout <<map->countries[i].id << "\t\t" << map->countries[i].name
					<< "\t\t" << map->countries[i].owner << "\t"
					<< map->countries[i].troops << endl;
		}
		cout << "__________________________________________________________"<< endl;
	}
	/**
	 * Displays a list of continents in the map
	 * @param map to be diplayed
	 *
	 */
	void listContinents(Map* map){
		cout << "__________________________________________________________"<< endl;
		cout << "Continent\tNumber of Countries\tCountries" << endl;
		cout << "----------------------------------------------------------"<< endl;
		for(int i = 0; i < map->numCountries; i++){
			cout << map->continents[i].name << "\t\t\t" << map->continents[i].numCountries << "\t\t";
			for(int j = 0; j < map->continents[i].numCountries-1; j++)
				cout << map->continents[i].countries[j] << ", ";
			cout << map->continents[i].countries[map->continents[i].numCountries-1] << endl;
		}
		cout << "__________________________________________________________"<< endl;
	}
}
