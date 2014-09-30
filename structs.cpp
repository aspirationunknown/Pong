/***************************************************************************//**
 * structs.cpp
 * Authors - Derek Stotz, Charles Parsons
 *
 * This file contains functionality for the structures in the pong game.
 ******************************************************************************/
#include "structs.h"


 /***************************************************************************//**
 * applyCollision
 * Authors - Derek Stotz, Charles Parsons
 *
 * Takes a ball and a paddle and applies a velocity modification based on
    whether or not the paddle is in contact with the ball.
******************************************************************************/
bool applyCollision(Ball &ball, Paddle paddle[2])
{   
    int ball_bounding_box[4] = {0}; //stored as left-x, top-y, right-x, bottom-y
    int paddle_bounding_box[2][4] = {0}; //stored as left-x, top-y, right-x, bottom-y
                                         //row zero is player one and row 1 is player 2

    //calculate ball bounding box
    ball_bounding_box[0] = ball.position.first - ball.diameter / 2.0;  //left-x
    ball_bounding_box[1] = ball.position.second + ball.diameter / 2.0; //top-y
    ball_bounding_box[2] = ball.position.first + ball.diameter / 2.0;  //right-x
    ball_bounding_box[3] = ball.position.second - ball.diameter / 2.0; //bottom-y

    //calculate bounding box for player one's paddle
    paddle_bounding_box[PLAYER_ONE][0] = paddle[PLAYER_ONE].position.first;          //left-x
    paddle_bounding_box[PLAYER_ONE][1] = paddle[PLAYER_ONE].position.second + 1.04 * //top-y
                                         paddle[PLAYER_ONE].dimensions.second;
    paddle_bounding_box[PLAYER_ONE][2] = paddle[PLAYER_ONE].position.first +         //right-x
                                         paddle[PLAYER_ONE].dimensions.first;
    paddle_bounding_box[PLAYER_ONE][3] = paddle[PLAYER_ONE].position.second - 0.04 * //bottom-y
                                         paddle[PLAYER_ONE].dimensions.second;

    //calculate bounding box for player two's paddle
    paddle_bounding_box[PLAYER_TWO][0] = paddle[PLAYER_TWO].position.first;          //left-x
    paddle_bounding_box[PLAYER_TWO][1] = paddle[PLAYER_TWO].position.second + 1.04 * //top-y
                                         paddle[PLAYER_TWO].dimensions.second;
    paddle_bounding_box[PLAYER_TWO][2] = paddle[PLAYER_TWO].position.first +         //right-x
                                         paddle[PLAYER_TWO].dimensions.first;
    paddle_bounding_box[PLAYER_TWO][3] = paddle[PLAYER_TWO].position.second - 0.04 * //bottom-y
                                         paddle[PLAYER_TWO].dimensions.second;

    //use ball position(center) and diameter, paddle position(lower left-hand 
    //corner) and dimensions to determine collision.

    //if paddle is moving predict where paddle will be at next step and where
    //ball will be next step. if they would have passed through each other
    //cause collision.
        if((ball_bounding_box[0] <= paddle_bounding_box[PLAYER_ONE][2]) &&
           (ball_bounding_box[3] <= paddle_bounding_box[PLAYER_ONE][1]) &&
           (ball_bounding_box[1] >= paddle_bounding_box[PLAYER_ONE][3]) &&
           (ball_bounding_box[2] >= paddle_bounding_box[PLAYER_ONE][0] + ball.velocity_vector.first))
        {
            ball.velocity_vector.first *= -1;
            ball.position.first = paddle_bounding_box[PLAYER_ONE][2] + ball.diameter;
            applySpin(ball, paddle[PLAYER_ONE]);
            return true;
        }

        if((ball_bounding_box[2] >= paddle_bounding_box[PLAYER_TWO][0]) &&
           (ball_bounding_box[3] <= paddle_bounding_box[PLAYER_TWO][1]) &&
           (ball_bounding_box[1] >= paddle_bounding_box[PLAYER_TWO][3]) &&
           (ball_bounding_box[0] <= paddle_bounding_box[PLAYER_TWO][2] + ball.velocity_vector.first))
        {
            ball.velocity_vector.first *= -1;
            ball.position.first = paddle_bounding_box[PLAYER_TWO][0] - ball.diameter;
            applySpin(ball, paddle[PLAYER_TWO]);
            return true;
        }
    return false;
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

    int spin = 0; //1 = top, -1 = bottom, 0 = middle
    ball.max_velocity = 35;
    //if ball hits top third of paddle make y velocity positive.
    if(ball.position.second >= paddle.position.second +
       (paddle.dimensions.second * 2.0 / 3.0))
    {
        spin = 1;
    } 
    //if ball hits bottom third of paddle make y velocity negative.
    else if(ball.position.second <= paddle.position.second + (paddle.dimensions.second / 3.0))
    {
        spin = -1;
    }
    ///if ball hits middle third of paddle do not change y velocity.
    else
    {
        spin = 0;
    }

    ball.velocity_vector.first += 0.5 * paddle.velocity_vector.first;
    if(ball.velocity_vector.first > ball.max_velocity)
    {
        ball.velocity_vector.first = ball.max_velocity;
    }
    ball.velocity_vector.second += spin * 10 + 0.2 * paddle.velocity_vector.second;
    if(ball.velocity_vector.second > ball.max_velocity)
    {
        ball.velocity_vector.second = ball.max_velocity;
    }

}

 /***************************************************************************//**
 * assignColor
 * Authors - Derek Stotz, Charles Parsons
 *
 * Allows color changes from the globally declared colors.
******************************************************************************/
void assignColor(float value[3], const float color[3])
{
    value[0] = color[0];
    value[1] = color[1];
    value[2] = color[2];
}
