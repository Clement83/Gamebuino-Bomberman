#ifndef BOMB_H
#define BOMB_H
#include <Arduino.h>

class Bomb {
  
  public:
    byte x;
    byte y;
    boolean active;
    unsigned long startTime;
    
    void render();
};

#endif


