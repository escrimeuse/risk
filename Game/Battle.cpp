#include "Battle.h"
#include <iostream>


using std::cout;
using std::cin;
using std::endl;


// Constructor

Battle::Battle(Player* theAttacker) {

	attacker.player = theAttacker;
	attacker.isComputer = theAttacker->isComputer();
	// all fields other than player are initialized to NULL automatically

};

// Service methods

int Battle::selectAttackingCountry() {

	// get all necessary data for asking about countries 
	list<Country*> *countries = attacker.player->getOwnedCountries();		
	int numCountriesOwned = (attacker.player)->getNumOfOwnedCountries();
	int selection;	// this will store the ID of the country selected by the player
	int* validIDs = new int[numCountriesOwned];		// this will store the array of VALID country IDs of countries that the player can select
	int numValidIDs=0;	
	
	// display to screen the countries they can attack with 
	// NOTE: as per Risk rules, the country they attack with must have AT LEAST 2 armies on it.
	// NOTE: Country should also be adjacent to at least 1 country that is not owned by the attacking player

	cout << endl;
	cout << "ID\tName\t\t# of Armies" << endl;
	cout << "-------------------------------------" << endl;
	for (list<Country*>::iterator i = countries->begin(); i != countries->end(); ++i) {

		if ((*i)->getArmies()>=2) {

				cout << (*i)->getId() << "\t" << (*i)->getName() << "\t\t" <<
					(*i)->getArmies() << endl;
				validIDs[numValidIDs] = (*i)->getId();
				numValidIDs++;
			
			
		}
	}

	if (numValidIDs == 0) {
		// then there are no countries meeting the above criteria for attacking
		return 1;
	}
	else {
		// get selected country ID from the player, and validate it against the list of valid IDs
		cout << endl;
		cout << "Please enter the ID number of the country you would like to attack with: ";
		cin >> selection;
		bool validSelection = false;
		while (!validSelection) {	// continue asking until a valid ID is selected
			for (int i = 0; i != numValidIDs; i++) {
				if (selection == validIDs[i])
					validSelection = true;
			}
			if (!validSelection) {
				cout << "INVALID COUNTRY ID ENTERED: Please enter the ID again: ";
				cin >> selection;
			}
		}

		// set the attacking country equal to the country with the selected ID
		for (list<Country*>::iterator i = countries->begin(); i != countries->end(); ++i) {
			if ((*i)->getId() == selection) {
				attacker.country = (*i);
				break;
			}
		}

		// cleanup heap
		delete[] validIDs;
		validIDs = NULL;

		return 0;
	}
	

};

int Battle::selectDefendingCountry(Map* map) {

	// get all the data necessary for making a selection of the defending country
	vector<Country*> enemies = map->getEnemyCountries(attacker.country);
	int selection;	// this will store the ID of the selected country to defend
	int* validIDs = new int[enemies.size()];
	int numValidIDs = 0;

	// display all adjacent countries owned by players other than the attacker
	cout << endl;
	cout << "ID\tName\t\t# of Armies\tOwner" << endl;
	cout << "------------------------------------------------------" << endl;

	for (int i = 0; i != enemies.size(); i++) {

		if ((enemies[i]->getOwner())->getName() != (attacker.player)->getName()) {
			cout << enemies[i]->getId();
			cout << "\t";
			cout << enemies[i]->getName();
			cout << "\t\t";
			cout << enemies[i]->getArmies();
			cout << "\t\t";
			cout << (enemies[i]->getOwner())->getName();
			cout << endl;
			validIDs[numValidIDs] = enemies[i]->getId();
			numValidIDs++;
		}
		
	}

	if (numValidIDs == 0) {
		// then there were no countries meeting the above criteria to attack
		return 1;
	}
	else {
		cout << endl;
		cout << "Please enter the ID number of the country you would like to attack: ";
		cin >> selection;
		bool validSelection = false;
		while (!validSelection) {

			for (int i = 0; i != enemies.size(); i++) {
				if (validIDs[i] == selection) {
					validSelection = true;
					break;
				}

			}
			if (!validSelection) {
				cout << "INVALID COUNTRY ID ENTERED: Please enter the ID again: ";
				cin >> selection;
			}

		}

		// set the defending country equal to the country with the selected ID
		for (int i = 0; i != enemies.size(); i++) {
			if (enemies[i]->getId() == selection) {
				defender.player = enemies[i]->getOwner();
				defender.country = enemies[i];
				break;
			}
		}

		// cleanup heap
		delete[] validIDs;
		validIDs = NULL;

		return 0;
	}

	
	

};

