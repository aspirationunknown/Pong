 /***************************************************************************//**
 * structs.cpp
 * Authors - Derek Stotz, Charles Parsons
 *
 * This file contains functionality for the structures in the pong game.
 ******************************************************************************/
 #include "structs.h"
 
 void applyCollision(Ball ball, Paddle paddle)
{
    //determine if ball and paddle collide

    //use ball position(center) and diameter, paddle position(upper left-hand 
	//corner) and dimensions to determine collision.
	
	//player1 collision: paddle right x pos is > ball x pos - diameter/2 
	//&& ball y pos +- diameter/2 is in between paddle y pos and y pos - length

    //player2 collision: paddle x pos  is < ball x pos + diameter/2
	//&& ball y pos +- diameter/2 is in between paddle y pos and y pos - length
	
    //apply appropriate vector change to ball based on where on the paddle
    //it collided.

    //if ball hits top third of paddle make y velocity positive.
    //if ball hits middle third of paddle do not change y velocity.
    //if ball hits bottom third of paddle make y velocity negative.
	
	//spin:
	//if paddle is moving up increase y velocity of ball.
	//if paddle is moving down increase -y velocity of ball.
	//if paddle is moving toward ball increase -x velocity of ball.

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
	//if player2 use 'up', 'down' ,'left', 'right' arrow keys for paddle movement.
    
}