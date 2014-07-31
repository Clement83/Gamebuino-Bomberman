#include "Entity.h"

void Entity::entitySpawn(Entity *e) {
    byte randomX = random(1, 20);
    byte randomY = random(1, 12);
    
    if (Maze::isTileEmpty(randomX, randomY)) {
         e->x = randomX * 4; 
         e->y = randomY * 4;
    } else
      entitySpawn(e);
    
}
void Entity::moveLeft(Entity *e) {
  e->x = max(0, e->x - e->vx );
   if (Maze::checkWallCollision(&e->x, &e->y, *gb)) {
      e->x = max(0, e->x + e->vx );
   }
}

void Entity::moveRight(Entity *e) {
      e->x = min(LCDWIDTH - e->w, e->x + e->vx );
      if (Maze::checkWallCollision(&e->x, &e->y, *gb)) {
        e->x = min(LCDWIDTH - e->w, e->x - e->vx );
     }
}

void Entity::moveUp(Entity *e) {
     e->y = max(0, e->y - e->vy );
     if (Maze::checkWallCollision(&e->x, &e->y,*gb)) {
        e->y = max(0, e->y + e->vy );
     }
}

 void Entity::moveDown(Entity *e) {
     e->y = min(LCDHEIGHT - e->h, e->y + e->vy );
      if (Maze::checkWallCollision(&e->x, &e->y,*gb)) {
       e->y = min(LCDHEIGHT - e->h, e->y - e->vy );
     }
}  
