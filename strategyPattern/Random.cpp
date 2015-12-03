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
		int i = 0;
		do {
			srand(time(NULL));
			Country* c = NULL;
			while (c == NULL) {
				if (p->getNumOfOwnedCountries() == 1)
					c = playersCountries->front();
				else {
					int attackingCountry = rand() % p->getNumOfOwnedCountries();
					for (list<Country*>::iterator it = playersCountries->begin(); it != playersCountries->end(); ++it) {
						if (i == attackingCountry) {
							c = (*it);
							break;
						}
						i++;
					}
					if (i >= 60000)
						return false;
				}
			}	
			if (c->getArmies() >= 2) {
				vector<Country*> enemies = map->getEnemyCountries(c);
				if (enemies.size() > 0) {
					int defendingCountry;
					int i = 0;
					do {
						srand(time(NULL));
						defendingCountry = rand() % enemies.size();
						if (i >= 30000)
							return false;
						i++;
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