void Battle::decideNumDiceToRoll(bool allIn) {

	
	// RULES FOR ATTACKER DICE: Attacker can role 1, 2, or 3 dice. The attacker must have AT LEAST one more
	// army in their country than the number of dice rolled.
	if ((attacker.country)->getArmies() == 2) {
		cout << endl << (attacker.player)->getName() << " will roll 1 dice" << endl;
		attacker.numOfDice = 1;
	}
	else if ((attacker.country)->getArmies() == 3) {

		if (allIn) {
			cout << endl << (attacker.player)->getName() << " will roll 2 dice" << endl;
			attacker.numOfDice = 2;
		}
		else {
			cout << endl << (attacker.player)->getName() << ", you can roll either 1 or 2 dice. How many would you like to roll? ";
			int numToRoll;
			cin >> numToRoll;
			bool valid = false;
			if (numToRoll == 1 || numToRoll == 2) {
				valid = true;
			}
			while (!valid) {
				cout << "INVALID NUMBER OF DICE ENTERED: Please enter either 1 or 2: ";
				cin >> numToRoll;
				if (numToRoll == 1 || numToRoll == 2) {
					valid = true;
				}
			}
			attacker.numOfDice = numToRoll;
		}

	}
	else if ((attacker.country)->getArmies() > 3) {

		if (allIn) {
			cout << endl << (attacker.player)->getName() << " will roll 3 dice" << endl;
			attacker.numOfDice = 3;
		}
		else {
			cout << endl << (attacker.player)->getName() << ", you can roll either 1, 2, or 3 dice. How many would you like to roll? ";
			int numToRoll;
			cin >> numToRoll;
			bool valid = false;
			if (numToRoll == 1 || numToRoll == 2 || numToRoll == 3) {
				valid = true;
			}
			while (!valid) {
				cout << "INVALID NUMBER OF DICE ENTERED: Please enter either 1, 2, or 3: ";
				cin >> numToRoll;
				if (numToRoll == 1 || numToRoll == 2 || numToRoll == 3) {
					valid = true;
				}
			}
			attacker.numOfDice = numToRoll;
		}

	}

	



	// RULES FOR DEFENDER DICE: Defender can roll 1 or 2 dice. To roll 2 dice, the defender must have at least 2 armies in their country
	if ((defender.country)->getArmies() == 1 || (defender.country)->getArmies() == 2) {
		cout << endl << (defender.player)->getName() << ", you will roll 1 die" << endl;
		defender.numOfDice = 1;
	}
	else if ((defender.country)->getArmies() > 2) {

		if (allIn) {
			cout << endl << (defender.player)->getName() << ", you will roll 2 dice" << endl;
			defender.numOfDice = 2;
		}
		else {
			cout << endl << (defender.player)->getName() << ", you can roll either 1 or 2 dice. How many would you like to roll? ";
			int numToRoll;
			cin >> numToRoll;
			bool valid = false;
			if (numToRoll == 1 || numToRoll == 2) {
				valid = true;
			}
			while (!valid) {
				cout << "INVALID NUMBER OF DICE ENTERED: Please enter either 1 or 2: ";
				cin >> numToRoll;
				if (numToRoll == 1 || numToRoll == 2) {
					valid = true;
				}
			}
			defender.numOfDice = numToRoll;
		}

	}
	


}

void Battle::rollDice() {

	// for attacker
	for (int i = 0; i != attacker.numOfDice; i++) {
		attacker.dice[i] = (rand() % 6) + 1;
	}

	// for defender
	for (int i = 0; i != attacker.numOfDice; i++) {
		defender.dice[i] = (rand() % 6) + 1;
	}
};

void Battle::sortDice() {

	if (attacker.numOfDice == 1) {
		// do nothing
	}
	else {
		// sort from highest to lowest roll
		for (int i = 1; i < attacker.numOfDice; i++) {
			int j = i;
			while (j > 0 && attacker.dice[j - 1] < attacker.dice[j]) {
				int temp = attacker.dice[j];
				attacker.dice[j] = attacker.dice[j - 1];
				attacker.dice[j - 1] = temp;
				j--;
			}
		}

	}

	if (defender.numOfDice == 1) {
		// do nothing
	}
	else {
		// sort from highest to lowest roll
		for (int i = 1; i < defender.numOfDice; i++) {
			int j = i;
			while (j > 0 && defender.dice[j - 1] < defender.dice[j]) {
				int temp = defender.dice[j];
				defender.dice[j] = defender.dice[j - 1];
				defender.dice[j - 1] = temp;
				j--;
			}
		}

	}


		

};

