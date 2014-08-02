#include <math.h>
#include <Arduino.h>
class Bomber {
  public:
    Gamebuino gb;
    byte gameState;
    bool debug;
    
    void setup();
    void loop();
    void deadMenu();
    void debugRender();
    void renderGame();
    void handleInput();
};

#include "Entity.h"
#include "Bomb.h"
#include "Player.h"
#include "Enemy.h"
#include "Maze.h"
