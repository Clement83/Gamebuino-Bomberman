#include "Bomber.h"

boolean debug = false;
byte gameState = 0;
extern const byte font3x5[];

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

Bomber::Bomber() {
 Gamebuino *gb = Gamebuino(); 
}

void Bomber::setup () {
  Serial.begin(9600);
  Serial.println("Loading...");
  gb.begin();
  gb.pickRandomSeed();
  gb.setFrameRate(21);
  gb.battery.show = true;
  gb.titleScreen(F("Bomberman by Limited"), logo);
  gb.display.setFont(font3x5);
  
  Maze maze();

  Bombs::initBombs();
  initEnemy();
  initPlayer();
}

void Bomber::loop() {
  if (gb.update()) {

    handleInput();

    if (debug) {
      debugRender();
      return;
    }

    switch(gameState) {

    case 0:
      updateEnemy();
      updateBombs();

      renderGame();
      renderPlayer();
      renderEnemy();
      renderBombs(*gb);
      break;
    case 1: // Dead
      deadMenu();
      break;
    }
  }
}

void Bomber::deadMenu() {
  gb.display.print("\nYou Died\nPress A to respawn");
}

void Bomber::debugRender() {
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

  gb.display.print("\nVersion: 1.1a");
}

void Bomber::renderGame() {
  if (!debug)
    renderMap();
    
    gb.display.cursorX = LCDWIDTH-gb.display.fontWidth+1;
    gb.display.cursorY = 8;
    gb.display.print(playerDeaths);
    
    gb.display.cursorX = LCDWIDTH-gb.display.fontWidth+1;
    gb.display.cursorY = 16;
    gb.display.print(playerKills);
}
void Bomber::handleInput() {
  if (gb.buttons.pressed(BTN_B))
    debug = !debug;

  if (gb.buttons.pressed(BTN_C))
    gb.titleScreen(F("Bomberman by Limited"), logo);


  if (gameState == 0) { // Playing
    if (gb.buttons.repeat(BTN_LEFT, 1))
      moveLeft(&player);

    else if (gb.buttons.repeat(BTN_RIGHT, 1))
      moveRight(&player);

    else if (gb.buttons.repeat(BTN_UP, 1))
      moveUp(&player);

    else if (gb.buttons.repeat(BTN_DOWN, 1))
      moveDown(&player);

    if(gb.buttons.pressed(BTN_A)) {
      setBomb(player.x+(player.w/2),player.y+(player.h/2));
    }
  }
  else if (gameState == 1) {
    if (gb.buttons.pressed(BTN_A)) {
      // Respawn player
      entitySpawn(&enemy);
      entitySpawn(&player);
      player.active = true;
      gameState = 0;
    }
  }
}

