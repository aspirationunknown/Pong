/***************************************************************************//**
 * game.cpp
 *
 * Assignment - PA 1 - Pong
 *
 * Authors - Derek Stotz, Charles Parsons
 *
 * Date - September 30, 2014
 *
 * Instructor - Dr. Weiss
 *
 * Course - CSC 433
 *
 * Location - McLaury - Room 313
 *
 *
 * Usage - 
            To Compile: make pong
            Usage: pong
            
 * Details -
            This application contains a two-player pong game.
 *
 * Issues and Bugs - 
            No bugs to speak of.
 *
 ******************************************************************************/
#include "pong.h"

using namespace std;

Menu main_menu;
Menu pause_menu;

// splashscreen info
const char* splashscreen_filepath = "./resources/splashscreen.bmp"; 
int splashscreen_cols = 640;
int splashscreen_rows = 256;
byte* splashscreen_image;

// screen state
screen current_screen = SPLASHSCREEN;
screen resume_screen = SPLASHSCREEN;
int ScreenWidth = 640;
int ScreenHeight = 256;

// world coordinate window extents: -1000 to +1000 in smaller dimension
const float ViewplaneSize = 1000.0;

// the global variables associated with the game
int player_scores[2] = { 0, 0 };
Ball game_ball;
Paddle player_paddles[2];
int end_score = 10;    // the score at which a player wins the game

// function prototypes
void initOpenGL( void );
void splashScreenSetup( void );
void mainMenuSetup( void );
void display( void );
void display_splashscreen( void );
void reshape( int w, int h );

// functions by Dr. Weiss, for loading and displaying bmp files
bool LoadBmpFile( const char* filename, int &NumRows, int &NumCols, unsigned char* &ImagePtr );
void displayImage( int x, int y, int w, int h, byte *image );
 
 /***************************************************************************//**
 * main
 * Authors - Derek Stotz, Charles Parsons
 *
 * The entry point of the pong game.  Sets up the menus and begins Pong.
 *
 * Parameters - 
            argc - the number of arguments from the command prompt.
            argv - the command line arguments.
 ******************************************************************************/
int main ( int argc, char *argv[] )
{
    //load the splash screen
    if ( !LoadBmpFile( splashscreen_filepath, splashscreen_rows, splashscreen_cols, splashscreen_image ) )
    {
	cerr << "Error: unable to load file " << splashscreen_filepath << endl;
        return -1;
    }

    //start displaying
    initOpenGL();
    splashScreenSetup();

    //splash screen spins until a key is pressed
    mainMenuSetup();
    return 0;
}


 /***************************************************************************//**
 * initOpenGL
 * Authors - Derek Stotz, Charles Parsons
 *
 * Sets up OpenGL and creates the main window.
 ******************************************************************************/
void initOpenGL( void )
{
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );     // 32-bit graphics and single buffering

    glutInitWindowSize( 640, 256 );    // initial window size
    glutInitWindowPosition( 100, 50 );                  // initial window position
    glutCreateWindow( "Pong" );                  // window title

    glClearColor( 0.0, 0.0, 0.0, 1.0 );                 // use black for glClear command
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
}

 /***************************************************************************//**
 * mainMenuSetup
 * Authors - Derek Stotz, Charles Parsons
 *
 * Sets up the callbacks for drawing and using the main menu.
 ******************************************************************************/
void mainMenuSetup( void )
{

}

 /***************************************************************************//**
 * mainMenuSetup
 * Authors - Dr. John Weiss
 *
 * Displays an image through the glDrawPixels method
 ******************************************************************************/
void displayImage( int x, int y, int w, int h, byte *image )
{
    glRasterPos2i( x, y );
    glDrawPixels( w, h, GL_RGB, GL_UNSIGNED_BYTE, image );
}

 /***************************************************************************//**
 * display
 * Authors - Derek Stotz, Charles Parsons
 *
 * The display callback, taking into account the current screen
 ******************************************************************************/
void display( void )
{
    switch( current_screen )
    {
        case SPLASHSCREEN:
            display_splashscreen();
        case MAINMENU:
            display_menu(main_menu);
        case PRACTICE:
            display_practice(player_paddles[0], player_paddles[1], game_ball);
        case GAME:
            display_game(player_scores[0], player_scores[1], player_paddles[0], player_paddles[1], game_ball);
        case PAUSE:
            display_menu(pause_menu);
        default: return;
    }
}

 /***************************************************************************//**
 * display_splashscreen
 * Authors - Derek Stotz, Charles Parsons
 *
 * The display function for the splashscreen screen, called in the display function
 ******************************************************************************/
void display_splashscreen()
{
    displayImage(0, 0, splashscreen_cols, splashscreen_rows, splashscreen_image );
}

 /***************************************************************************//**
 * reshape
 * Authors - Dr. John Weiss
 *
 * The callback function which reshapes the window
 ******************************************************************************/
void reshape( int w, int h )
{
    // store new window dimensions globally
    ScreenWidth = w;
    ScreenHeight = h;

    // orthographic projection of 3-D scene onto 2-D, maintaining aspect ratio
    glMatrixMode( GL_PROJECTION );      // use an orthographic projection
    glLoadIdentity();                   // initialize transformation matrix
    if ( w > h )                        // use width:height aspect ratio to specify view extents
        gluOrtho2D( -ViewplaneSize * w / h, ViewplaneSize * w / h, -ViewplaneSize, ViewplaneSize );
    else
        gluOrtho2D( -ViewplaneSize, ViewplaneSize, -ViewplaneSize * h / w, ViewplaneSize * h / w );
    glViewport( 0, 0, w, h );           // adjust viewport to new window

    // switch back to (default) model view mode, for transformations
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}
