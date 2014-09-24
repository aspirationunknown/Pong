 /***************************************************************************//**
 * pong.cpp
 * Authors - Derek Stotz, Charles Parsons
 *
 * This file contains functionality for the pong game and drawing the structs
    from structs.h.
 ******************************************************************************/
 #include "pong.h"

  /***************************************************************************//**
 * drawMenuText
 * Authors - Derek Stotz, Charles Parsons
 *
 * Draws a text menu, including the selected item.
 *
 * Parameters -
            menu - the Menu object to draw on the screen
 ******************************************************************************/
void drawMenuText(Menu menu)
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
void score(player scorer, int player_scores[], int end_score)
{
    player_scores[scorer]++;
    
    if( player_scores[scorer] >= end_score)
        endGame(scorer);
}

  /***************************************************************************//**
 * display_practice
 * Authors - Derek Stotz, Charles Parsons
 *
 * Displays the practice field
 *
 * Parameters -
            player_one_paddle - the paddle under a player's control
            cpu_paddle - the paddle under the control of the computer
            ball - the ball on the field
 ******************************************************************************/
void display_practice(Paddle player_one_paddle, Paddle cpu_paddle, Ball ball)
{
}

  /***************************************************************************//**
 * display_game
 * Authors - Derek Stotz, Charles Parsons
 *
 * Displays the game field
 *
 * Parameters -
            player_one_score - the score to display of player one (right side)
            player_two_score - the score to display of player two (left side)
            player_one_paddle - the paddle under player one's player's control
            player_two_paddle - the paddle under player two's player's control
            ball - the ball on the field
 ******************************************************************************/
void display_game(int player_one_score, int player_two_score, Paddle player_one_paddle, Paddle player_two_paddle, Ball ball)
{
}


  /***************************************************************************//**
 * display_menu
 * Authors - Derek Stotz, Charles Parsons
 *
 * Displays a full menu, including the background and what is selected
 *
 * Parameters -
            menu - the menu to display
 ******************************************************************************/
void display_menu( Menu menu )
{
}
