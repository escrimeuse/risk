#ifndef BATTLE_H
#define BATTLE_H

#include "../Player\Player.h"
#include "../Map\Map.h"
#include "../StrategyPattern/Strategy.h"
#include <stdlib.h> 

class Battle {

private:
	
	// DATA MEMBERS
	struct BattlePlayer {
		Player* player;		// a pointer to the player
		Country* country;	// a pointer to the country used to attack
		int numOfDice;		// the number of dice rolled by the player
		int* dice;			// an array of dice rolls
		bool isComputer;
	} attacker, defender;

	// MUTATORS (.)
	// NOTE: These mutators were coded as . as they contain simple, one-line code
	void setAttacker(Player* theAttacker);
	void setDefender(Player* theDefender);

	// ACCESSORS (.)
	// NOTE: These accessors were coded as . as they contain simple, one-line code
	Player* getAttacker();
	Player* getDefender();

	// SERVICE METHODS

	// this function allows the attacking player to select the country they wish to attack with, and sets the attacking country accordingly
	int selectAttackingCountry();

	// this function allows the attacking player to select the country they wish to attack, and sets the defending country and player accordingly
	// it returns false if there are no applicable defending countries adjacent to the attacking country
	int selectDefendingCountry(Map* map);

	// this function sets the number of dice for the player
	void decideNumDiceToRoll(bool allIn);

	// this function rolls a number of dice, and returns an array (of size numberOfDice) with the dice roll results
	void rollDice();

	// this function sorts an array of dice rolls, ordering them from highest roll to lowest roll
	void sortDice();

	void compareRolls();


public:

	// CONSTRUCTOR
	Battle(Player* attacker);
	~Battle();

	// SERVICE METHOD'

	// this function is the "battle driver", and goes through all steps of the battle phase (country selection, dice rolling, battle, etc)
	void doBattle(Map* map);

};


// this function is called from the game driver at the beginning of the battle phase, and initiates the battle
	void attackPhase(Player* attacker, Map* map);




#endif

