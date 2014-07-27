byte playerx = 4;
byte playery = 4;
byte playerw = 4;
byte playerh = 4;
byte playervx = 2;
byte playervxStart = playervx;
byte playervy = 2;
byte playervyStart = playervy;
byte playerscore = 0;


void renderPlayer() {
   gb.display.fillRect(playerx, playery, playerw, playerh); 
   gb.display.setColor(WHITE);
   gb.display.drawPixel(playerx+1, playery+1);
   gb.display.setColor(BLACK);
}

void playerLeft() {
  playerx = max(0, playerx - playervx );
   if (checkWallCollision()) {
     playervx = 1;
      playerx = max(0, playerx + playervx );
   } else {
      playervx = playervxStart; 
   }
}

void playerRight() {
      playerx = min(LCDWIDTH - playerw, playerx + playervx );
      if (checkWallCollision()) {
        playervx = 1;
        playerx = min(LCDWIDTH - playerw, playerx - playervx );
     } else
       playervx = playervyStart;
}

void playerUp() {
     playery = max(0, playery - playervy );
     if (checkWallCollision()) {
       playervy = 1;
        playery = max(0, playery + playervy );
     } else 
       playervy = 2;
}

 void playerDown() {
      playery = min(LCDHEIGHT - playerh, playery + playervy );
      if (checkWallCollision()) {
        playervy= 1;
       playery = min(LCDHEIGHT - playerh, playery - playervy );
     } else 
       playervy = 2;
   }  
