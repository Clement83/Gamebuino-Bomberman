
byte enemyMode = 0;

Entity enemy;

void initEnemy() {
   enemy.x = 60;
   enemy.y = 16;
   enemy.w = 4;
   enemy.h = 4;
   enemy.vx = 1;
   enemy.vy = 1;   
}

void enemySpawn() {
  enemy.x = 60;
  enemy.y = 16;
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
      
     if (gb.frameCount % 15) {
        if (getDistance(enemy.x,enemy.y,playerx,playery) < 25) {
            enemyMode = 1; // Seek
        } else 
          enemyMode = 0; // Idle
     }
    
    if (enemyMode == 1) {
    
      // Basic seek
      if (playerx > enemy.x)
        moveRight(&enemy);    
      else if (playerx < enemy.x)
        moveLeft(&enemy);        
      if (playery > enemy.y)
        moveDown(&enemy);    
      else if (playery < enemy.y)
        moveUp(&enemy);
    }
}


