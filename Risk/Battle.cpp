#include "Battle.h"
#include <iostream>
#include <time.h>

using std::cout;
using std::cin;
using std::endl;


// Constructor

Battle::Battle(Player* theAttacker): attacker(theAttacker) {

	// all fields other than attacker are initialized to NULL automatically

};


// Mutator methods

void Battle::setAttacker(Player& theAttacker) {
	attacker = &theAttacker;
};

void Battle::setDefender(Player& theDefender) {
	defender = &theDefender;
};

void Battle::setAttackingCountry(Country& theCountry) {
	attackingCountry = &theCountry;
};

void Battle::setDefendingCountry(Country& theCountry) {
	defendingCountry = &theCountry;
};

void Battle::setAttackerNumArmies(int num) {
	attackerNumOfArmies = num;
};

void Battle::setDefenderNumArmies(int num) {
	defenderNumOfArmies = num;

};

void Battle::setAttackerNumDice(int num) {
	
	attackerNumOfDice = num;

};

void Battle::setDefenderNumDice(int num) {
	defenderNumOfDice = num;
};

void Battle::setAttackerDice(int* dice) {

	attackerDice = dice;

};

void Battle::setDefenderDice(int* dice) {

	defenderDice = dice;

};


// Accessor methods

Player* Battle::getAttacker() {
	return attacker;
};

Player* Battle::getDefender() {
	return defender;
};

Country* Battle::getAttackingCountry() {
	return attackingCountry;
};

Country* Battle::getDefendingCountry() {
	return defendingCountry;
};

int Battle::getAttackerNumArmies() {
	return attackerNumOfArmies;
};

int Battle::getDefenderNumArmies() {
	return defenderNumOfArmies;
};

int Battle::getAttackerNumDice() {
	return attackerNumOfDice;
};

int Battle::getDefenderNumDice() {
	return defenderNumOfDice;
};

int* Battle::getAttackerDice() {
	return attackerDice;
};

int* Battle::getDefenderDice() {
	return defenderDice;
};


// Service methods

void Battle::selectAttackingCountry() {

	

	// get all necessary data for asking about countries 
	Country** countries = attacker->getOwnedCountries();		
	int numCountriesOwned = attacker->getNumOfOwnedCountries();
	int selection = NULL;	// this will store the ID of the country selected by the player
	int* validIDs = new int[numCountriesOwned];		// this will store the array of VALID country IDs of countries that the player can select
	int numValidIDs=0;	
	
	// display to screen the countries they can attack with 
	// NOTE: as per Risk rules, the country they attack with must have AT LEAST 2 armies on it
	cout << "ID\tName\t\t# of Armies" << endl;
	cout << "-------------------------------------" << endl;
	for (int i = 0; i != numCountriesOwned; i++) {
		if (countries[i]->getNumOfArmies()>=2) {
			cout << countries[i]->getID() << "\t" << countries[i]->getName() << "\t\t" <<
				countries[i]->getNumOfArmies() << endl;
			validIDs[numValidIDs]=countries[i]->getID();
			numValidIDs++;
		}
	}

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
	for (int i = 0; i != numCountriesOwned; i++) {
		if (countries[i]->getID() == selection) {
			setAttackingCountry(*(countries[i]));
			break;
		}
	}

	delete[] validIDs;
	validIDs = NULL;


};

