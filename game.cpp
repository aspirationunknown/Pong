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

// keyboard press flags
bool up_pressed;
bool down_pressed;
bool left_pressed;
bool right_pressed;

bool w_pressed;
bool s_pressed;
bool a_pressed;
bool d_pressed;

bool enter_pressed;
bool escape_pressed;
bool shift_pressed;

// splashscreen info
const char* splashscreen_filepath = "./resources/splashscreen.bmp"; 
int splashscreen_cols = 640;
int splashscreen_rows = 256;
byte* splashscreen_image;

// opening the readme
const char* open_readme_command = "xdg-open README";
const char* focus_readme_command = "wmctrl -a README";
//const char* open_readme_command = "notepad.exe README";

// screen state
screen current_screen = MAINMENU;
screen resume_screen = MAINMENU;
int ScreenWidth = 1280;
int ScreenHeight = 512;

int FieldWidth = 1280;
int FieldHeight = 512;

// world coordinate window extents: -1000 to +1000 in smaller dimension
const float ViewplaneSize = 1000.0;

// the global variables associated with the game
int player_scores[2] = { 0, 0 };
Ball game_ball;
Paddle player_paddles[2];
int end_score = 10;    // the score at which a player wins the game
int fps = 60;
int turn = 1; // 1 is serve right, -1 is serve left

// function prototypes
void initOpenGL( void );
void mainMenuSetup( void );
void pauseMenuSetup( void );
void pauseMenu_resume( void );
void gameSetup( void );
void display( void );
void step( int value);
void display_splashscreen( void );
void reshape( int w, int h );
void keyboard_up( unsigned char key, int x, int y );
void keyboard_down( unsigned char key, int x, int y );
void special_up( int key, int x, int y );
void special_down( int key, int x, int y );

// step functions
void menu_step(Menu &menu);
void practice_step();
void game_step();

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
    mainMenuSetup();
    glutInit(&argc, argv);
    initOpenGL();
    glutMainLoop();    

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
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );     // 32-bit graphics and double buffering

    glutInitWindowSize( ScreenWidth, ScreenHeight );    // initial window size
    glutInitWindowPosition( 100, 50 );                  // initial window position
    glutCreateWindow( "Pong" );                  // window title

    glutIgnoreKeyRepeat(1); // ignore repeated key presses
    glutKeyboardUpFunc( keyboard_up );
    glutKeyboardFunc( keyboard_down );
    glutSpecialUpFunc( special_up );
    glutSpecialFunc( special_down );

    glClearColor( 0.0, 0.0, 0.0, 1.0 );                 // use black for glClear command
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutTimerFunc( 1000/fps, step, 0 );
}


void step ( int value )
{
    
    if( escape_pressed && current_screen != PAUSE)
    {
        resume_screen = current_screen;
        current_screen = PAUSE;
        escape_pressed = false;
    }

    switch(current_screen)
    {
        case MAINMENU:
            menu_step( main_menu );
            break;
        case PRACTICE:
            practice_step();
            break;
        case GAME:
            game_step();
            break;
        case PAUSE:
            menu_step(pause_menu);
        default:
            break;
    }
    glutPostRedisplay();
    glutTimerFunc( 1000/fps, step, 0 );
}

 /***************************************************************************//**
 * displayImage
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
    glClear( GL_COLOR_BUFFER_BIT );
    switch( current_screen )
    {
        case MAINMENU:
            display_splashscreen();
            display_menu(main_menu, 0, -ScreenHeight, 128);
            break;
        case PRACTICE:
            display_practice(player_paddles[0], player_paddles[1], game_ball, ScreenWidth, ScreenHeight);
            break;
        case GAME:
            display_game(player_scores, player_paddles[0], player_paddles[1], game_ball, ScreenWidth, ScreenHeight);
            break;
        case PAUSE:
            display_menu(pause_menu, 0, -ScreenHeight, 128);
        default:
            break;
    }

    glutSwapBuffers();
    glFlush();

}

 /***************************************************************************//**
 * display_splashscreen
 * Authors - Derek Stotz, Charles Parsons
 *
 * The display function for the splashscreen screen, called in the display function
 ******************************************************************************/
