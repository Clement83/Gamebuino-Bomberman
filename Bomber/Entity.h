#ifndef ENTITY_H
#define ENTITY_H
#include "Maze.h"

class Entity {
  public:
   Entity();
   void moveLeft(Entity *e);
    void moveRight(Entity *e);
    void moveUp(Entity *e);
    void moveDown(Entity *e);
    void entitySpawn(Entity *e);
    boolean active;
    byte x;
    byte y;
    byte h;
    byte w;
    byte vy;
    byte vx;
};

#endif
