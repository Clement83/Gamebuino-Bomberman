#ifndef BOMBER_H
#define BOMBER_H

#include <SPI.h>
#include <Gamebuino.h>
#include <math.h>

#include "Bomb.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Maze.h"
Gamebuino gb;
class Bomber {
  public:
     Bomber(); 
   
    Maze maze;
    Bomb bomb1;
    Player playerx;
    Enemy enemy1;
    

    byte gameState;
    bool debug;
    const byte logo[];
    
    void setup();
    void loop();
    void deadMenu();
    void debugRender();
    void renderGame();
    void handleInput();
};
#endif
