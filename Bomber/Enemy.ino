byte enemyx = 60;
byte enemyy = 16;
byte enemyw = 4;
byte enemyh = 4;
byte enemyvx = 1;
byte enemyvy = 1;

byte enemyMode = 0;

void enemySpawn() {
  enemyx = 60;
  enemyy = 16;
}

const byte enemy[] PROGMEM = {
  4, 4,
  B01100000,
  B11110000,
  B11110000,
  B01100000
};

void renderEnemy() {
  gb.display.drawBitmap(enemyx, enemyy, enemy);
}

byte getDistance(byte x1, byte y1, byte x2,byte y2) {
  return floor((abs(sqrt(((x1 - x2) * (x1 - x2) ) + ( (y1 - y2) * (y1 - y2) ) ))));
}

void updateEnemy() {
      
     if (gb.frameCount % 15) {
        if (getDistance(enemyx,enemyy,playerx,playery) < 25) {
            enemyMode = 1; // Seek
        } else 
          enemyMode = 0; // Idle
     }
    
    if (enemyMode == 1) {
    
      // Basic seek
      if (playerx > enemyx)
        enemyRight();    
      else if (playerx < enemyx)
        enemyLeft();        
      if (playery > enemyy)
        enemyDown();    
      else if (playery < enemyy)
        enemyUp();
    }
}


void enemyLeft() {
  enemyx = max(0, enemyx - enemyvx );
   if (checkWallCollision(&enemyx, &enemyy)) {
      enemyx = max(0, enemyx + enemyvx );
   }
}

void enemyRight() {
      enemyx = min(LCDWIDTH - enemyw, enemyx + enemyvx );
      if (checkWallCollision(&enemyx, &enemyy)) {
        enemyx = min(LCDWIDTH - enemyw, enemyx - enemyvx );
     }
}

void enemyUp() {
     enemyy = max(0, enemyy - enemyvy );
     if (checkWallCollision(&enemyx, &enemyy)) {
        enemyy = max(0, enemyy + enemyvy );
     }
}

 void enemyDown() {
      enemyy = min(LCDHEIGHT - enemyh, enemyy + enemyvy );
      if (checkWallCollision(&enemyx, &enemyy)) {
       enemyy = min(LCDHEIGHT - enemyh, enemyy - enemyvy );
     }
}  
