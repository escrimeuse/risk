#include "MapObserver.h"

MapObserver::MapObserver() {
	subject = NULL;
}

MapObserver::MapObserver(Map* mapSubject) {
	subject = mapSubject;
}

void MapObserver::update() {
	displayMap();
}

void MapObserver::displayMap() {
	ofstream fout;
	fout.open("mapobs.txt",ios::app);

	fout << "******************" << endl;
	fout << "     MAP INFO     " << endl;
	fout << "******************" << endl;
	fout << endl; 
	
	for (vector<Continent*>::iterator i = subject->getContinents()->begin(); i != subject->getContinents()->end(); ++i) {
		fout << endl << (*i)->getName() << endl;
		fout << "ID\tCOUNTRY\tOWNER\t# of Armies" << endl;
		for (vector<Country*>::iterator j = (*i)->getCountries()->begin(); j != (*i)->getCountries()->end(); ++j) {
			fout << (*j)->getId() << "\t" << (*j)->getName() << "\t" << (*j)->getOwner()->getName() << "\t" << (*j)->getArmies() << "\t" <<  endl;
			subject->printAdjacentCountryNames(fout,(*j)->getName());
		}
	}
}
