#ifndef STRAT_H
#define STRAT_H

#include <iostream>
#include "../Player/Player.h"
#include "../Map/Country.h"
#include <stdlib.h>

class Map;

using namespace std;

class Strategy
 {
 public:
     Strategy();

     virtual bool decideAttack(Player* p, Map* map) = 0;

     Country* getAttackingCountry();
     Country* getDefendingCountry();

     void setAttackingCountry(Country* c);
     void setDefendingCountry(Country* c);

 private:
    Country* attackingCountry;
    Country* defendingCountry;
     
 }; 



#endif