#include <SPI.h>
#include <Gamebuino.h>
Gamebuino gb = Gamebuino();

boolean debug = false;

void setup () {
  gb.begin();
  gb.pickRandomSeed();
  gb.setFrameRate(41);
  gb.battery.show = true; 
  gb.titleScreen(F("Bomberman by Limited"));
}

void loop() {
   if (gb.update()) {  
    
    handleInput(); 
    debugRender();
    renderGame();
  }  
}

void debugRender() {
    if (!debug) return;
  
    gb.display.print("\nDebug Bomberman\n");
    
    gb.display.print("\nRAM:");
    gb.display.print(gb.getFreeRam());
    
    gb.display.print("\nCPU: ");
    gb.display.print(gb.getCpuLoad());
}

void renderGame() {
  if (!debug)
     renderMap();
}
void handleInput() {
  if (gb.buttons.pressed(BTN_C))
    debug = !debug;
}
