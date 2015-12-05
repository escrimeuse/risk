#pragma once

#include "../SaveLoad/SaverLoader.h"
#include "../SaveLoad/ConquestSaverLoader.h"

class SaverLoaderTwoWayAdapter : public SaverLoader, public ConquestSaverLoader {
private:
	SaverLoader *sl;
	ConquestSaverLoader *csl;
public:
	SaverLoaderTwoWayAdapter(SaverLoader *s);
	SaverLoaderTwoWayAdapter(ConquestSaverLoader *c);
	void saveConquestMap(Map *myMap);
	void saveNormalMap(Map *myMap);
	Map* loadNormalMap();
	Map* loadConquestMap();

};