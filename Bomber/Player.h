#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

#include <Arduino.h>
#include <Gamebuino.h>

class Player : public Entity {
  public:
   Player();
   void entitySpawn();
   void doDamage(byte val);
   void setDead();
   void renderPlayer();
   byte playervxStart;
  byte playervyStart;
  byte deaths;
  byte kills;
  byte health;
};

#endif;

