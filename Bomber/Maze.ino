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

extern byte playerx;
extern byte playery;
extern byte playerw;
extern byte playerh;

bool checkWallCollision() {
  for (byte row = 0; row < maze_h; row++) {
    for (byte col = 0; col < maze_w; col++) {
      if (maze[row][col] == 0 ) continue; // If not wall skip
      if (gb.collideRectRect(playerx, playery, playerw, playerh, col*wall_size_x, row*wall_size_y, wall_size_x, wall_size_y)) {
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
   
   Serial.print("Bomb X:");
   Serial.print(tileX);
   Serial.print(" Y:" );
   Serial.println(tileY);
   
   gb.sound.playOK();
   
   // Check Right
   if (isBreakable(tileY, tileX+1)) {
     Serial.println("Breakable Right");
      maze[tileY][tileX+1] = 0;     
      gb.sound.playTick();
   }   
   
   // Check left
   if (isBreakable(tileY, tileX-1)) {
     Serial.println("Breakable Left");
      maze[tileY][tileX-1] = 0;     
      gb.sound.playTick();
   }   
   
   // Check Up
   if (isBreakable(tileY-1, tileX)) {
     Serial.println("Breakable Up");
      maze[tileY-1][tileX] = 0;     
      gb.sound.playTick();
   } 
  
   // Check Down
   if (isBreakable(tileY+1, tileX)) {
     Serial.println("Breakable Down");
      maze[tileY+1][tileX] = 0;    
     gb.sound.playTick() ;
   }  
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
