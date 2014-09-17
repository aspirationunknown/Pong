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

Menu mainMenu;
Menu pauseMenu;

// function prototypes
void initOpenGL( void );
void splashScreenSetup( void );
void mainMenuSetup( void );
 
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
}

 /***************************************************************************//**
 * splashScreenSetup
 * Authors - Derek Stotz, Charles Parsons
 *
 * Sets up the callbacks and drawn image used in the splash screen.
 ******************************************************************************/
void splashScreenSetup( void )
{

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