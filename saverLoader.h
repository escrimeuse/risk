#ifndef SAVERLOADER_H
#define SAVERLOADER_H

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "map.h"

using namespace std;

class SaverLoader{
public:
    SaverLoader();
    SaverLoader(string fn);
    void save(Map& map);
    static const string extension;
    Map* load();
private:
    string fileName;
    char* getTime();
    void saveMap(ofstream& out, Map map);
    void saveCountries(ofstream& out, Map map);
    void saveContinents(ofstream& out, Map map);
    void saveAdjencencies(ofstream& out, Map map);
    void loadMap(ifstream& in, Map* map);
    void loadCountries(ifstream& in, Map* map);
    void loadContinents(ifstream& in, Map* map);
    void loadAdjacencies(ifstream& in, Map* map);
};

#endif
