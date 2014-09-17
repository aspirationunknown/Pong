 /***************************************************************************//**
 * structs.cpp
 * Authors - Derek Stotz, Charles Parsons
 *
 * This file contains functionality for the structures in the pong game.
 ******************************************************************************/
 #include "structs.h"
 
 void applyCollision(ball b, paddle p)
{
    //determine if ball and paddle collide

    //use ball position and diameter, paddle position and dimensions to
    //determine collision.

    //apply appropriate vector change to ball based on where on the paddle
    //it collided.

    //if ball hits top third of paddle make y velocity positive.
    //if ball hits middle third of paddle do not change y velocity.
    //if ball hits bottom third of paddle make y velocity negative.

    //apply appropriate vector change to ball if it hits a wall.

}


void movePaddle(paddle p)
{
    //after keypress move paddle in the direction indicated by the key pressed.
    
}