#define wall_size_x 4
#define wall_size_y 4
#define maze_w 21
#define maze_h 12

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

void renderEdges () {
  gb.display.drawLine(0, 0, LCDWIDTH-1, 0); // Top
  gb.display.drawLine(0, LCDHEIGHT-1, LCDWIDTH-1, LCDHEIGHT-1); // Bottom  
  gb.display.drawLine(0, 1, 0, LCDHEIGHT-1); // Left
  gb.display.drawLine(LCDWIDTH-1, 0, LCDWIDTH-1, LCDHEIGHT-1); // Right
}

bool mazeEmpty(byte x, byte y) {
  if (maze[y][x] == 0)
    return true;
  else 
    return false;
}

void renderMap() {
    for(byte row = 0; row < maze_h; row++) {
    for(byte col = 0; col < maze_w; col++) {
      if (maze[row][col] == 1) {
        gb.display.fillRect(col*4,row*4,4,4); 
      } else if (maze[row][col] == 2 ) {
        gb.display.drawRect(col*4,row*4,4,4);         
      } else if (maze[row][col] == 2 ) {
        gb.display.drawRect(col*4,row*4,4,4);         
      }
    }
  }
}

boolean checkWallCollision(byte *xIn, byte *yIn) {
  // Get elements around player
  int tileX = toTileX(*xIn) - 2;
  int tileY = toTileY(*yIn) - 2;
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
 
      if (gb.collideRectRect(*xIn, *yIn, player.w, player.h, col*wall_size_x, row*wall_size_y, wall_size_x, wall_size_y)) {
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

void bombExplode(byte x, byte y) {
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
      maze[tileY][tileX+1] = 0;     
      gb.sound.playTick();
   }   
   
   // Check left
   if (isBreakable(tileY, tileX-1) ) {
     Serial.println("Breakable Left");
      maze[tileY][tileX-1] = 0;     
      gb.sound.playTick();
   }   
   
   // Check Up
   if (isBreakable(tileY-1, tileX) ) {
     Serial.println("Breakable Up");
      maze[tileY-1][tileX] = 0;     
      gb.sound.playTick();
   } 
  
   // Check Down
   if (isBreakable(tileY+1, tileX) ) {
     Serial.println("Breakable Down");
      maze[tileY+1][tileX] = 0;    
     gb.sound.playTick() ;
   }  
}


void playerDead() {  
  gb.sound.playCancel();
  setup();
}

void enemyDead() {
  gb.sound.playCancel();
  enemySpawn();
}
byte toTileX(byte xIn) {
   return round(xIn / wall_size_x); 
}

byte toTileY(byte yIn) {
   return round(yIn / wall_size_y); 
}

boolean isBreakable(byte y, byte x) {  
  // TODO: check bounds
  Serial.print("tile: ");
  Serial.println(maze[y][x]);

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
