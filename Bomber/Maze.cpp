#include "Maze.h"
#include "Player.h"
#include "Enemy.h"
extern Gamebuino *gb;
extern Player player;
extern Enemy enemy;
extern byte gameState;

Maze::Maze() {
  byte maze[maze_w][maze_w] = {
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
}

void Maze::renderEdges () {
  gb->display.drawLine(0, 0, LCDWIDTH-1, 0); // Top
  gb->display.drawLine(0, LCDHEIGHT-1, LCDWIDTH-1, LCDHEIGHT-1); // Bottom  
  gb->display.drawLine(0, 1, 0, LCDHEIGHT-1); // Left
  gb->display.drawLine(LCDWIDTH-1, 0, LCDWIDTH-1, LCDHEIGHT-1); // Right
}

boolean Maze::isTileEmpty(byte x, byte y) {
  if (maze[y][x] == 0)
    return true;
  else 
    return false;
}

void Maze::renderMaze() {
    for(byte row = 0; row < maze_h; row++) {
    for(byte col = 0; col < maze_w; col++) {
      if (maze[row][col] == 1) {
        gb->display.fillRect(col*4,row*4,4,4); 
      } else if (maze[row][col] == 2 ) {
        gb->display.drawRect(col*4,row*4,4,4);         
      } else if (maze[row][col] == 2 ) {
        gb->display.drawRect(col*4,row*4,4,4);         
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
      if (maze[row][col] == 0 ) continue; // If empty skip
 
      if (gb->collideRectRect(xIn, yIn, player.w, player.h, col*wall_size_x, row*wall_size_y, wall_size_x, wall_size_y)) {
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
   byte tileX = Maze::toTileX(x);
   byte tileY = Maze::toTileY(y);
   
   byte tilePlayerX = Maze::toTileX(player.x);
   byte tilePlayerY = Maze::toTileY(player.y);
   
   Serial.print("Bomb X:");
   Serial.print(tileX);
   Serial.print(" Y:" );
   Serial.println(tileY);
   
   gb->sound.playOK();
      
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
      maze[tileY][tileX+1] = 0;     
      gb->sound.playTick();
   }   
   
   // Check left
   if (isBreakable(tileY, tileX-1) ) {
     Serial.println("Breakable Left");
      maze[tileY][tileX-1] = 0;     
      gb->sound.playTick();
   }   
   
   // Check Up
   if (isBreakable(tileY-1, tileX) ) {
     Serial.println("Breakable Up");
      maze[tileY-1][tileX] = 0;     
      gb->sound.playTick();
   } 
  
   // Check Down
   if (isBreakable(tileY+1, tileX) ) {
     Serial.println("Breakable Down");
      maze[tileY+1][tileX] = 0;    
     gb->sound.playTick() ;
   }  
}

void Maze::playerDead() {  
  gb->sound.playCancel();
  gameState = 1;
  player.deaths++;
}

void Maze::enemyDead() {
  gb->sound.playCancel();
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

  switch(maze[y][x]) {
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

