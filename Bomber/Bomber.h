#ifndef BOMBER_H
#define BOMBER_H

#include <Arduino.h>
#include <Gamebuino.h>
#include <SPI.h>
#include <math.h>

#include "Entity.h"
#include "Bomb.h"
#include "Player.h"
#include "Enemy.h"
#include "Maze.h"

class Bomber {
  public:
     Bomber(); 
     Gamebuino gb;
   
    Maze maze;
    Bomb bomb1;
    Player player;
    Enemy enemy;
    

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
