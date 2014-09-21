 /***************************************************************************//**
 * pong.cpp
 * Authors - Derek Stotz, Charles Parsons
 *
 * This file contains functionality for the pong game and drawing the structs
    from structs.h.
 ******************************************************************************/
 #include "pong.h"
 
 // game objects and state information
 int player_scores[2] = { 0, 0 }
 Ball game_ball;
 Paddle player_paddles[2];
 int end_score = 10;    // the score at which a player wins the game

  /***************************************************************************//**
 * drawMenuText
 * Authors - Derek Stotz, Charles Parsons
 *
 * Draws a text menu, including the selected item.
 *
 * Parameters -
            menu - the Menu object to draw on the screen
 ******************************************************************************/
void drawMenuText(menu)
{


}

  /***************************************************************************//**
 * endGame
 * Authors - Derek Stotz, Charles Parsons
 *
 * Ends the game with a specified winner.
 *
 * Parameters -
            player - the winner
 ******************************************************************************/
void endGame(player winner)
{


}

  /***************************************************************************//**
 * drawBall
 * Authors - Derek Stotz, Charles Parsons
 *
 * Draws a Ball on the screen.
 *
 * Parameters -
            Ball - the ball object to draw
 ******************************************************************************/
void drawBall(Ball ball)
{


}

  /***************************************************************************//**
 * drawPaddle
 * Authors - Derek Stotz, Charles Parsons
 *
 * Draws a Paddle on the screen.
 *
 * Parameters -
            Paddle - the paddle object to draw
 ******************************************************************************/
void drawPaddle(Paddle paddle)
{
    //can use glRect{sfid}(x1, y1, x2, y2)
    //determine (x1, y1) & (x2, y2) using position and dimensions.
}

  /***************************************************************************//**
 * drawField
 * Authors - Derek Stotz, Charles Parsons
 *
 * Draws the playing field, including the centre line and scores
 ******************************************************************************/
void drawField()
{
    // set the background color to black
    glClearColor(Black[0], Black[1], Black[2], 1.0f);
    
    // draw a dotted white line in the middle of the screen
    
    
    // draw each player's score


}

  /***************************************************************************//**
 * score
 * Authors - Derek Stotz, Charles Parsons
 *
 * Scores one point for a player.  If this brings the score to the end_score,
    end the game with the given player as the winner.
 *
 * Parameters -
            player - the player to score for.
 ******************************************************************************/
void score(player scorer)
{
    player_scores[player]++;
    
    if( player_scores[player] >= end_score)
        endGame(player);
}