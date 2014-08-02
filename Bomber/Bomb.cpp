#include "Bomb.h"
#define BOMB_MAX 3

extern Bomb bombs[];

void bombsInit() {
   for (int i = 0; i < BOMB_MAX; i++ ) {
     bombs[i].active = false;    
   }
}


