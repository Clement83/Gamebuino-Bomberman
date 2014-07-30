
byte enemyMode = 0;

Entity enemy;

void initEnemy() {
  enemy.w = 4;
  enemy.h = 4;
  enemy.vx = 1;
  enemy.vy = 1;
  entitySpawn(&enemy);
}

const byte enemySprite[] PROGMEM = {
  4, 4,
  B01100000,
  B11110000,
  B11110000,
  B01100000
};

void renderEnemy() {
  gb.display.drawBitmap(enemy.x, enemy.y, enemySprite);
}

byte getDistance(byte x1, byte y1, byte x2,byte y2) {
  return floor((abs(sqrt(((x1 - x2) * (x1 - x2) ) + ( (y1 - y2) * (y1 - y2) ) ))));
}

void updateEnemy() {

  if (gb.frameCount % 25) {
    if (getDistance(enemy.x,enemy.y,player.x,player.y) < 30) {
      enemyMode = 1; // Seek
    }
    else
      enemyMode = 0; // Idle
  }

  if (enemyMode == 1) {

    // Basic seek
    if (player.x > enemy.x)
      moveRight(&enemy);
    else if (player.x < enemy.x)
      moveLeft(&enemy);
    if (player.y > enemy.y)
      moveDown(&enemy);
    else if (player.y < enemy.y)
      moveUp(&enemy);
  }
}



