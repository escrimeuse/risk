#include "SaveGame.h"

SaveGame::SaveGame(Game* game, SaverLoader* saver) {
	thegametosave = game;
	thesaverloader = saver;
}
void SaveGame::saveMap() {
	thesaverloader->savingMap(thegametosave->map);

};
void SaveGame::savePlayers() {
	thesaverloader->savePlayersAndCards(thegametosave);
}
void SaveGame::saveState() {
	thesaverloader->saveState(thegametosave);
}