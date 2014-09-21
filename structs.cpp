/***************************************************************************//**
 * structs.cpp
 * Authors - Derek Stotz, Charles Parsons
 *
 * This file contains functionality for the structures in the pong game.
 ******************************************************************************/
#include "structs.h"
 
void applyCollision(Ball &ball, Paddle paddle[2])
{
    //determine if ball and paddle collide, assuming (0,0) is in upper
    //left-hand corner of window

    //use ball position(center) and diameter, paddle position(upper left-hand 
    //corner) and dimensions to determine collision.

    //player1 collision: paddle right x pos is > ball x pos - diameter/2 
    //&& ball y pos +- diameter/2 is in between paddle y pos and y pos - length
    if((ball.position.first - ball.diameter / 2.0 < 
        paddle[PLAYER_ONE].position.first + 
        paddle[PLAYER_ONE].dimensions.first) && 
       (ball.position.second + ball.diameter / 2.0 < 
        paddle[PLAYER_ONE].position.second) &&
       (ball.position.second - ball.diameter / 2.0 >
        paddle[PLAYER_ONE].position.second - 
        paddle[PLAYER_ONE].dimensions.second))
    {
        ball.velocity_vector.first *= -1;
        applySpin(ball, paddle);
        return;
    }
     
    //player2 collision: paddle x pos  is < ball x pos + diameter/2
    //&& ball y pos +- diameter/2 is in between paddle y pos and y pos - length
    if((ball.position.first - ball.diameter / 2.0 > 
        paddle[PLAYER_TWO].position.first) &&
       (ball.position.second + ball.diameter / 2.0 < 
        paddle[PLAYER_TWO].position.second) &&
       (ball.position.second - ball.diameter / 2.0 >
        paddle[PLAYER_TWO].position.second -
        paddle[PLAYER_TWO].dimensions.second))
    {
        ball.velocity_vector.first *= -1;
        applySpin(ball, paddle);
        return;
    }
    //apply appropriate vector change to ball based on where on the paddle
    //it collided.

    //determine if ball and wall collide.
    //apply appropriate vector change to ball if it hits a wall.
    //if ball y pos - diameter/2 is < bottom wall or ball y pos + diameter/2 
    //is > top wall.
}


void movePaddle(Paddle paddle)
{
    //after key-press move paddle in the direction indicated by the key pressed.
    //How does it know what key was pressed?
    //if player1 use 'w', 'a', 's', 'd' keys for paddle movement.
    //if player2 use 'up', 'down' ,'left', 'right' arrow keys for paddle 
    //movement.
    
}


void applySpin(Ball &ball, Paddle paddle[2])
{
    //spin:
    //if paddle is moving up increase y velocity of ball.
    //if paddle is moving down increase -y velocity of ball.
    //if paddle is moving toward ball increase -x velocity of ball.

    //if ball hits top third of paddle make y velocity positive.
    //if ball hits middle third of paddle do not change y velocity.
    //if ball hits bottom third of paddle make y velocity negative.

}
