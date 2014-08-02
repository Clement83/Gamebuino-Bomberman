#include "Maze.h"
#include "Player.h"
#include "Enemy.h"

#include <Arduino.h>

extern Gamebuino gb;
extern Player player;
extern Enemy enemy;
extern byte gameState;

#define wall_size_x 4
#define wall_size_y 4
#define maze_w 21
#define maze_h 12

byte mazeLevel[maze_h][maze_w] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,1},
{1,0,0,1,0,0,1,0,0,2,2,0,0,1,0,0,1,0,0,1},
{1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,1},
{1,0,0,1,0,0,1,0,0,2,2,0,0,1,0,0,1,0,0,1},
{1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

    
void Maze::renderEdges () {
  gb.display.fillRect(0, 0, LCDWIDTH-4, 4); // Top
  gb.display.fillRect(0, LCDHEIGHT-4, LCDWIDTH-4, LCDHEIGHT-1); // Bottom  
  gb.display.fillRect(0, 1, 4, LCDHEIGHT-1); // Left
  gb.display.fillRect(LCDWIDTH-8, 0, 4, LCDHEIGHT-1); // Right
}

boolean Maze::isTileEmpty(byte x, byte y) {
  if (mazeLevel[y][x] == 0)
    return true;
  else 
    return false;
}

void Maze::renderMaze() {
    for(byte row = 0; row < maze_h; row++) {
    for(byte col = 0; col < maze_w; col++) {
      if (mazeLevel[row][col] == 1) {
        gb.display.fillRect(col*4,row*4,4,4); 
      } else if (mazeLevel[row][col] == 2 ) {
        gb.display.drawRect(col*4,row*4,4,4);         
      }
    }
  }
}

boolean Maze::checkWallCollision(byte xIn, byte yIn) {
  // Get elements around player
  int tileX = toTileX(xIn) - 2;
  int tileY = toTileY(yIn) - 2;
  int tileXMax = tileX + 4;
  int tileYMax = tileY + 4;
  
  if (tileX < 0) tileX = 0;
  if (tileY < 0) tileY = 0;
  
  if (tileXMax > maze_w) tileXMax = maze_w;
  if (tileYMax > maze_h) tileYMax = maze_h; 
 
  for (byte row = tileY; row < tileYMax; row++) {
    if (row > maze_h || row < 0) continue;
    for (byte col = tileX; col < tileXMax; col++) {
      if (col > maze_w || col < 0) continue;
      if (mazeLevel[row][col] == 0 ) continue; // If empty skip
 
      if (gb.collideRectRect(xIn, yIn, player.w, player.h, col*wall_size_x, row*wall_size_y, wall_size_x, wall_size_y)) {
          Serial.print("Collision - Col:");
          Serial.print(col);
          Serial.print(" Row:");
          Serial.println(row);
          return true;
      }
    }
  }
  return false;
}

void Maze::bombExplode(byte x, byte y) {
  Serial.println("Explode:");
   byte tileX = toTileX(x);
   byte tileY = toTileY(y);
   
   byte tilePlayerX = toTileX(player.x);
   byte tilePlayerY = toTileY(player.y);
   
   Serial.print("Bomb X:");
   Serial.print(tileX);
   Serial.print(" Y:" );
   Serial.println(tileY);
   
   gb.sound.playOK();
      
   // Check plyer dead
   if ((tilePlayerX==tileX+1 && tilePlayerY==tileY)
   || (tilePlayerX==tileX-1 && tilePlayerY==tileY)
   || (tilePlayerX==tileX && tilePlayerY==tileY-1)
   || (tilePlayerX==tileX && tilePlayerY==tileY+1)
   || (tilePlayerX==tileX && tilePlayerY==tileY)) {
       playerDead();
       return;
  }
  
   byte tileEnemyX = toTileX(enemy.x);
   byte tileEnemyY = toTileY(enemy.y);
  
  if ((tileEnemyX==tileX+1 && tileEnemyY==tileY)
   || (tileEnemyX==tileX-1 && tileEnemyY==tileY)
   || (tileEnemyX==tileX && tileEnemyY==tileY-1)
   || (tileEnemyX==tileX && tileEnemyY==tileY+1)
   || (tileEnemyX==tileX && tileEnemyY==tileY)) {
       enemyDead();
       return;
  }
   
   // Check Right
   if (isBreakable(tileY, tileX+1)) {
     Serial.println("Breakable Right");
      mazeLevel[tileY][tileX+1] = 0;     
      gb.sound.playTick();
   }   
   
   // Check left
   if (isBreakable(tileY, tileX-1) ) {
     Serial.println("Breakable Left");
      mazeLevel[tileY][tileX-1] = 0;     
      gb.sound.playTick();
   }   
   
   // Check Up
   if (isBreakable(tileY-1, tileX) ) {
     Serial.println("Breakable Up");
      mazeLevel[tileY-1][tileX] = 0;     
      gb.sound.playTick();
   } 
  
   // Check Down
   if (isBreakable(tileY+1, tileX) ) {
     Serial.println("Breakable Down");
      mazeLevel[tileY+1][tileX] = 0;    
     gb.sound.playTick() ;
   }  
}

void Maze::playerDead() {  
  gb.sound.playCancel();
  gameState = 1;
  player.deaths++;
}

void Maze::enemyDead() {
  gb.sound.playCancel();
  player.kills++;
  enemy.entitySpawn();
}
byte Maze::toTileX(byte x) {
   return round(x / wall_size_x); 
}

byte Maze::toTileY(byte y) {
   return round(y / wall_size_y); 
}

boolean Maze::isBreakable(byte y, byte x) {  
  // TODO: check bounds

  switch(mazeLevel[y][x]) {
     case 0:
        return false;
        break;
    case 1:
        return false;
        break;
    case 2: 
        return true;
        break;
  }
}