void Battle::selectDefendingCountry() {

	

	// get all the data necessary for making a selection of the defending country
	Country** countries = attackingCountry->getAdjacencies();
	int numCountriesAdj = attackingCountry->getNumOfAdjacencies();
	int selection = NULL;	// this will store the ID of the selected country to defend
	int* validIDs = new int[numCountriesAdj];
	int numValidIDs = 0;

	
	cout << endl;
	cout << "ID\tName\t\t# of Armies\tOwner" << endl;
	cout << "------------------------------------------------------" << endl;

	for (int i = 0; i != numCountriesAdj; i++) {

		if ((countries[i]->getOwner())->getName() != attacker->getName()) {
			cout << countries[i]->getID();
			cout << "\t";
			cout << countries[i]->getName();
			cout << "\t\t";
			cout << countries[i]->getNumOfArmies();
			cout << "\t\t";
			cout << (countries[i]->getOwner())->getName();
			cout << endl;
			validIDs[numValidIDs] = countries[i]->getID();
			numValidIDs++;
		}
		
	}

	cout << endl;
	cout << "Please enter the ID number of the country you would like to attack: ";
	cin >> selection;
	bool validSelection = false;
	while (!validSelection) {

		for (int i = 0; i != numCountriesAdj; i++) {
			if (countries[i]->getID() == selection) {
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
	for (int i = 0; i != numCountriesAdj; i++) {
		if (countries[i]->getID() == selection) {
			setDefendingCountry(*(countries[i]));
			setDefender(*countries[i]->getOwner());
			break;
		}
	}

	delete[] validIDs;
	validIDs = NULL;

	

};

void Battle::determineAndSetAttackerNumDice() {
	// RULES FOR ATTACKER DICE: Attacker can role 1, 2, or 3 dice. The attacker must have AT LEAST one more
	// army in their country than the number of dice rolled.
	if (attackerNumOfArmies == 2) {
		cout << attacker->getName() << " will roll 1 dice" << endl;
		setAttackerNumDice(1);
	}
	else if (attackerNumOfArmies == 3) {
		cout << attacker->getName() << ", you can roll either 1 or 2 dice. How many would you like to roll? ";
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
		setAttackerNumDice(numToRoll);
	}
	else if (attackerNumOfArmies > 3) {
		cout << attacker->getName() << ", you can roll either 1, 2, or 3 dice. How many would you like to roll? ";
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
		setAttackerNumDice(numToRoll);
	}
	
};

void Battle::determineAndSetDefenderNumDice() {

	// RULES FOR DEFENDER DICE: Defender can roll 1 or 2 dice. To roll 2 dice, the defender must have at least 2 armies in their country
	if (defenderNumOfArmies == 1 || defenderNumOfArmies == 2) {
		cout << defender->getName() << ", you will roll 1 die" << endl;
		setDefenderNumDice(1);
	}
	else if (defenderNumOfArmies > 2) {
		cout << defender->getName() << ", you can roll either 1 or 2 dice. How many would you like to roll? ";
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
		setDefenderNumDice(numToRoll);
	}
};

int* Battle::rollDice(int numOfDice) {

	int* diceArray = new int[numOfDice];

	for (int i = 0; i != numOfDice; i++) {
		diceArray[i] = (rand() % 6) + 1;
	}


	return diceArray;

};

void Battle::sortDice(int* dice, int numOfDice) {

	if (numOfDice == 1)
		return;
	else {
		// sort from highest to lowest roll
		for (int i = 1; i < numOfDice; i++) {
			int j = i;
			while (j > 0 && dice[j - 1] < dice[j]) {
				int temp = dice[j];
				dice[j] = dice[j - 1];
				dice[j - 1] = temp;
				j--;
			}
		}

	}
		

};

void Battle::doBattle() {

	cout << endl;
	cout << "*************" << endl;
	cout << "BATTLE BEGINS" << endl;
	cout << "*************" << endl << endl;

	// Step 1:
	// Select the attacking and defending countries
	// =========================================================================================================
	cout << endl;
	cout << "*******************************************" << endl;
	cout << "SELECT ONE OF YOUR COUNTRIES TO ATTACK WITH" << endl;
	cout << "*******************************************" << endl << endl;
	
	selectAttackingCountry();

	cout << endl;
	cout << "*******************************************" << endl;
	cout << "SELECT THE COUNTRY YOU WANT TO ATTACK      " << endl;
	cout << "*******************************************" << endl << endl;

	selectDefendingCountry();

	// Step 2:
	// Read the number of armies stationed in the attacking and defending countries, and set the attacker and
	// defender number of armies as appropriate
	// ==========================================================================================================
	setAttackerNumArmies(attackingCountry->getNumOfArmies());
	setDefenderNumArmies(defendingCountry->getNumOfArmies());

	// Step 3:
	// Perform the battle!
	// ==========================================================================================================
	bool continueAttack = true;
	while (continueAttack) {

		// Step 3a: 
		// Dice rolling!
		// ========================================================================================================

		cout << endl;
		cout << "*******************************************" << endl;
		cout << "ROLL DICE                                  " << endl;
		cout << "*******************************************" << endl << endl;
		
		// First, determine the number of dice to be rolled by each player and set the number of dice for each player
		determineAndSetAttackerNumDice();
		determineAndSetDefenderNumDice();

		srand(time(NULL));	// this is for initializing the seed for generating random numbers for the dice rolls

		// Attacker and defender roll their dice
		setAttackerDice(rollDice(attackerNumOfDice));
		setDefenderDice(rollDice(defenderNumOfDice));

		// Output results of dice roll to screen
		cout << attacker->getName() << ", you rolled: ";
		for (int i = 0; i < attackerNumOfDice; i++)
			cout << attackerDice[i] << ' ';
		cout << endl;
		cout << defender->getName() << ", you rolled: ";
		for (int i = 0; i < defenderNumOfDice; i++)
			cout << defenderDice[i] << ' ';
		cout << endl;

		// Step 3b:
		// Compare the dice rolls: 
		// ===========================================================================================================

		cout << endl;
		cout << "*******************************************" << endl;
		cout << "BATTLE RESULTS                             " << endl;
		cout << "*******************************************" << endl << endl;

		// sort the dice from highest to lowest
		sortDice(attackerDice, attackerNumOfDice);	
		sortDice(defenderDice, defenderNumOfDice);

		// determine how many dice we will be comparing
		int min;
		if (attackerNumOfDice <= defenderNumOfDice) {
			min = attackerNumOfDice;
		}
		else if (attackerNumOfDice > defenderNumOfDice) {
			min = defenderNumOfDice;
		}

		// compare the dice rolls, from highest to lowest roll
		for (int i = 0; i < min; i++) {

			if (attackerDice[i] > defenderDice[i]) { 
				// attacker has the highest roll, so the defender loses 1 army
				cout << defender->getName() << ", you lose 1 army!" << endl;
				defenderNumOfArmies--;

				// check if the defender still has armies left
				// if there are no armies left, then the attacker has conquered the country
				if (defenderNumOfArmies == 0) {
					cout << "No more armies on defending country!" << endl;
					defendingCountryCaptured = true; 
					continueAttack = false;
					break;
				}

			} else if (attackerDice[i] <= defenderDice[i]) { 
				// defender has the highest roll, or there is a tie, so the attacker loses 1 army
				cout << attacker->getName() << ", you lose 1 army!" << endl;
				attackerNumOfArmies--;

				// check how many armies the attacker has left. If they have only 1 army left, then the battle
				// must stop (as the attacker must always leave behind 1 army on the attacking country)
				if (attackerNumOfArmies == 1) {
					cout << "No more armies on attacking country!" << endl;
					attackingCountryStop = true;
					continueAttack = false;
					break;
				}
			}
		}

		if (continueAttack) {
			// if continueAttack is true, then that means that the defending country was not captured and the attacking
			// country still has more than 1 army left on it. We will ask the attacker if they would like to continue attacking
			// this country.
			char continueYN; 
			cout << endl << attacker->getName() << ", would you like to continue attacking " << defendingCountry->getName() << "? ";
			cin >> continueYN; 
			if (continueYN == 'y')
				continueAttack = true;
			else
				continueAttack = false;
		}
	}

	// Step 4:
	// Post-battle actions: update the number of armies on the attacking and defending country, and change the owner of
	// the defeated country if applicable.
	//=====================================================================================================================
	if (defendingCountryCaptured) {

		defendingCountry->setOwner(attacker); // change the owner of the country to the attacker

		cout << "Congratulations " << attacker->getName() << ", you defeated " << defendingCountry->getName() << "!" << endl;
		
		// Migrate armies onto the defending country from the attacking country
		if (attackerNumOfArmies == 2) {
			// the if the attacking country has only 2 armies left on it, then 1 army must stay behind on the attacking country,
			// and 1 army must be placed on the defending country.
			defendingCountry->setNumOfArmies(1);
			attackingCountry->setNumOfArmies(1);
		}
		else {
			// if there are more than 2 armies, then we can ask the attacker how many armies they would like to place on the 
			// defeated country. The number of armies placed on the defeated country must be greater than or equal to the number
			// of armies used on the roll that defeated the country
			int maxNumArmiesToPlace = attackerNumOfArmies - 1;
			int minNumArmiesToPlace = getAttackerNumDice(); 
			int numArmiesToPlace;
			cout << "You can place " << minNumArmiesToPlace << " to " << maxNumArmiesToPlace << " on your new country. How many armies would you like to place? ";
			cin >> numArmiesToPlace; 

			// check the validity of the number of armies to place
			bool validNumArmies;
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
			defendingCountry->setNumOfArmies(numArmiesToPlace);

			// change the number of armies on the attacking country as appropriate
			attackingCountry->setNumOfArmies(attackerNumOfArmies - numArmiesToPlace);
		}
	}
	else {
		// if the defending country wasn't captured, or if the attacker stopped attacking (by choice or because they
		// don't have enough armies left), then update the number of armies on both the attacking and defeated countries
		defendingCountry->setNumOfArmies(defenderNumOfArmies);
		attackingCountry->setNumOfArmies(attackerNumOfArmies);
	}

	cout << endl;
	cout << "*************" << endl;
	cout << " BATTLE ENDS " << endl;
	cout << "*************" << endl << endl;

	
};

void attackPhase(Player* player) {

	char wantsToAttack;
	bool attack;
	cout << player->getName() << ", would you like to attack? ";
	cin >> wantsToAttack; 

	if (wantsToAttack == 'Y' || wantsToAttack == 'y')
		attack = true;
	else
		attack = false; 

	while (attack) {
		Battle* battle = new Battle(player); 
		battle->doBattle(); 

		cout << player->getName() << ", would you like to attack again? ";
		cin >> wantsToAttack;

		if (wantsToAttack == 'Y' || wantsToAttack == 'y')
			attack = true;
		else
			attack = false;
	}
	
};