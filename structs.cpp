/***************************************************************************//**
 * structs.cpp
 * Authors - Derek Stotz, Charles Parsons
 *
 * This file contains functionality for the structures in the pong game.
 ******************************************************************************/
#include "structs.h"
#include <iostream> 

 /***************************************************************************//**
 * applyCollision
 * Authors - Derek Stotz, Charles Parsons
 *
 * Takes a ball and a paddle and applies a velocity modification based on
    whether or not the paddle is in contact with the ball.
******************************************************************************/
bool applyCollision(Ball &ball, Paddle paddle[2])
{   
    int paddle_next_location; //where the paddle will be in the next step
    int ball_next_location; //where the ball will be in the next step
    bool should_collide = false;

    //use ball position(center) and diameter, paddle position(lower left-hand 
    //corner) and dimensions to determine collision.

    //if paddle is moving predict where paddle will be at next step and where
    //ball will be next step. if they would have passed through each other
    //cause collision.
    if(paddle[PLAYER_ONE].velocity_vector.first > 0)
    {
        //predict paddle's next location
        //predict ball's next location
        //if there should be a collision 
        paddle_next_location = paddle[PLAYER_ONE].position.first + 
                               paddle[PLAYER_ONE].velocity_vector.first;
        ball_next_location = ball.position.first + ball.velocity_vector.first;
        
        if((ball_next_location - ball.diameter / 2.0 < 
            paddle_next_location + 
            paddle[PLAYER_ONE].dimensions.first) && 
           (ball.position.second - ball.diameter / 2.0 > 
            paddle[PLAYER_ONE].position.second) &&
           (ball.position.second + ball.diameter / 2.0 <
            paddle[PLAYER_ONE].position.second + 
            paddle[PLAYER_ONE].dimensions.second) &&
           (ball.position.first - ball.diameter / 2.0 > //checks if ball is not
            paddle[PLAYER_ONE].position.first +
            paddle[PLAYER_ONE].velocity_vector.first))         //behind paddle
        {
            ball.velocity_vector.first *= -1;
            applySpin(ball, paddle[PLAYER_ONE]);
            return true;
        }

    }
    else
    {
        //player1 collision: paddle right x pos is > ball x pos - diameter/2
        //&& ball y pos +- diameter/2 is in between paddle y pos and y pos - 
        //length
        if((ball.position.first - ball.diameter / 2.0 < 
            paddle[PLAYER_ONE].position.first + 
            paddle[PLAYER_ONE].dimensions.first) && 
           (ball.position.second - ball.diameter / 2.0 > 
            paddle[PLAYER_ONE].position.second) &&
           (ball.position.second + ball.diameter / 2.0 <
            paddle[PLAYER_ONE].position.second + 
            paddle[PLAYER_ONE].dimensions.second) &&
           (ball.position.first - ball.diameter / 2.0 > //checks if ball is not
            paddle[PLAYER_ONE].position.first))         //behind paddle
        {
            ball.velocity_vector.first *= -1;
            applySpin(ball, paddle[PLAYER_ONE]);
            return true;
        }
    }
    
    if(paddle[PLAYER_TWO].velocity_vector.first < 0)
    {
        //predict paddle's next location
        //predict ball's next location
        //if there should be a collision 
        paddle_next_location = paddle[PLAYER_TWO].position.first + 
                               paddle[PLAYER_TWO].velocity_vector.first;
        ball_next_location = ball.position.first + ball.velocity_vector.first;
        
        if((ball_next_location + ball.diameter / 2.0 >
            paddle_next_location) &&
           (ball.position.second - ball.diameter / 2.0 > 
            paddle[PLAYER_TWO].position.second) &&
           (ball.position.second + ball.diameter / 2.0 <
            paddle[PLAYER_TWO].position.second +
            paddle[PLAYER_TWO].dimensions.second) &&
           (ball.position.first + ball.diameter / 2.0 < //makes sure ball is not
            paddle[PLAYER_TWO].position.first -
            paddle[PLAYER_TWO].velocity_vector.first +         //behind paddle
            paddle[PLAYER_TWO].dimensions.first))
        {
            ball.velocity_vector.first *= -1;
            applySpin(ball, paddle[PLAYER_TWO]);
            return true;
        }
    }
    else
    {
        //player2 collision: paddle x pos  is < ball x pos + diameter/2
        //&& ball y pos +- diameter/2 is in between paddle y pos and y pos - 
        //length
        if((ball.position.first + ball.diameter / 2.0 >
            paddle[PLAYER_TWO].position.first) &&
           (ball.position.second - ball.diameter / 2.0 > 
            paddle[PLAYER_TWO].position.second) &&
           (ball.position.second + ball.diameter / 2.0 <
            paddle[PLAYER_TWO].position.second +
            paddle[PLAYER_TWO].dimensions.second) &&
           (ball.position.first + ball.diameter / 2.0 < //makes sure ball is not
            paddle[PLAYER_TWO].position.first +         //behind paddle
            paddle[PLAYER_TWO].dimensions.first))
        {
            ball.velocity_vector.first *= -1;
            applySpin(ball, paddle[PLAYER_TWO]);
            return true;
        }
    }
    return false;
}


 /***************************************************************************//**
 * movePaddle
 * Authors - Derek Stotz, Charles Parsons
 *
 * Checks currently pressed keys and moves a given paddle based on which keys
    are currently being pressed for a given player.
 ******************************************************************************/
