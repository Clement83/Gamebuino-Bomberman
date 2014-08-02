#ifndef MAZE_H
#define MAZE_H

#include <Arduino.h>
#include <Gamebuino.h>

#define maze_w 21
#define maze_h 12

class Maze {
  public:
    void renderEdges();
    boolean isTileEmpty(byte x,byte y);
    void renderMaze();
    boolean checkWallCollision(byte xIn, byte yIn);
    void bombExplode(byte x, byte y);  
    byte toTileX(byte x);
    byte toTileY(byte y);
    boolean isBreakable(byte x, byte y);
    void playerDead();
    void enemyDead();
};

#endif;


