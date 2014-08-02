#include "Enemy.h"
#include "Player.h"
#include <Arduino.h>
#include <Gamebuino.h>
extern Gamebuino gb;
extern Player player;

Enemy::Enemy() {
  w = 4;
  h = 4;
  vx = 1;
  vy = 1;
  entitySpawn();
}

void Enemy::renderEnemy() {
  gb.display.drawBitmap(x, y, enemySprite);
}

void Enemy::updateEnemy() {
  
  dist = getDistance(x,y,player.x,player.y);
  
  if (gb.frameCount % 25) {
    if (dist < 30) enemyMode = 1; // Seek    
    else enemyMode = 0; // Idle
    if (dist <= 4) player.doDamage(10);
  }
  if (enemyMode == 1) {

    // Basic seek
    if (player.x > x)
      moveRight();
    else if (player.x < x)
      moveLeft();
    if (player.y > y)
      moveDown();
    else if (player.y < y)
      moveUp();
  }
}