void movePaddle(Paddle paddle, player mover)
{
    //after key-press move paddle in the direction indicated by the key pressed.
    //How does it know what key was pressed?
    //if player1 use 'w', 'a', 's', 'd' keys for paddle movement.
    //if player2 use 'up', 'down' ,'left', 'right' arrow keys for paddle 
    //movement.
    
}


 /***************************************************************************//**
 * applySpin
 * Authors - Derek Stotz, Charles Parsons
 *
 * Takes a ball and a colliding paddle and applies a "spin", or a velocity
    modification dependant on the paddle's relative position.
 ******************************************************************************/
void applySpin(Ball &ball, Paddle &paddle)
{
    bool collision = false;
    int moving = 0; // 1 = up, -1 = down, 0 = not moving
    int spin = 0; //1 = top, -1 = bottom, 0 = middle
  
    //if paddle is moving up increase y velocity of ball.
    if(paddle.velocity_vector.second > 0)
    {
        moving = 1;
    }
    //if paddle is moving down increase -y velocity of ball.
    else if(paddle.velocity_vector.second < 0)
    {
        moving = -1;
    }
    //if paddle is moving toward ball increase -x velocity of ball.
    else
    {
        moving = 0;
    }
    
    //if ball hits top third of paddle make y velocity positive.
    if(ball.position.second > paddle.position.second -
       paddle.position.second / 3.0)
    {
        spin = 1;
        collision = true;
    } 
    //if ball hits bottom third of paddle make y velocity negative.
    else if(ball.position.second < paddle.position.second -
            paddle.position.second * 2 / 3.0)
    {
        spin = -1;
        collision = true;
    }
    ///if ball hits middle third of paddle do not change y velocity.
    else
    {
        spin = 0;
        collision = true;
    }
    std::cout << "ball velocity: " << ball.velocity_vector.first << ", " << ball.velocity_vector.second << std::endl;
    //formula for new ball velocity:
    //x_bvelocity = (xbvelocity > 0) ? -(x_bvelocity + x_pvelocity): -x_bvelocity + x_pvelocity
    //                                  
    //y bvelocity = 
    ball.velocity_vector.first = (collision && ball.velocity_vector.first > 0) ? (ball.velocity_vector.first + abs(paddle.velocity_vector.first)) :
                                 (ball.velocity_vector.first + abs(paddle.velocity_vector.first));
    ball.velocity_vector.second = 0;
    collision = false;
}

/*Ball::Ball(int diam, int max_v, std::pair<int, int> v_vector, std::pair<int, int> pos, float* clr)
{
    this.diameter = diam;
    this.max_velocity = max_v;
    this.velocity_vector = v_vector;
    this.position = pos;
    this.color = clr;
}

Paddle::Paddle(std::pair<int, int> dim, std::pair<int, int> v_vector, std::pair<int, int> pos, std::pair<int, int> mov_speed, float* clr)
{
    this.dimensions = dim;
    this.velocity_vector = v_vector;
    this.position = pos;
    this.movement_speed = mov_speed;
    this.color = clr;
}

Menu::Menu(std::string* opt, int sel_index, fptr* opt_actions, float* bck_color, float* txt_color, float* sel_color)
{
    this.options = opt;
    this.selection_index = sel_index;
    this.option_actions = opt_actions;
    this.background_color = bck_color;
    this.text_color = txt_color;
    this.selection_color = sel_color
}*/

void assignColor(float value[3], const float color[3])
{
    value[0] = color[0];
    value[1] = color[1];
    value[2] = color[2];
}
