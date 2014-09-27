 /***************************************************************************//**
 * pong.cpp
 * Authors - Derek Stotz, Charles Parsons
 *
 * This file contains functionality for the pong game and drawing the structs
    from structs.h.
 ******************************************************************************/
 #include "pong.h"

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
void drawField(int ScreenWidth, int ScreenHeight)
{
    // set the background color to black
    glClearColor(Black[0], Black[1], Black[2], 1.0f);
    
    // draw a dotted white line in the middle of the screen
    glEnable( GL_LINE_STIPPLE );
    glLineStipple( 1, 0xFF00 );
    DrawLine( 0, -ScreenHeight * 2, 0, ScreenHeight * 2, White );
    
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
void display_practice(Paddle &player_one_paddle, Paddle &cpu_paddle, Ball &ball, int ScreenWidth, int ScreenHeight)
{
    drawField(ScreenWidth, ScreenHeight);
    drawBall(ball);
    drawPaddle(player_one_paddle);
    drawPaddle(cpu_paddle);
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
            ball - the ball on the field
 ******************************************************************************/
void display_game(int player_one_score, int player_two_score, Paddle &player_one_paddle, Paddle &player_two_paddle, Ball &ball, int ScreenWidth, int ScreenHeight)
{
    std::cout << "\nball diameter: " << ball.diameter << "\n";
    std::cout.flush();
    drawField(ScreenWidth, ScreenHeight);
    //drawBall(ball);
    //drawPaddle(player_one_paddle);
    //drawPaddle(player_two_paddle);
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
            DrawStrokeString( menu.options[i].c_str(), x, y + i * spacing, menu.selection_color );
        }
        else
        {
            DrawStrokeString( menu.options[i].c_str(), x, y + i * spacing, menu.text_color );
        }
    }
}


 /***************************************************************************//**
 * Utility Graphics Functions
 ******************************************************************************/
 /***************************************************************************//**
 * DrawStrokeString
 * Authors - Dr. John Weiss
 *
 * Draws a stroke string for a game menu
 ******************************************************************************/
void DrawStrokeString( const char *string, float x, float y, float color[] )
{
    glColor3f( color[0], color[1], color[2] );
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef( x, y, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)string );
    glPopMatrix();
}

 /***************************************************************************//**
 * DrawLine
 * Authors - Dr. John Weiss
 *
 * Draws a stroke string for a game menu
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
