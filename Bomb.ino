boolean bombActive = false;
byte bombx = -1;
byte bomby = -1;
byte bombTimer = -1;

void setBomb(byte x, byte y) {
   bombx = x;
   bomby = y;
   bombActive = true; 
}

void setBombInactive() { bombActive = false; }
void renderBomb() {
  if (!bombActive) return;
  if (gb.frameCount % 25) {
//    gb.display.fillRect(bombx+1,bomby, 2,1); // top  
//    gb.display.fillRect(bombx,bomby+1,1,2); // left  
//    gb.display.fillRect(bombx+1,bomby+3, 2,1); // bottom
//    gb.display.fillRect(bombx+3,bomby+1, 1,2); // right
    gb.display.drawCircle(bombx,bomby,2);
  } else {
    gb.display.fillCircle(bombx,bomby,2);
  }
}


