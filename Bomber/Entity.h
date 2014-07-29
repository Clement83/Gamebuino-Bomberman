typedef struct {
  boolean active;
  byte x;
  byte y;
  byte h;
  byte w;
  byte vy;
  byte vx;
} Entity;

void moveLeft(Entity *e) {
  e->x = max(0, e->x - e->vx );
   if (checkWallCollision(&e->x, &e->y)) {
      e->x = max(0, e->x + e->vx );
   }
}

void moveRight(Entity *e) {
      e->x = min(LCDWIDTH - e->w, e->x + e->vx );
      if (checkWallCollision(&e->x, &e->y)) {
        e->x = min(LCDWIDTH - e->w, e->x - e->vx );
     }
}

void moveUp(Entity *e) {
     e->y = max(0, e->y - e->vy );
     if (checkWallCollision(&e->x, &e->y)) {
        e->y = max(0, e->y + e->vy );
     }
}

 void moveDown(Entity *e) {
     e->y = min(LCDHEIGHT - e->h, e->y + e->vy );
      if (checkWallCollision(&e->x, &e->y)) {
       e->y = min(LCDHEIGHT - e->h, e->y - e->vy );
     }
}  
