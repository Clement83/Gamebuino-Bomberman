
boolean bombActive = false;
byte bombx = -1;
byte bomby = -1;
unsigned long bombStart;
int bombEnd;

void setBomb(byte x, byte y) {
   bombx = (round(x/4) * 4) + 2;
   bomby = (round(y/4) * 4) + 2;
   bombActive = true; 
   bombStart = millis();
   Serial.print("Set bomb x:");
   Serial.print(bombx);
   Serial.print(" y:");
   Serial.println(bomby);
   Serial.println(bombStart);   
}

void setBombInactive() { bombActive = false; }

void renderBomb() {
  if (!bombActive) return;
  if (gb.frameCount % 25) {
//    gb.display.fillRect(bombx+1,bomby, 2,1); // top  
//    gb.display.fillRect(bombx,bomby+1,1,2); // left  
//    gb.display.fillRect(bombx+1,bomby+3, 2,1); // bottom
//    gb.display.fillRect(bombx+3,bomby+1, 1,2); // right
    gb.display.drawCircle(bombx,bomby,1);
  } else {
    gb.display.fillCircle(bombx,bomby,1);
  }
}

void updateBomb() {
  if (!bombActive) return;
  
  if ((millis() - bombStart) >= 5000) {
Serial.print("Timer:");
Serial.println((millis() - bombStart));
     
     bombActive = false; 
     Serial.println("Bomb explode");
  } 
}
