#include "structs.h"
#include <iostream>
#include <GL/freeglut.h>

// keys
const int EscapeKey = 27;

// player enumeration
enum player {PLAYER_ONE, PLAYER_TWO};

// function prototypes
void drawMenuText(menu);
void endGame(player winner);
void drawBall();
void drawPaddle();
void drawField();
void score(player scorer);