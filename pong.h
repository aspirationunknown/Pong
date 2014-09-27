#include "structs.h"
#include <iostream>
#include <GL/freeglut.h>

// keys
const int EscapeKey = 27;

// screens
enum screen {MAINMENU, PRACTICE, GAME, PAUSE};

// function prototypes
void endGame(player winner);
void drawBall(Ball* ball);
void drawPaddle(Paddle* paddle);
void drawField();
void score(player scorer, int player_scores[], int end_score);

// display functions
void display_menu(Menu &menu, int x, int y, int spacing);
void display_practice(Paddle &player_one_paddle, Paddle &cpu_paddle, Ball &ball, int ScreenWidth, int ScreenHeight);
void display_game(int player_two_score[], Paddle &player_one_paddle, Paddle &player_two_paddle, Ball &ball, int ScreenWidth, int ScreenHeight);
void DrawStrokeString( const char *string, float x, float y, float color[] );
void DrawLine( float x1, float y1, float x2, float y2, const float color[] );
void DrawFilledEllipse( float x, float y, float xRadius, float yRadius, float color[] );
void DrawFilledRectangle( float x1, float y1, float x2, float y2, float color[] );
