#include "structs.h"
#include <iostream>
#include <GL/freeglut.h>

// keys
const int EscapeKey = 27;

// screens
enum screen {MAINMENU, PRACTICE, GAME, PAUSE};

// function prototypes
void endGame(player winner);
void drawBall();
void drawPaddle();
void drawField();
void score(player scorer);

// display functions
void display_menu(Menu* menu, int x, int y, int spacing);
void display_practice(Paddle player_one_paddle, Paddle cpu_paddle, Ball ball);
void display_game(int player_one_score, int player_two_score, Paddle player_one_paddle, Paddle player_two_paddle, Ball ball);
void DrawStrokeString( const char *string, float x, float y, float color[] );
