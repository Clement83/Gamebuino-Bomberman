#include "Bomb.h"
#define BOMB_MAX 3
#include <Gamebuino.h>
extern Gamebuino gb;
extern Bomb bombs[];

void bombsInit() {
   for (int i = 0; i < BOMB_MAX; i++ ) {
     bombs[i].active = false;    
   }
}

void Bomb::render() {
  if (gb.frameCount % 25) {
        gb.display.fillRect(x+1,y, 2,1); // top  
        gb.display.fillRect(x,y+1,1,2); // left  
        gb.display.fillRect(x+1,y+3, 2,1); // bottom
        gb.display.fillRect(x+3,y+1, 1,2); // right
      }
}


