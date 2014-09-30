 /***************************************************************************//**
 * pongGraphics.cpp
 * Authors - Derek Stotz, Charles Parsons
 *
 * This file contains drawing functionaliy for the pong game.
 ******************************************************************************/
 #include "pongGraphics.h"

  /***************************************************************************//**
 * drawBall
 * Authors - Derek Stotz, Charles Parsons
 *
 * Draws a Ball on the screen.
 *
 * Parameters -
            Ball - the ball object to draw
 ******************************************************************************/
void drawBall(Ball &ball)
{
    DrawFilledEllipse( ball.position.first, ball.position.second, ball.diameter/2, ball.diameter/2, ball.color );
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
void drawPaddle(Paddle &paddle)
{
    DrawFilledRectangle( 
        paddle.position.first, 
        paddle.position.second, 
        paddle.position.first+paddle.dimensions.first, 
        paddle.position.second+paddle.dimensions.second, 
        paddle.color );
}

  /***************************************************************************//**
 * drawField
 * Authors - Derek Stotz, Charles Parsons
 *
 * Draws the playing field, including the centre line and scores
 ******************************************************************************/
void drawField(int ScreenWidth, int ScreenHeight, int scores[])
{
    // set the background color to black
    glClearColor(Black[0], Black[1], Black[2], 1.0f);
    
    // draw a dotted white line in the middle of the screen
    glEnable( GL_LINE_STIPPLE );
    glLineStipple( 1, 0xFF00 );
    DrawLine( 0, -ScreenHeight, 0, ScreenHeight, White );

    // draw the field boundaries
    glDisable( GL_LINE_STIPPLE );
    DrawLine(-ScreenWidth, ScreenHeight, ScreenWidth, ScreenHeight, White);
    DrawLine(-ScreenWidth, -ScreenHeight, ScreenWidth, -ScreenHeight, White);
    DrawLine(-ScreenWidth, -ScreenHeight, -ScreenWidth, ScreenHeight, White);
    DrawLine( ScreenWidth, -ScreenHeight, ScreenWidth, ScreenHeight, White);

    // draw each player's score
    float white_set[3] = {White[0], White[1], White[2]};
    if(scores[0] >= 0)
        DrawBitmapString( std::to_string(scores[0]).c_str(), -ScreenWidth / 2, ScreenHeight - 96, white_set );
    if(scores[1] >= 0)
        DrawBitmapString( std::to_string(scores[1]).c_str(), ScreenWidth / 2, ScreenHeight - 96, white_set );
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
void score(player scorer, int player_scores[], int end_score, screen &current_screen)
{
    player_scores[scorer]++;
    
    if( player_scores[scorer] >= end_score)
        current_screen = WIN;
}

  /***************************************************************************//**
 * display_game
 * Authors - Derek Stotz, Charles Parsons
 *
 * Displays the game field
 *
 * Parameters -
            scores - the score to display of players
            player_one_paddle - the paddle under player one's player's control
            ball - the ball on the field
 ******************************************************************************/
void display_game(int scores[], Paddle &player_one_paddle, Paddle &player_two_paddle, Ball &ball, int ScreenWidth, int ScreenHeight)
{
    drawField(ScreenWidth, ScreenHeight, scores);
    drawBall(ball);
    drawPaddle(player_one_paddle);
    drawPaddle(player_two_paddle);
}

  /***************************************************************************//**
 * display_win
 * Authors - Derek Stotz, Charles Parsons
 *
 * Displays the winner of the game on top of a blank field
 *
 * Parameters -
            scores - the scores to show, also determining who wins
 ******************************************************************************/
void display_win(int scores[], int ScreenWidth, int ScreenHeight)
{
    drawField(ScreenWidth, ScreenHeight, scores);
    
    float yellow_set[3] = { Yellow[0], Yellow[1], Yellow[2] };

    if(scores[0] > scores[1])
        DrawBitmapString( "PLAYER 1 WINS", -2*ScreenWidth/3, 0, yellow_set);
    else
        DrawBitmapString( "PLAYER 2 WINS", ScreenWidth/3, 0, yellow_set);
}


  /***************************************************************************//**
 * display_menu
 * Authors - Derek Stotz, Charles Parsons
 *
 * Displays a full menu, including the selected option
 *
 * Parameters
            menu - the menu to display
 ******************************************************************************/
void display_menu( Menu &menu, int x, int y, int spacing )
{
    for(int i = 0; i < menu.n; i++)
    {
        if( menu.selection_index == i )
        {
            DrawBitmapString( menu.options[i].c_str(), x, y + i * spacing, menu.selection_color );
        }
        else
        {
            DrawBitmapString( menu.options[i].c_str(), x, y + i * spacing, menu.text_color );
        }
    }
}


 /***************************************************************************//**
 * Utility Graphics Functions
 ******************************************************************************/
 /***************************************************************************//**
 * DrawBitmapString
 * Authors - Dr. John Weiss
 *
 * Draws a stroke string for a game menu
 ******************************************************************************/
void DrawBitmapString( const char *string, float x, float y, float color[] )
{
    glColor3f( color[0], color[1], color[2] );
    glRasterPos2f( x, y );
    // while ( *string ) glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *string++ );
    glutBitmapString( GLUT_BITMAP_HELVETICA_18, (const unsigned char *)string );
}

 /***************************************************************************//**
 * DrawLine
 * Authors - Dr. John Weiss
 *
 * Draws a line
 ******************************************************************************/
void DrawLine( float x1, float y1, float x2, float y2, const float color[] )
{
    glColor3fv( color );
    glBegin( GL_LINES );
        glVertex2f( x1, y1 );
        glVertex2f( x2, y2 );
    glEnd();
    glFlush();
}

 /***************************************************************************//**
 * DrawFilledEllipse
 * Authors - Dr. John Weiss
 *
 * Draws a filled ellipse
 * Parameters -
    x - the x of the center of the circle
    y - the y of the center of the circle
    xRadius - the radius of the circle on the x axis
    yRadius - the radius of the circle on the y axis
    color - the color to draw the circle
 ******************************************************************************/
void DrawFilledEllipse( float x, float y, float xRadius, float yRadius, float color[] )
{
    float radius = xRadius < yRadius ? xRadius : yRadius;   // stretch circle into ellipse
    glColor3f( color[0], color[1], color[2] );
    glPushMatrix();
    glTranslatef( x, y, 0 );
    glScalef( xRadius / radius, yRadius / radius, 1.0 );    // by ratio of major to minor axes
    GLUquadricObj *disk = gluNewQuadric();
    gluDisk( disk, 0, radius, int( radius ), 1 );
    gluDeleteQuadric( disk );
    glPopMatrix();
}

 /***************************************************************************//**
 * DrawFilledRectangle
 * Authors - Dr. John Weiss
 *
 * Draws a filled rectangle
 * Parameters -
    x1 - the x1 of the rectangle
    y1 - the y1 of the rectangle
    x2 - the x2 of the rectangle
    y2 - the y2 of thoe rectangle
    color - the color to draw the rectangle
 ******************************************************************************/
void DrawFilledRectangle( float x1, float y1, float x2, float y2, float color[] )
{
    glColor3f( color[0], color[1], color[2] );
    glRectf( x1, y1, x2, y2 );
}
