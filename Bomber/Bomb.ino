
boolean bombActive = false;
byte bombx = 0;
byte bomby = 0;
unsigned long bombStart;

void setBomb(byte x, byte y) {
   if (bombActive) return;
  
   bombx = (round(x/4) * 4);
   bomby = (round(y/4) * 4);
   bombActive = true; 
   bombStart = millis();
   Serial.print("Set bomb x:");
   Serial.print(bombx);
   Serial.print(" y:");
   Serial.println(bomby);
   Serial.println(bombStart);   
}

void renderBomb() {
  if (!bombActive) return;
  if (gb.frameCount % 25) {
    gb.display.fillRect(bombx+1,bomby, 2,1); // top  
    gb.display.fillRect(bombx,bomby+1,1,2); // left  
    gb.display.fillRect(bombx+1,bomby+3, 2,1); // bottom
    gb.display.fillRect(bombx+3,bomby+1, 1,2); // right
  }
//    gb.display.drawCircle(bombx+2,bomby+2,1);
//  } else {
//    gb.display.fillCircle(bombx+2,bomby+2,1);
//  }
}

void updateBomb() {
  if (!bombActive) return;
  
  if ((millis() - bombStart) >= 5000) {
     bombActive = false; 
     Serial.println("Bomb explode");
     bombExplode(bombx, bomby);
  } 
}
