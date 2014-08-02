#ifndef MAZE_H
#define MAZE_H

#include <Arduino.h>
#include <Gamebuino.h>

#define wall_size_x 4
#define wall_size_y 4
#define maze_w 21
#define maze_h 12

class Maze {
  public:
    Maze();
    void renderEdges();
    boolean isTileEmpty(byte x,byte y);
    void renderMaze();
    boolean checkWallCollision(byte xIn, byte yIn);
    void bombExplode(byte x, byte y);  
    byte toTileX(byte x);
    byte toTileY(byte y);
    boolean isBreakable(byte x, byte y);
    byte maze[maze_w][maze_w];
    void playerDead();
    void enemyDead();
};

#endif;


