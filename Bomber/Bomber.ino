#include <SPI.h>
#include <Gamebuino.h>
#include "Bomber.h"
Gamebuino gb = Gamebuino();

boolean debug = false;
byte gameState = 0;
extern const byte font3x5[];

#define BOMB_MAX 3

Bomber bomber;
Maze maze;
Player player;
Enemy enemy;
Bomb bombs[BOMB_MAX];

const byte logo[] PROGMEM = {
  64,30,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00011000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B01111110,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00011111,B11100001,B11100010,B00000000,B00000000,
  B00000000,B00000000,B00000000,B01111111,B11111001,B11000011,B00000000,B00000000,
  B00000000,B00000000,B00000001,B11111111,B11111111,B10000011,B00000000,B00000000,
  B00000000,B00000000,B00000011,B11111111,B11111111,B10000000,B00000000,B00000000,
  B00000000,B00000000,B00000111,B11111111,B11111111,B10000000,B00000000,B00000000,

  B00000000,B00000000,B00001111,B11111111,B11111111,B11000000,B00000000,B00000000,
  B00000000,B00000000,B00001111,B11100000,B00111111,B11000000,B00000000,B00000000,
  B00000000,B00000000,B00011111,B11100111,B10001111,B11100000,B00000000,B00000000,
  B00000000,B00000000,B00011111,B11100111,B11001111,B11100000,B00000000,B00000000,
  B00000000,B00000000,B00011111,B11100111,B11001111,B11100000,B00000000,B00000000,
  B00000000,B00000000,B00111111,B11100111,B11001111,B11110000,B00000000,B00000000,
  B00000000,B00000000,B00111111,B11100111,B10011111,B11110000,B00000000,B00000000,
  B00000000,B00000000,B00111111,B11100000,B00111111,B11110000,B00000000,B00000000,

  B00000000,B00000000,B00111111,B11100111,B10001111,B11110000,B00000000,B00000000,
  B00000000,B00000000,B00111111,B11100111,B11100111,B11110000,B00000000,B00000000,
  B00000000,B00000000,B00111111,B11100111,B11100111,B11110000,B00000000,B00000000,
  B00000000,B00000000,B00111111,B11100111,B11100111,B11110000,B00000000,B00000000,
  B00000000,B00000000,B00011111,B11100111,B11000111,B11100000,B00000000,B00000000,
  B00000000,B00000000,B00011111,B11100111,B10001111,B11100000,B00000000,B00000000,
  B00000000,B00000000,B00011111,B11100000,B00111111,B11100000,B00000000,B00000000,
  B00000000,B00000000,B00001111,B11111111,B11111111,B11000000,B00000000,B00000000,

  B00000000,B00000000,B00001111,B11111111,B11111111,B11000000,B00000000,B00000000,
  B00000000,B00000000,B00000111,B11111111,B11111111,B10000000,B00000000,B00000000,
  B00000000,B00000000,B00000011,B11111111,B11111111,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000001,B11111111,B11111110,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B01111111,B11111000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00011111,B11100000,B00000000,B00000000,B00000000,
};

void setup () {
  
  Serial.begin(9600);
  Serial.println("Loading...");
  gb.begin();
  gb.pickRandomSeed();
  gb.setFrameRate(21);
  gb.battery.show = true;
  gb.titleScreen(F("Bomberman by Limited"), logo);
  gb.display.setFont(font3x5);
}

void loop() {
  if (gb.update()) {

    handleInput();

    if (debug) {
      debugRender();
      return;
    }

    switch(gameState) {

    case 0:
      enemy.updateEnemy();
      updateBombs();

      renderGame();
      player.renderPlayer();
      enemy.renderEnemy();
      renderBombs();
     
      break;
    case 1: // Dead
      deadMenu();
      break;
    }
  }
}

void deadMenu() {
  gb.display.print("\nYou Died\nPress A to respawn");
}

void debugRender() {
  if (!debug) return;

  gb.display.print("\nDebug Bomberman\n");
  gb.display.print("Player X:");
  gb.display.print(player.x);
  gb.display.print("\nPlayer Y:");
  gb.display.print(player.y);

  gb.display.print("\nRAM Free:");
  gb.display.print(gb.getFreeRam());

  gb.display.print("\nCPU: ");
  gb.display.print(gb.getCpuLoad());

  gb.display.print("\nVersion: 2.0a");
}

void renderGame() {
   if (!debug)
    maze.renderMaze();
    
    gb.display.cursorX = LCDWIDTH-gb.display.fontWidth+1;
    gb.display.cursorY = 8;
    gb.display.print(player.deaths);
    
    gb.display.cursorX = LCDWIDTH-gb.display.fontWidth+1;
    gb.display.cursorY = 16;
    gb.display.print(player.kills);
}
void handleInput() {
  if (gb.buttons.pressed(BTN_B)) {
    debug = !debug;
  }

  if (gb.buttons.pressed(BTN_C))
    gb.titleScreen(F("Bomberman by Limited"), logo);


  if (gameState == 0) { // Playing
    if (gb.buttons.repeat(BTN_LEFT, 1))
      player.moveLeft();

    else if (gb.buttons.repeat(BTN_RIGHT, 1))
      player.moveRight();

    else if (gb.buttons.repeat(BTN_UP, 1))
      player.moveUp();

    else if (gb.buttons.repeat(BTN_DOWN, 1))
      player.moveDown();

    if(gb.buttons.pressed(BTN_A)) {
      setBomb(player.x+(player.w/2),player.y+(player.h/2));
    }
  }
  else if (gameState == 1) {
    if (gb.buttons.pressed(BTN_A)) {
      // Respawn player
      enemy.entitySpawn();
      player.entitySpawn();
      player.active = true;
      gameState = 0;
    }
  }
}

void renderBombs() {
  for (int i = 0; i < BOMB_MAX; i++) {
      if (!bombs[i].active) continue;
      
      Bomb *b = &bombs[i];
      if (gb.frameCount % 25) {
        gb.display.fillRect(b->x+1,b->y, 2,1); // top  
        gb.display.fillRect(b->x,b->y+1,1,2); // left  
        gb.display.fillRect(b->x+1,b->y+3, 2,1); // bottom
        gb.display.fillRect(b->x+3,b->y+1, 1,2); // right
      }
  }
}

void updateBombs() {
  for (int i = 0; i < BOMB_MAX; i++) {
      if (!bombs[i].active) continue;
      Bomb *b = &bombs[i];
  
      if ((millis() - b->startTime) >= 5000) {
         b->active = false; 
          maze.bombExplode(b->x, b->y);
      } 
  }
}
void setBomb(byte x, byte y) {
   for (int i= 0; i < BOMB_MAX; i++) {     
      if (bombs[i].active) continue; 
      
      Bomb b;
      b.active = true;
      b.x = (round(x/4) * 4);
      b.y = (round(y/4) * 4);
      b.startTime = millis();
      bombs[i] = b;
      break;
   }
}


