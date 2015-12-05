#include "Defensive.h"
#include "../Map/Map.h"
#include <time.h>

using namespace std;

Defensive::Defensive() : Strategy(){}

bool Defensive::decideAttack(Player* p, Map* map){
	list<Country*>  *playersCountries = p->getOwnedCountries();
    bool willAttack = true;
	for (list<Country*>::iterator i = playersCountries->begin(); i != playersCountries->end(); ++i) {
            if ((*i)->getArmies() >= 2) {
                vector<Country*> enemies = map->getEnemyCountries((*i));
				if (enemies.size() == 0)
					willAttack = false;
                for (int j = 0; j != enemies.size(); j++) {
                    if((*i)->getOwner()->getName() != enemies[j]->getOwner()->getName()){
                        if((*i)->getArmies() < enemies[j]->getArmies()+2){
                            willAttack = false;
                        }
                    }
                }
                if(willAttack){
                    setAttackingCountry((*i));
                    int defendingCountryIndex;
                    do{
                        srand (time(NULL));
                        defendingCountryIndex = rand()% enemies.size();
                    }while(enemies[defendingCountryIndex]->getOwner()->getName() == (*i)->getOwner()->getName());
                    setDefendingCountry(enemies[defendingCountryIndex]);
                    break;
                }
            }
        }
        return willAttack;
}