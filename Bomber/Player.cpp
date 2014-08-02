#include "Player.h"

extern Gamebuino *gb;

Player::Player() {
  x = 4;
  y = 4;
  w = 4;
  h = 4;
  vx = 2;
  playervxStart = vx;
  vy = 2;
  playervyStart = vy;
  deaths = kills = 0;
}

void Player::renderPlayer() {
   gb->display.fillRect(x, y, w, h); 
   gb->display.setColor(WHITE);
   gb->display.drawPixel(x+1, y+1);
   gb->display.drawPixel(x+2, y+2);
   gb->display.setColor(BLACK);
}

