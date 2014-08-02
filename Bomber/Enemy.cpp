#include "Enemy.h"
#include "Player.h"
#include <Arduino.h>
#include <Gamebuino.h>
extern Gamebuino *gb;
extern Player player;

Enemy::Enemy() {
  w = 4;
  h = 4;
  vx = 1;
  vy = 1;
  entitySpawn();
}

void Enemy::renderEnemy() {
  gb->display.drawBitmap(x, y, enemySprite);
}

void Enemy::updateEnemy() {

  if (gb->frameCount % 25) {
    if (getDistance(x,y,player.x,player.y) < 30) {
      enemyMode = 1; // Seek
    }
    else
      enemyMode = 0; // Idle
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

