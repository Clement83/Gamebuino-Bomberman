#ifndef BOMB_H
#define BOMB_H

#include <Arduino.h>
#include <Gamebuino.h>
#define BOMB_MAX 3

class Bomb {
  
  public:
    void initBombs();
    void setBomb(byte x,byte y);
    //void renderBombs(Gamebuino *gb);
    void updateBombs();
    
    byte x;
    byte y;
    bool active;
    unsigned long startTime;
};

#endif

