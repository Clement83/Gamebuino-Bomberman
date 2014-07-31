#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

#include <Arduino.h>
#include <Gamebuino.h>

class Player : Entity {
  public:
   Player();
   void renderPlayer();
   byte playervxStart;
  byte playervyStart;
  byte playerDeaths;
  byte playerKills;
};




#endif;
