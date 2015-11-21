#include "existingGameBuilder.h"
#include "Game.h"

ExistingGameBuilder::ExistingGameBuilder(SaverLoader* gameFile) {
	saveload = gameFile;
	builtGame = new Game();
}

void ExistingGameBuilder::buildMap() {
	//builtGame->map = saveload->loadMap();
}

void ExistingGameBuilder::buildPlayers() {
	//builtGame->currentPlayer = saveload->loadPlayers();
}

void ExistingGameBuilder::buildState() {

}

