#include "Player.h"

Player::Player() {
  player.x = 4;
  player.y = 4;
  player.w = 4;
  player.h = 4;
  player.vx = 2;
  playervxStart = player.vx;
  player.vy = 2;
  playervyStart = player.vy;
  playerDeaths = playerKills = 0;
}

void Player::renderPlayer() {
   gb.display.fillRect(player.x, player.y, player.w, player.h); 
   gb.display.setColor(WHITE);
   gb.display.drawPixel(player.x+1, player.y+1);
   gb.display.drawPixel(player.x+2, player.y+2);
   gb.display.setColor(BLACK);
}

