#ifndef SAVEGAME_H
#define SAVEGAME_H

#include "SaveGameBuilder.h"
#include "../SaveLoad/SaverLoader.h"
#include "../GameBuilder/Game.h"

class SaveGame : public SaveGameBuilder {

private:
	Game* thegametosave;
	SaverLoader* thesaverloader;

public:
	SaveGame(Game* game, SaverLoader* saver);
	void saveMap();
	void savePlayers();
	void saveState();


};

#endif
