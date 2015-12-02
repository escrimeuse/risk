#include "Random.h"
#include "../Map/Map.h"
#include <time.h>

using namespace std;

Random::Random() : Strategy(){}

bool Random::decideAttack(Player* p, Map* map){
    cout << "Random" << endl;
    srand (time(NULL));
    bool willAttack = rand()%2;
    if(willAttack){
        list<Country*> *playersCountries = p->getOwnedCountries();
		bool foundAttack = false;
		do {
			srand(time(NULL));
			Country* c = NULL;
			while (c == NULL) {
				if (p->getNumOfOwnedCountries() == 1)
					c = playersCountries->front();
				else {
					int attackingCountry = rand() % p->getNumOfOwnedCountries();

					for (list<Country*>::iterator it = playersCountries->begin(); it != playersCountries->end(); ++it) {
						if ((*it)->getId() == attackingCountry) {
							c = (*it);
							break;
						}

					}
				}
			}	
			if (c->getArmies() >= 2) {
				vector<Country*> enemies = map->getEnemyCountries(c);
				if (enemies.size() > 0) {
					int defendingCountry;
					do {
						srand(time(NULL));
						defendingCountry = rand() % enemies.size();
					} while (enemies[defendingCountry]->getOwner()->getName() == c->getOwner()->getName());
					//Set countries
					setAttackingCountry(c);
					setDefendingCountry(enemies[defendingCountry]);
					foundAttack = true;
				}
			}
			else if (p->getNumOfOwnedCountries() == 1)
				break;
        }while(!foundAttack);
        return foundAttack;
    }else{
        return false;
    }
}