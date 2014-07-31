#ifndef BOMB_H
#define BOMB_H
#include <Arduino.h>
#define BOMB_MAX 3

class Bomb {
  
  public:
    void initBombs();
    void setBomb(byte x,byte y);
    void renderBombs();
    void updateBombs();
    
    byte x;
    byte y;
    boolean active;
    unsigned long startTime;
};

#endif