void display_splashscreen()
{
    displayImage(-1 * ScreenWidth, 0, splashscreen_cols, splashscreen_rows, splashscreen_image );
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
    FieldWidth = w * 1.5;
    FieldHeight = h * 1.5;

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

 /***************************************************************************//**
 * Pause Menu Functions
 ******************************************************************************/
/***************************************************************************//**
 * pauseMenu_mainMenu
 * Authors - Derek Stotz, Charles Parsons
 *
 * Goes to the main menu
 ******************************************************************************/
void pauseMenu_mainMenu( void )
{
    current_screen = MAINMENU;
}

 /***************************************************************************//**
 * pauseMenu_restart
 * Authors - Derek Stotz, Charles Parsons
 *
 * Restarts the current game
 ******************************************************************************/
void pauseMenu_restart( void )
{
    gameSetup();
    pauseMenu_resume();
}

 /***************************************************************************//**
 * pauseMenu_resume
 * Authors - Derek Stotz, Charles Parsons
 *
 * Resumes the game
 ******************************************************************************/
void pauseMenu_resume( void )
{
    current_screen = resume_screen;
}


 /***************************************************************************//**
 * Main Menu Functions
 ******************************************************************************/

 /***************************************************************************//**
 * mainMenu_newGame
 * Authors - Derek Stotz, Charles Parsons
 *
 * Starts a new two-player game
 ******************************************************************************/
void mainMenu_newGame( void )
{
    gameSetup();
    pauseMenuSetup();
    current_screen = GAME;
}

 /***************************************************************************//**
 * mainMenu_newGame
 * Authors - Derek Stotz, Charles Parsons
 *
 * Starts a new one-player practice game
 ******************************************************************************/
void mainMenu_practice( void )
{
    gameSetup();
    current_screen = PRACTICE;
}

 /***************************************************************************//**
 * mainMenu_newGame
 * Authors - Derek Stotz, Charles Parsons
 *
 * Opens the readme
 ******************************************************************************/
void mainMenu_about( void )
{
    system(open_readme_command);
    system(focus_readme_command);
}

 /***************************************************************************//**
 * mainMenu_newGame
 * Authors - Derek Stotz, Charles Parsons
 *
 * Exits the application
 ******************************************************************************/
void mainMenu_exit( void )
{
    glutLeaveMainLoop();
}

 /***************************************************************************//**
 * mainMenuSetup
 * Authors - Derek Stotz, Charles Parsons
 *
 * Sets up the Main Menu properties and callback functions
 ******************************************************************************/
void mainMenuSetup()
{
    main_menu.options[0] = "Exit";
    main_menu.options[1] = "About";
    main_menu.options[2] = "Practice";
    main_menu.options[3] = "New Game";

    main_menu.option_actions[0] = mainMenu_exit;
    main_menu.option_actions[1] = mainMenu_about;
    main_menu.option_actions[2] = mainMenu_practice;
    main_menu.option_actions[3] = mainMenu_newGame;

    assignColor(main_menu.background_color, Black);
    assignColor(main_menu.text_color, White);
    assignColor(main_menu.selection_color, Yellow);

    main_menu.selection_index = 3;
    main_menu.n = 4;
}

 /***************************************************************************//**
 * pauseMenuSetup
 * Authors - Derek Stotz, Charles Parsons
 *
 * Sets up the Main Menu properties and callback functions
 ******************************************************************************/
void pauseMenuSetup()
{
    pause_menu.options[0] = "Exit";
    pause_menu.options[1] = "Main Menu";
    pause_menu.options[2] = "Restart";
    pause_menu.options[3] = "Resume";

    pause_menu.option_actions[0] = mainMenu_exit;
    pause_menu.option_actions[1] = pauseMenu_mainMenu;
    pause_menu.option_actions[2] = pauseMenu_restart;
    pause_menu.option_actions[3] = pauseMenu_resume;

    assignColor(pause_menu.background_color, Black);
    assignColor(pause_menu.text_color, White);
    assignColor(pause_menu.selection_color, Yellow);

    pause_menu.selection_index = 3;
    pause_menu.n = 4;
}


 /***************************************************************************//**
 * gameSetup
 * Authors - Derek Stotz, Charles Parsons
 *
 * Sets up the Game objects
 ******************************************************************************/
void gameSetup()
{
    game_ball.position.first = 0;
    game_ball.position.second = 0;
    game_ball.diameter = 64;
    game_ball.velocity_vector.first = 20 * turn;
    turn *= -1;  //change serving turn
    assignColor(game_ball.color, White);
    
    player_paddles[0].dimensions.first = 40;
    player_paddles[0].dimensions.second = 300;
    player_paddles[0].movement_speed.first = 15;
    player_paddles[0].movement_speed.second = 20;
    player_paddles[0].position.first = -ScreenWidth + 64 + player_paddles[0].dimensions.first;
    player_paddles[0].position.second = 0 - player_paddles[0].dimensions.second/2;
    assignColor(player_paddles[0].color, White);

    player_paddles[1].dimensions.first = 40;
    player_paddles[1].dimensions.second = 300;
    player_paddles[1].movement_speed.first = 15;
    player_paddles[1].movement_speed.second = 20;
    player_paddles[1].position.first = ScreenWidth - 64 - player_paddles[1].dimensions.first;
    player_paddles[1].position.second = 0 - player_paddles[1].dimensions.second/2;
    assignColor(player_paddles[1].color, White);
}

 /***************************************************************************//**
 * keyboard_down
 * Authors - Derek Stotz, Charles Parsons
 *
 * handles key press events
 ******************************************************************************/
void keyboard_down( unsigned char key, int x, int y )
{
    switch( key )
    {
        case 'w':
            w_pressed = true;
            break;
        case 's':
            s_pressed = true;
            break;
        case 'a':
            a_pressed = true;
            break;
        case 'd':
            d_pressed = true;
            break;
        case 13:
            enter_pressed = true;
            break;
        case 27:
            escape_pressed = true;
        default:
            break;
    }
}

 /***************************************************************************//**
 * keyboard_up
 * Authors - Derek Stotz, Charles Parsons
 *
 * handles key release events
 ******************************************************************************/
void keyboard_up( unsigned char key, int x, int y )
{
    switch( key )
    {
        case 'w':
            w_pressed = false;
            break;
        case 's':
            s_pressed = false;
            break;
        case 'a':
            a_pressed = false;
            break;
        case 'd':
            d_pressed = false;
            break;
        case '\n':
            enter_pressed = false;
            break;
        case 27:
            escape_pressed = false;
        default:
            break;
    }
}

 /***************************************************************************//**
 * special_down
 * Authors - Derek Stotz, Charles Parsons
 *
 * handles key press events for arrow keys
 ******************************************************************************/
void special_down( int key, int x, int y )
{
    switch( key )
    {
        case GLUT_KEY_UP:
            up_pressed = true;
            break;
        case GLUT_KEY_DOWN:
            down_pressed = true;
            break;
        case GLUT_KEY_LEFT:
            left_pressed = true;
            break;
        case GLUT_KEY_RIGHT:
            right_pressed = true;
        default:
            break;
    }
}

 /***************************************************************************//**
 * special_up
 * Authors - Derek Stotz, Charles Parsons
 *
 * handles key release events for special keys
 ******************************************************************************/
void special_up( int key, int x, int y )
{
    switch( key )
    {
        case GLUT_KEY_UP:
            up_pressed = false;
            break;
        case GLUT_KEY_DOWN:
            down_pressed = false;
            break;
        case GLUT_KEY_LEFT:
            left_pressed = false;
            break;
        case GLUT_KEY_RIGHT:
            right_pressed = false;
        default:
            break;
    }
}


 /***************************************************************************//**
 * Menu Step
 * Authors - Dr. John Weiss
 *
 * Does a step in a given menu, moves the selector and fires the callback
        functions if necessary
 * 
 * Parameters -
        menu - the menu to step through
 ******************************************************************************/
void menu_step(Menu &menu)
{
    if( down_pressed )
    {
        if (menu.selection_index == 0)
        {
            menu.selection_index = menu.n - 1;
            down_pressed = false;
        }
        else
        {
            menu.selection_index -= 1;
            down_pressed = false;
        }
    }
    else if ( up_pressed )
    {
        up_pressed = false;
        menu.selection_index = (menu.selection_index + 1 ) % menu.n;
    }
    else if ( enter_pressed )
    {
        enter_pressed = false;
        menu.option_actions[menu.selection_index]();
    }
}

 /***************************************************************************//**
 * DrawStrokeString
 * Authors - Dr. John Weiss
 *
 * Does a step in the practice game, telling what parts of the game's state
        need to change.
 ******************************************************************************/
void practice_step()
{
   // horizontal movement player 1
   if( a_pressed && d_pressed )
        player_paddles[0].velocity_vector.first = 0;
   else if( a_pressed )
        player_paddles[0].velocity_vector.first = -1 * player_paddles[0].movement_speed.first;
   else if( d_pressed )
        player_paddles[0].velocity_vector.first = player_paddles[0].movement_speed.first;
   else
        player_paddles[0].velocity_vector.first /= 2;

   // horizontal movement player 1
   if( s_pressed && w_pressed )
        player_paddles[0].velocity_vector.second = 0;
   else if( s_pressed )
        player_paddles[0].velocity_vector.second = -1 * player_paddles[0].movement_speed.second;
   else if( w_pressed )
        player_paddles[0].velocity_vector.second = player_paddles[0].movement_speed.second;
   else
        player_paddles[0].velocity_vector.second /= 2;

   // apply velocity
   player_paddles[0].position.first += player_paddles[0].velocity_vector.first;
   player_paddles[0].position.second += player_paddles[0].velocity_vector.second;
   player_paddles[1].position.second = game_ball.position.second - (player_paddles[1].dimensions.second / 2);    
}

 /***************************************************************************//**
 * Game Step
 * Authors - Dr. John Weiss
 *
 * Does a step in the main game, telling what parts of the game's state
        need to change.
 ******************************************************************************/
void game_step()
{
   // horizontal movement player 1
   if( a_pressed && d_pressed )
        player_paddles[0].velocity_vector.first = 0;
   else if( a_pressed )
        player_paddles[0].velocity_vector.first = -1 * player_paddles[0].movement_speed.first;
   else if( d_pressed )
        player_paddles[0].velocity_vector.first = player_paddles[0].movement_speed.first;
   else
        player_paddles[0].velocity_vector.first /= 1.2;

   // horizontal movement player 1
   if( s_pressed && w_pressed )
        player_paddles[0].velocity_vector.second = 0;
   else if( s_pressed )
        player_paddles[0].velocity_vector.second = -1 * player_paddles[0].movement_speed.second;
   else if( w_pressed )
        player_paddles[0].velocity_vector.second = player_paddles[0].movement_speed.second;
   else
        player_paddles[0].velocity_vector.second /= 1.2;

   // horizontal movement player 2
   if( left_pressed && right_pressed )
        player_paddles[1].velocity_vector.first = 0;
   else if( left_pressed )
        player_paddles[1].velocity_vector.first = -1 * player_paddles[1].movement_speed.first;
   else if( right_pressed )
        player_paddles[1].velocity_vector.first = player_paddles[1].movement_speed.first;
   else
        player_paddles[1].velocity_vector.first /= 1.2;

   // horizontal movement player 2
   if( down_pressed && up_pressed )
        player_paddles[1].velocity_vector.second = 0;
   else if( down_pressed )
        player_paddles[1].velocity_vector.second = -1 * player_paddles[1].movement_speed.second;
   else if( up_pressed )
        player_paddles[1].velocity_vector.second = player_paddles[1].movement_speed.second;
   else
        player_paddles[1].velocity_vector.second /= 1.2;

   // apply velocity
   
   int nextcoord = player_paddles[0].position.first + player_paddles[0].velocity_vector.first;
   if( nextcoord <  -player_paddles[1].dimensions.first && nextcoord > -FieldWidth)
       player_paddles[0].position.first += player_paddles[0].velocity_vector.first;

   nextcoord = player_paddles[1].position.first + player_paddles[1].velocity_vector.first;
   if( nextcoord <  FieldWidth - player_paddles[1].dimensions.first && nextcoord > 0)
       player_paddles[1].position.first += player_paddles[1].velocity_vector.first;

   nextcoord = player_paddles[0].position.second + player_paddles[0].velocity_vector.second;
   if( nextcoord <  FieldHeight - player_paddles[1].dimensions.second && nextcoord > -FieldHeight)
       player_paddles[0].position.second += player_paddles[0].velocity_vector.second;

   nextcoord = player_paddles[1].position.second + player_paddles[1].velocity_vector.second;
   if( nextcoord <  FieldHeight - player_paddles[1].dimensions.second && nextcoord > -FieldHeight)
       player_paddles[1].position.second += player_paddles[1].velocity_vector.second;
  
   nextcoord = game_ball.position.second + game_ball.velocity_vector.second;
   if( nextcoord <  FieldHeight && nextcoord > -FieldHeight)
       game_ball.position.second += game_ball.velocity_vector.second;
   else
       game_ball.velocity_vector.second *= -1;

   nextcoord = game_ball.position.first + game_ball.velocity_vector.first;
   if( nextcoord <  FieldHeight && nextcoord > -FieldHeight)
       game_ball.position.first += game_ball.velocity_vector.first;
   else
       score(PLAYER_ONE, player_scores, end_score);
   

   // collisions
   applyCollision(game_ball, player_paddles);
}
