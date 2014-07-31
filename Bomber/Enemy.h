#ifndef "Enemy.h"
#define "Enemy.h"

class Enemy : Entity {
  public:  
    Enemy();
    byte enemyMode;
    void initEnemy();
    void renderEnemy();
    void getDistance();
    void updateEnemy();
    
};

byte enemyMode = 0;

const byte enemySprite[] PROGMEM = {
  4, 4,
  B01100000,
  B11110000,
  B11110000,
  B01100000
};


#endif


