#include "structs.h"
#include <iostream>
#include <GL/freeglut.h>

// keys
const int EscapeKey = 27;

// function prototypes
void drawMenuText(Menu menu);
void endGame(player winner);
void drawBall();
void drawPaddle();
void drawField();
void score(player scorer);
