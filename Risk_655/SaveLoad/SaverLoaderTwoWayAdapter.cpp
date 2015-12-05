#include "SaverLoaderTwoWayAdapter.h"

SaverLoaderTwoWayAdapter::SaverLoaderTwoWayAdapter(SaverLoader *s) {
	sl = s;
	csl = NULL;

}
SaverLoaderTwoWayAdapter::SaverLoaderTwoWayAdapter(ConquestSaverLoader *c) {
	sl = NULL;
	csl = c;
}
void SaverLoaderTwoWayAdapter::saveConquestMap(Map *myMap) {
	csl->savingMap(myMap);
}
void SaverLoaderTwoWayAdapter::saveNormalMap(Map *myMap) {
	sl->savingMap(myMap);
}
Map* SaverLoaderTwoWayAdapter::loadNormalMap() {
	return sl->loadMap();
}
Map* SaverLoaderTwoWayAdapter::loadConquestMap() {
	return csl->loadMap();
}