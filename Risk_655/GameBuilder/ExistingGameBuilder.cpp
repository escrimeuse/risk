#include "existingGameBuilder.h"
#include "Game.h"

ExistingGameBuilder::ExistingGameBuilder(SaverLoader* gameFile) {
	saveload = gameFile;
	myGame = new Game();
}

void ExistingGameBuilder::buildMap() {
	myGame->map = saveload->loadMap();
}

void ExistingGameBuilder::buildPlayers() {
	myGame->gamePlayers = saveload->loadPlayers();
	
	// now we need to do the correct association of continents and players
	for (vector<Player*>::iterator i = myGame->gamePlayers->begin(); i != myGame->gamePlayers->end(); ++i) {

		if ((*i)->getNumOfOwnedContinents() > 0) {

			// get the name of each continent owned, and then set that continent equal to the one in the map
			for (list<Continent*>::iterator j = (*i)->getOwnedContinents()->begin(); j != (*i)->getOwnedContinents()->end(); ++j) {
				
				string continentName = (*j)->getName();
				
				*j = myGame->map->getContinentByName(continentName);
				
				(*j)->setOwner((*i)); // set the owner
			}
			
		}
		
	}
	
	// now we need to do the correct association of countries and players
	for (vector<Player*>::iterator i = myGame->gamePlayers->begin(); i != myGame->gamePlayers->end(); ++i) {
		
		if ((*i)->getNumOfOwnedCountries() > 0) {

			// get the name of each country owned, and then set that country equal to the one in the map
			for (list<Country*>::iterator j = (*i)->getOwnedCountries()->begin(); j != (*i)->getOwnedCountries()->end(); ++j) {
				string countryName = (*j)->getName();
				*j = myGame->map->getCountryByName(countryName);
				(*j)->setOwner((*i));
			}

		}

	}
	
}

void ExistingGameBuilder::buildState() {

	// first load the cards
	myGame->gameArtilleryCards = saveload->loadCards(artillery);
	myGame->gameCavalryCards = saveload->loadCards(cavalry);
	myGame->gameInfantryCards = saveload->loadCards(infantry);
	myGame->gameWildCards = saveload->loadCards(wild);
	


	// now load the total number of card sets traded in
	myGame->numCardSetsTradedIn = saveload->loadNumCardSetsTradedIn();

	

	// now load the current player:
	string currentPlayerName = saveload->loadCurrentPlayer(); // first get the name of the current player

	if (currentPlayerName == "NULL") {
		myGame->currentPlayer = NULL;
	}
	else {

		for (vector<Player*>::iterator i = myGame->gamePlayers->begin(); i != myGame->gamePlayers->end(); ++i) {
			// search the players for the one with the corresponding name, and set
			// current player appropriately
			if ((*i)->getName().compare(currentPlayerName) == 0) {
				myGame->currentPlayer = *i;
				break;
			}
		}
	}
	// now load the current phase (reinforcement, battle, fortification...)
	myGame->phase = saveload->loadCurrentPhase();

	// now load the game name
	myGame->gameName = saveload->loadGameName();
	



}

