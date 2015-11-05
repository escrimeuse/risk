/* 
Assignment #1
COMP 345 - Prof: Joey Paquet - Section D DI
Author: Cathryn Griffiths (ID#29108777) 

DESCRIPTION OF PROGRAM: 
This program is designed to satisfy Part 3 of Assignment #1. It implements a group of C++ class simulating a battle from the game Risk. 

*/
#include "Player.h"
#include "Country.h"
#include "Battle.h"
#include <iostream>
#include <time.h>	// required for initialising the seed for generating random numbers

using namespace std;

int main() {

	srand(time(NULL));	// this is for initializing the seed for generating random numbers for the dice rolls

	// Set up players and countries
	// NOTE: Player and country information has been hard-coded for demonstrative purposes of this assignent. 

	Player player1 = Player("Rick");
	Player player2 = Player("Morty");

	Country canada = Country("Canada", 10, &player1);
	Country us = Country("US", 11, &player1);
	Country england = Country("England", 12, &player1);
	Country mexico = Country("Mexico", 13, &player2);
	Country russia = Country("Russia", 14, &player2);

	const int NUM_ADJ_CANADA = 2;
	Country *adjCanada[NUM_ADJ_CANADA] = { &us,&england };
	canada.setAdjacencies(adjCanada, NUM_ADJ_CANADA);
	canada.setNumOfArmies(1);

	const int NUM_ADJ_US = 3;
	Country *adjUS[NUM_ADJ_US] = { &mexico, &england, &canada };
	us.setAdjacencies(adjUS, NUM_ADJ_US);
	us.setNumOfArmies(10);

	const int NUM_ADJ_ENGLAND = 4;
	Country *adjEngland[NUM_ADJ_ENGLAND] = { &canada, &us, &mexico, &russia };
	england.setAdjacencies(adjEngland, NUM_ADJ_ENGLAND);
	england.setNumOfArmies(2);

	const int NUM_ADJ_MEXICO = 2;
	Country *adjMexico[NUM_ADJ_MEXICO] = { &us, &england };
	mexico.setAdjacencies(adjMexico, NUM_ADJ_MEXICO);
	mexico.setNumOfArmies(4);

	const int NUM_ADJ_RUSSIA = 1;
	Country *adjRussia[NUM_ADJ_RUSSIA] = { &england };
	russia.setAdjacencies(adjRussia, NUM_ADJ_RUSSIA);
	russia.setNumOfArmies(10);

	Country *player1Countries[3] = { &us,&canada,&england };
	Country *player2Countries[2] = { &mexico,&russia };

	player1.setOwnedCountries(player1Countries);
	player2.setOwnedCountries(player2Countries);
	player1.setNumOwnedCountries(3);
	player2.setNumOwnedCountries(2);

	// Demonstrate an attack, with player1 (Rick) as the attacker
	attackPhase(&player1);




}