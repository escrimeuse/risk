#include "SaveDirector.h"

SaveDirector::SaveDirector(SaveGameBuilder* saver) {
	theSaver = saver;
}

void SaveDirector::saveGame() {
	theSaver->saveMap();
	theSaver->savePlayers();
	theSaver->saveState();
}