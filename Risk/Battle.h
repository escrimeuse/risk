#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"
#include "Country.h"

class Battle {

private:
	
	// data members
	Player* attacker;
	Player* defender;
	Country* attackingCountry;
	Country* defendingCountry;
	int attackerNumOfArmies;
	int defenderNumOfArmies;
	int attackerNumOfDice;
	int defenderNumOfDice;
	int* attackerDice;	// points to a dynamic array of dice
	int* defenderDice;	// points to a dynamic array of dice
	bool defendingCountryCaptured;
	bool attackingCountryStop;


	// mutators
	void setAttacker(Player& theAttacker);
	void setDefender(Player& theDefender);
	void setAttackingCountry(Country& theCountry);
	void setDefendingCountry(Country& theCountry);
	void setAttackerNumArmies(int num);
	void setDefenderNumArmies(int num);
	void setAttackerNumDice(int num);
	void setDefenderNumDice(int num);
	void setAttackerDice(int* dice);
	void setDefenderDice(int* dice);

	// accessors
	Player* getAttacker();
	Player* getDefender();
	Country* getAttackingCountry();
	Country* getDefendingCountry();
	int getAttackerNumArmies();
	int getDefenderNumArmies();
	int getAttackerNumDice();
	int getDefenderNumDice();
	int* getAttackerDice();
	int* getDefenderDice();

	// service methods
	void selectAttackingCountry();
	void selectDefendingCountry();
	void determineAndSetAttackerNumDice();
	void determineAndSetDefenderNumDice();
	int* rollDice(int numberOfDice);
	void sortDice(int* dice, int numOfDice);


public:
	Battle(Player* attacker);
	void doBattle();	// attacker and defender will roll dice, rolls will be compared, until battle is over



};

void attackPhase(Player* attacker);


#endif

