#include <SPI.h>
#include <Gamebuino.h>
#include <math.h>
Gamebuino gb = Gamebuino();

boolean debug = false;
extern const byte font3x5[];

void setup () {
  Serial.begin(9600);
  Serial.println("Loading...");
  gb.begin();
  gb.pickRandomSeed();
  gb.setFrameRate(21);
  gb.battery.show = true; 
  gb.titleScreen(F("Bomberman by Limited"));
  gb.display.setFont(font3x5);
}

void loop() {
   if (gb.update()) {  
    
    handleInput(); 
    debugRender();
    updateBomb();
    
    renderGame();
    renderPlayer();
    renderBomb();
  }  
}
extern byte playerx;
extern byte playery;
extern byte playerw;
extern byte playerh;
void debugRender() {
    if (!debug) return;

    
    gb.display.print("\nDebug Bomberman\n");
    gb.display.print("Player X:");
    gb.display.print(playerx);
    gb.display.print("\nPlayer Y:");
    gb.display.print(playery);
    
    gb.display.print("\nRAM Free:");
    gb.display.print(gb.getFreeRam());
    
    gb.display.print("\nCPU: ");
    gb.display.print(gb.getCpuLoad());
    
    gb.display.print("\nVersion: alpha 1.0");
}

void renderGame() {
  if (!debug)
     renderMap();
}
void handleInput() {
  if (gb.buttons.pressed(BTN_B)) 
    debug = !debug;
    
  if (gb.buttons.pressed(BTN_C))
     gb.titleScreen(F("Bomberman by Limited2"));
     
  if (gb.buttons.repeat(BTN_LEFT, 1))    
    playerLeft();
    
  else if (gb.buttons.repeat(BTN_RIGHT, 1))    
    playerRight();
    
  else if (gb.buttons.repeat(BTN_UP, 1))   
    playerUp();
      
  else if (gb.buttons.repeat(BTN_DOWN, 1))    
    playerDown();
    
  if(gb.buttons.pressed(BTN_A)) {
      setBomb(playerx+(playerw/2),playery+(playerh/2));
  }
}