void Battle::compareRolls() {

	// determine how many dice we will be comparing
	int numDiceToCompare;
	if (attacker.numOfDice <= defender.numOfDice) {
		numDiceToCompare = attacker.numOfDice;
	}
	else if (attacker.numOfDice > defender.numOfDice) {
		numDiceToCompare = defender.numOfDice;
	}

	// compare the dice rolls, from highest to lowest roll
	for (int i = 0; i < numDiceToCompare; i++) {

		if (attacker.dice[i] > defender.dice[i]) {
			// attacker has the highest roll, so the defender loses 1 army

			cout << endl << (defender.player)->getName() << ", you lose 1 army!" << endl;

			int numOfArmiesCurrentlyOnDefendingCountry = (defender.country)->getArmies() -1;
			defender.player->setArmiesInCountry(defender.country, numOfArmiesCurrentlyOnDefendingCountry);

			cout << (defender.country)->getName() << " now has " << (defender.country)->getArmies() << " armies." << endl;

		}
		else if (attacker.dice[i] <= defender.dice[i]) {
			// defender has the highest roll, or there is a tie, so the attacker loses 1 army

			cout << endl << (attacker.player)->getName() << ", you lose 1 army!" << endl;

			int numOfArmiesCurrentlyOnAttackingCountry = (attacker.country)->getArmies() -1;
			attacker.player->setArmiesInCountry(attacker.country, numOfArmiesCurrentlyOnAttackingCountry);
			cout << (attacker.country)->getName() << " now has " << (attacker.country)->getArmies() << " armies." << endl;

		}
	}
}

void Battle::doBattle(vector<Player*>& players, Map* map) {

	cout << endl;
	cout << "*************" << endl;
	cout << "BATTLE BEGINS" << endl;
	cout << "*************" << endl << endl;

	// Step 1:
	// Select the attacking country
	// =========================================================================================================
	cout << endl;
	cout << "*******************************************" << endl;
	cout << "SELECT ONE OF YOUR COUNTRIES TO ATTACK WITH" << endl;
	cout << "*******************************************" << endl << endl;
	if(!attacker.isComputer){
		if (selectAttackingCountry() == 1) {
			cout << "There are no countries that you can attack with!" << endl;
			return;
		}
	}else{
		attacker.country = (attacker.player)->getStrategy()->getAttackingCountry();
		cout << "Player will  attack with " << attacker.country->getName()  << endl;
	}

	// Step 2:
	// Select the defending country
	// =========================================================================================================
	cout << endl;
	cout << "*******************************************" << endl;
	cout << "SELECT THE COUNTRY YOU WANT TO ATTACK      " << endl;
	cout << "*******************************************" << endl << endl;
	if(!attacker.isComputer){
		if (selectDefendingCountry(map) == 1) {

			cout << "There are no countries that you can attack with that selected country!" << endl;
			return;

		}
	}else{
		defender.country = (attacker.player)->getStrategy()->getDefendingCountry();
		defender.player = defender.country->getOwner();
		cout << "Player will  attack " << defender.country->getName()  << endl;
	}



	// Step 3:
	// Perform the battle!
	// ==========================================================================================================
	cout << endl;
	cout << "*******************************************" << endl;
	cout << "FIGHT! FIGHT! FIGHT! FIGHT! FIGHT! FIGHT!  " << endl;
	cout << "*******************************************" << endl << endl;

	// determine if attacker wants to go "all in"
	bool allIn = false;
	if(!attacker.isComputer){
		char goAllIn;
		cout << (attacker.player)->getName() << ", do you want to go ALL IN? (Y or N?) ";
		cin >> goAllIn;
		if (goAllIn == 'y' || goAllIn == 'Y') {
			allIn = true;
		}
	}else{
		allIn = true;
	}

	

	bool continueFight = true;
	while (continueFight) {

		// decide the number of dice to roll
		if (allIn) {
			decideNumDiceToRoll(1);	// # dice to roll decided automatically
		}
		else {
			decideNumDiceToRoll(0); // # dice to roll decided by users
		}

		rollDice();
		sortDice();

		cout << endl << (attacker.player)->getName() << ", you rolled: ";
		for (int i = 0; i < attacker.numOfDice; i++) {
			cout << attacker.dice[i] << " ";
		}
		cout << endl;
		cout << (defender.player)->getName() << ", you rolled: ";
		for (int i = 0; i < defender.numOfDice; i++) {
			cout << defender.dice[i] << " ";
		}
		cout << endl;


		compareRolls();

		if ((defender.country)->getArmies() == 0) {

			// attacker has successfully defeated the country
			cout << "Congratulations " << (attacker.player)->getName() << "! You conquered " << (defender.country)->getName() << "!" << endl;
			continueFight = false;

			// change the ownership of the country
			(defender.country)->setOwner(attacker.player);

			// migrate armies from attacking country to defeated country
			if ((attacker.country)->getArmies() == 2) {
				// the if the attacking country has only 2 armies left on it, then 1 army must stay behind on the attacking country,
				// and 1 army must be placed on the defending country.
				defender.player->setArmiesInCountry((defender.country), 1);
				attacker.player->setArmiesInCountry((attacker.country), 1);
			}
			else {
				int maxNumArmiesToPlace = (attacker.country)->getArmies() - 1;
				int minNumArmiesToPlace = attacker.numOfDice;
				int numArmiesToPlace;

				if (allIn) {
					// if "all in" mode, then we move all armies (leaving one behind on the attacking country) to the defeated country
					defender.player->setArmiesInCountry((defender.country), maxNumArmiesToPlace);
					attacker.player->setArmiesInCountry((attacker.country), 1);

				}
				else {
					// if there are more than 2 armies, then we can ask the attacker how many armies they would like to place on the 
					// defeated country. The number of armies placed on the defeated country must be greater than or equal to the number
					// of armies used on the roll that defeated the country

					cout << "You can place " << minNumArmiesToPlace << " to " << maxNumArmiesToPlace << " armies on your new country. How many armies would you like to place? ";
					cin >> numArmiesToPlace;

					// check the validity of the number of armies to place
					bool validNumArmies = false;
					if (numArmiesToPlace <= maxNumArmiesToPlace && numArmiesToPlace >= minNumArmiesToPlace) {
						validNumArmies = true;
					}
					while (!validNumArmies) {
						cout << "INVALID NUMBER OF ARMIES. Please enter the number of armies you would like to place: ";
						cin >> numArmiesToPlace;
						if (numArmiesToPlace <= maxNumArmiesToPlace && numArmiesToPlace > minNumArmiesToPlace) {
							validNumArmies = true;
						}
					}
					// set the number of armies on the country that was defeated
					defender.player->setArmiesInCountry(defender.country, numArmiesToPlace);

					// change the number of armies on the attacking country as appropriate
					attacker.player->setArmiesInCountry(attacker.country, (attacker.country)->getArmies() - numArmiesToPlace);



				}

				// update attacker's ownedCountry array
				attacker.player->addOwnedCountry(defender.country);

				// update the defender's ownedCountry array
				(defender.player)->removeOwnedCountry(defender.country->getName());	
				if (defender.player->isAlive()) {
					for (int i = 0; i < players.size(); i++) {
						if (players[i] == defender.player) {
							players.erase(players.begin() + i);
							break;
						}
					}
					if (players.size() == 1) {
						victory(players.front());
					}
				}
			}


		}

		else if ((attacker.country)->getArmies() == 1) {
			// the attacker cannot continue fighting with this country
			cout << (attacker.player)->getName() << ", you cannot attack with " << (attacker.country)->getName() << " anymore." << endl;
			continueFight = false;
		}
		else if ((attacker.country)->getArmies() >1 && !allIn) {

			char userAnswer = ' ';
			cout << (attacker.player)->getName() << ", would you like to continue attacking " << (defender.country)->getName() << " with ";
			cout << (attacker.country)->getName() << "? (Enter Y or N) ";
			cin >> userAnswer;

			if (userAnswer == 'y')
				continueFight = true;
			else
				continueFight = false;



		}
	}
	

	cout << endl;
	cout << "*************" << endl;
	cout << " BATTLE ENDS " << endl;
	cout << "*************" << endl << endl;

	
};

