#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

/*
FILE: PlayerView.h
AUTHOR: Cathryn Griffiths (29108777)
DESCRIPTION: This header file contains the declaration for the PlayerView class, which extends the Observer class. 
*/

#include "Observer.h"
#include "../Player/Player.h"
#include "../Map/Country.h"
#include "../Map/Continent.h"

class PlayerView : public Observer {

private:
	Player *subject;	// the player being observed	
	void displayCountries(ofstream& fout);	// function to ouput the countries owned by the player being observed
	void displayContinents(ofstream& fout);	// function to output the continents owened by the player being observed
	void displayCards(ofstream& fout);

public:
	PlayerView();	// default constructor
	PlayerView(Player* subject);	// constructor that sets the player being observed to the player passed as an argument
	void displayPlayerInfo();	// displays the observed player's information to the screen
	void update();	// update function, inherited from the observer class

	
};
#endif
