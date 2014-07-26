#define wall_size_x 4
#define wall_size_y 4
#define maze_w 21
#define maze_h 12

byte maze[maze_w][maze_w] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
      }
    }
  }
}
