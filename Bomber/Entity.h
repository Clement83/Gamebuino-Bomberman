#include "Maze.h"

typedef struct {
  boolean active;
  byte x;
  byte y;
  byte h;
  byte w;
  byte vy;
  byte vx;
} Entity;

void moveLeft(Entity *e) {
  e->x = max(0, e->x - e->vx );
   if (Maze::checkWallCollision(&e->x, &e->y, *gb)) {
      e->x = max(0, e->x + e->vx );
   }
}
void entitySpawn(Entity *e) {
    byte randomX = random(1, 20);
    byte randomY = random(1, 12);
    
    if (Maze::isTileEmpty(randomX, randomY)) {
         e->x = randomX * 4; 
         e->y = randomY * 4;
    } else
      entitySpawn(e);
    
}
void moveRight(Entity *e) {
      e->x = min(LCDWIDTH - e->w, e->x + e->vx );
      if (Maze::checkWallCollision(&e->x, &e->y, *gb)) {
        e->x = min(LCDWIDTH - e->w, e->x - e->vx );
     }
}

void moveUp(Entity *e) {
     e->y = max(0, e->y - e->vy );
     if (Maze::checkWallCollision(&e->x, &e->y,*gb)) {
        e->y = max(0, e->y + e->vy );
     }
}

 void moveDown(Entity *e) {
     e->y = min(LCDHEIGHT - e->h, e->y + e->vy );
      if (Maze::checkWallCollision(&e->x, &e->y,*gb)) {
       e->y = min(LCDHEIGHT - e->h, e->y - e->vy );
     }
}  