void attackPhase(vector<Player*>& players, Player* player, Map* map) {

	// First, determine if the player has any countries with 2 or more armies stationed on them.
	// If the player does NOT have any such countries, then they cannot attack. 
	bool attack = true;
	while (attack) {

		bool canAttack = false;

		list<Country*> *playersCountries = player->getOwnedCountries();
		for (list<Country*>::iterator i = playersCountries->begin(); i != playersCountries->end(); ++i) {
			if ((*i)->getArmies() >= 2) {
				canAttack = true;
			}
		}

		if (canAttack) {
			char wantsToAttack;
			if(!player->isComputer()){
				cout << player->getName() << ", would you like to attack? (Please enter Y or N) ";
				cin >> wantsToAttack;

				if (wantsToAttack == 'Y' || wantsToAttack == 'y') {
					Battle* battle = new Battle(player);
					battle->doBattle(players, map);
					delete battle;
				}
				else {
					attack = false;
				}
			}else{
				cout << "Player is a Computer" << endl;
				if(player->getStrategy()->decideAttack(player, map)){
					Battle* battle = new Battle(player);
					battle->doBattle(players, map);
					delete battle;
				}else{
					attack = false;
				}
			}
		}
		else {
			cout << player->getName() << ", you have no countries with which to attack!" << endl;
			attack = false;
		}
	}
}

void Battle::victory(Player* player) {
	cout << "CONGRATULATIONS " << player->getName() << " YOU WON THE WAR" << endl;
}

Battle::~Battle(){
}

