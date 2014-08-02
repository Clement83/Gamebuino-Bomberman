#ifndef ENEMY_H
#define ENEMY_H

#include <Arduino.h>
#include <Gamebuino.h>

#include "Entity.h"

class Enemy : public Entity {
  public:  
    Enemy();
    byte dist;
    byte enemyMode;
    void initEnemy();
    void renderEnemy();
    void updateEnemy();
};

const byte enemySprite[] PROGMEM = {
  4, 4,
  B01100000,
  B11110000,
  B11110000,
  B01100000
};

#endif



