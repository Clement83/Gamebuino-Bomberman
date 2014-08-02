#ifndef ENTITY_H
#define ENTITY_H

#include <Arduino.h>
#include <Gamebuino.h>
#include "Maze.h"

class Entity {
  public:
   Entity();
   void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    byte getDistance(byte x1, byte y1, byte x2,byte y2);
    void entitySpawn();
    boolean active;
    byte x;
    byte y;
    byte h;
    byte w;
    byte vy;
    byte vx;
};

#endif

