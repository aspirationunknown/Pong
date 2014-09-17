 /***************************************************************************//**
 * pong.cpp
 * Authors - Derek Stotz, Charles Parsons
 *
 * This file contains functionality for the pong game and drawing the structs
    from structs.h.
 ******************************************************************************/
 #include "pong.h"
 
 int player_scores[2] = { 0, 0 }
 
 // the score at which a player wins the game
 int end_score = 10;

void drawMenuText(menu)
{


}


void endGame(player winner)
{


}


void drawBall()
{


}


void drawPaddle()
{
    //can use glRect{sfid}(x1, y1, x2, y2)
    //determine (x1, y1) & (x2, y2) using position and dimensions.
}


void drawField()
{


}

void score(player scorer)
{
    player_scores[player]++;
    
    if( player_scores[player] >= end_score)
        endGame(player);
}