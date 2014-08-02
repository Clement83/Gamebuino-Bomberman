#include "Entity.h"
#include "Maze.h"

#include "Player.h"
#include "Maze.h"
extern Gamebuino *gb;
extern Maze maze;

Entity::Entity() {
  
}

void Entity::entitySpawn() {
    byte randomX = random(1, 20);
    byte randomY = random(1, 12);
    
    if (maze.isTileEmpty(randomX, randomY)) {
         x = randomX * 4; 
         y = randomY * 4;
    } else
      entitySpawn();    
}

byte Entity::getDistance(byte x1, byte y1, byte x2,byte y2) {
  return floor((abs(sqrt(((x1 - x2) * (x1 - x2) ) + ( (y1 - y2) * (y1 - y2) ) ))));
}

void Entity::moveLeft() {
  x = max(0, x - vx );
   if (maze.checkWallCollision(x, y)) {
      x = max(0, x + vx );
   }
}

void Entity::moveRight() {
      x = min(LCDWIDTH - w, x + vx );
      if (maze.checkWallCollision(x, y)) {
        x = min(LCDWIDTH - w, x - vx );
     }
}

void Entity::moveUp() {
     y = max(0, y - vy );
     if (maze.checkWallCollision(x, y)) {
        y = max(0, y + vy );
     }
}

 void Entity::moveDown() {
     y = min(LCDHEIGHT - h, y + vy );
      if (maze.checkWallCollision(x, y)) {
       y = min(LCDHEIGHT - h, y - vy );
     }
}  

