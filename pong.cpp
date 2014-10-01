/***************************************************************************//**
 * pong.cpp
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
            To Compile: make
            To Run: ./pong

            This application contains a two-player pong game and a single-player
            practice game.  The game opens on a main menu with a Pong graphic on
            the left, and options on the right which the player can cycle through
            using the arrow keys.

            When an options on the menu is selected with enter, the user enters
            a new screen.  On "New Game" the screen changes immediately to a
            two-player game.  On "Practice" the screen transitions to a
            difficulty selection screen, where the player can select a CPU
            difficulty level in a similar fasion to the main menu's options.
            On "About", the readme is opened in a text editor, and on "Exit"
            the game quits.

            
            
 * Details -  
            
 *
 * Issues and Bugs - 
            No bugs to speak of.
 *
 ******************************************************************************/
#include "pongGraphics.h"
#include <cmath>


using namespace std;

Menu main_menu;
Menu pause_menu;
Menu practice_menu;

// keyboard press flags
bool up_pressed = false;
bool down_pressed = false;
bool left_pressed = false;
bool right_pressed = false;

bool minus_pressed = false;
bool plus_pressed = false;

bool w_pressed = false;
bool s_pressed = false;
bool a_pressed = false;
bool d_pressed = false;

bool enter_pressed = false;
bool space_pressed = false;
bool shift_pressed = false;

// splashscreen info
const char* splashscreen_filepath = "./resources/splashscreen.bmp"; 
int splashscreen_cols = 640;
int splashscreen_rows = 256;
byte* splashscreen_image;

// opening the readme
const char* open_readme_command = "xdg-open README";
const char* open_readme_command_win = "notepad.exe README";
const char* open_readme_command_gedit = "gedit README";

//shrinking the game window to view the readme
const char* shrink_game_command = "wmctrl -a ";

// screen state
screen current_screen = MAINMENU;
screen resume_screen = MAINMENU;
int ScreenWidth = 1280;
int ScreenHeight = 512;

// the global variables associated with the game
int player_scores[2] = { 0, 0 };
Ball game_ball;
Paddle player_paddles[2];
int end_score = 10;    // the score at which a player wins the game
int fps = 60;
int turn = 1; // 1 is serve right, -1 is serve left

int full_paddlesize = 150; // the starting size of the paddle
double paddle_scale = 1.0; // for shrinking the paddle over time
double paddle_scalemin = .20; // the smallest possible paddle size multiplier
double paddle_scalespeed = .01; // the amount the paddle is shrunk by every step

// cpu control

int cpu_returning = false;
int cpu_offset;
int cpu_direction = 1; // -1 is down, 1 is up
int cpu_offset_max; // the maximum offset.  It must be greater than the paddle height / 2
float cpu_difficulty = 1.2; // the amount of space the cpu paddle can be off by.  1 will never miss, while increasing values are easier.

// function prototypes
void initOpenGL( void );
void mainMenuSetup( void );
void pauseMenuSetup( void );
void practiceMenuSetup( void );
void pauseMenu_resume( void );
void practiceSetup( void );
void gameSetup( void );
void display( void );
void step( int value);
void reshape( int w, int h );
void keyboard_up( unsigned char key, int x, int y );
void keyboard_down( unsigned char key, int x, int y );
void special_up( int key, int x, int y );
void special_down( int key, int x, int y );
void ballSpeedupCheck( void );

// step functions
void menu_step(Menu &menu);
void practice_step();
void game_step();
void shared_step();

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


 /***************************************************************************//**
 * step
 * Authors - Derek Stotz, Charles Parsons
 *
 * Does a step in the game, handled differently depending on which screen is active
 * 
 * Parameters - 
    value - an unused integer passed by glutTimerFunc
 ******************************************************************************/
void step ( int value )
{
    switch( current_screen )
    {
        case MAINMENU:
            menu_step( main_menu );
            break;
        case PRACTICEMENU:
            menu_step( practice_menu );
            break;
        case PRACTICE:
            practice_step();
            break;
        case GAME:
            game_step();
            break;
        case PAUSE:
            if( space_pressed )
            {
                space_pressed = false;
                pauseMenu_resume();
            }
            menu_step(pause_menu);
            break;
        case WIN:
            if (space_pressed || enter_pressed)
            {
                space_pressed = false;
                enter_pressed = false;
                current_screen = MAINMENU;
            }
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
 *
 * Parameters - 
    x - the x position to draw the image at
    y - the y position to draw the image at
    w - the width to draw the image
    h - the height to draw the image
    image - a byte array holidng image information
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
        case PRACTICEMENU:
            //display the spashscreen
            displayImage(-1 * ScreenWidth, 0, splashscreen_cols, splashscreen_rows, splashscreen_image );
            display_menu(practice_menu, 0, 0, 96);
            break;
        case MAINMENU:
            //display the spashscreen
            displayImage(-1 * ScreenWidth, 0, splashscreen_cols, splashscreen_rows, splashscreen_image );
            display_menu(main_menu, 0, 0, 96);
            break;
        case PRACTICE:
            display_game(player_scores, player_paddles[0], player_paddles[1], game_ball, ScreenWidth, ScreenHeight);
            break;
        case GAME:
            display_game(player_scores, player_paddles[0], player_paddles[1], game_ball, ScreenWidth, ScreenHeight);
            break;
        case PAUSE:
            display_menu(pause_menu, 0, 0, 96);
            break;
        case WIN:
            display_win(player_scores, ScreenWidth, ScreenHeight);
        default:
            break;
    }

    glutSwapBuffers();
    glFlush();

}

 /***************************************************************************//**
 * reshape
 * Authors - Dr. John Weiss
 *
 * The callback function which reshapes the window
 *
 * Parameters -
    w - the width of the screen
    h - the height of the screen
 ******************************************************************************/
void reshape( int w, int h )
{
    // orthographic projection of 3-D scene onto 2-D, maintaining aspect ratio
    glMatrixMode( GL_PROJECTION );      // use an orthographic projection
    glLoadIdentity();                   // initialize transformation matrix
    if ( w > h )                        // use width:height aspect ratio to specify view extents
        gluOrtho2D( - ScreenWidth, ScreenWidth, - ScreenHeight, ScreenHeight );
    else
        gluOrtho2D( - ScreenWidth, ScreenWidth, -ScreenHeight, ScreenHeight );
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
    pauseMenuSetup();
    practiceMenuSetup();
    current_screen = PRACTICEMENU;
}

 /***************************************************************************//**
 * mainMenu_newGame
 * Authors - Derek Stotz, Charles Parsons
 *
 * Opens the readme in gedit (or the default editor, or notepad if in windows)
 ******************************************************************************/
void mainMenu_about( void )
{
    if(system(open_readme_command_gedit) != 0)
        if( system(open_readme_command) != 0)
            system(open_readme_command_win );  // well, if the default linux editor fails to launch, we're probably in windows.
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

    main_menu.option_actions[0] = glutLeaveMainLoop;
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
 * practiceMenuSetup
 * Authors - Derek Stotz, Charles Parsons
 *
 * Sets up the Main Menu properties and callback functions
 ******************************************************************************/
void practiceMenuSetup()
{
    practice_menu.options[0] = "Cruel";
    practice_menu.options[1] = "Hard";
    practice_menu.options[2] = "Medium";
    practice_menu.options[3] = "Easy";

    // lambda functions for the menu options
    practice_menu.option_actions[0] = [] () { 
        cpu_difficulty = 1.5; player_paddles[1].movement_speed.second = 10; practiceSetup(); current_screen = PRACTICE; };
    practice_menu.option_actions[1] = [] () { 
        cpu_difficulty = 2.5; player_paddles[1].movement_speed.second = 3; practiceSetup(); current_screen = PRACTICE; };
    practice_menu.option_actions[2] = [] () {
        cpu_difficulty = 4.0; player_paddles[1].movement_speed.second = 1; practiceSetup(); current_screen = PRACTICE; };
    practice_menu.option_actions[3] = [] () {
        cpu_difficulty = 7.0; player_paddles[1].movement_speed.second = 0; practiceSetup(); current_screen = PRACTICE; };

    assignColor(practice_menu.background_color, Black);
    assignColor(practice_menu.text_color, White);
    assignColor(practice_menu.selection_color, Yellow);

    practice_menu.selection_index = 3;
    practice_menu.n = 4;
}

 /***************************************************************************//**
 * pauseMenuSetup
 * Authors - Derek Stotz, Charles Parsons
 *
 * Sets up the Pause Menu properties and callback functions
 ******************************************************************************/
void pauseMenuSetup()
{
    pause_menu.options[0] = "Exit";
    pause_menu.options[1] = "Main Menu";
    pause_menu.options[2] = "Restart";
    pause_menu.options[3] = "Resume";

    pause_menu.option_actions[0] = glutLeaveMainLoop;
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
    end_score = 10;
    paddle_scale = 1.0;

    player_scores[0] = 0;
    player_scores[1] = 0;

    // game ball information
    game_ball.max_velocity = 30;
    game_ball.position.first = 0;
    game_ball.position.second = 0;
    game_ball.diameter = 16;
    game_ball.velocity_vector.first = 15 * turn;
    turn *= -1;  // change serving turn
    assignColor(game_ball.color, White);
    
    // set the player 1 paddle information
    player_paddles[0].dimensions.first = 20;
    player_paddles[0].dimensions.second = full_paddlesize;
    player_paddles[0].movement_speed.first = 10;
    player_paddles[0].movement_speed.second = 15;
    player_paddles[0].position.first = -ScreenWidth + player_paddles[0].dimensions.first;
    player_paddles[0].position.second = 0 - player_paddles[0].dimensions.second/2;
    assignColor(player_paddles[0].color, White);

    // set the player 2 paddle information
    player_paddles[1].dimensions.first = 20;
    player_paddles[1].dimensions.second = full_paddlesize;
    player_paddles[1].movement_speed.first = 10;
    player_paddles[1].movement_speed.second = 15;
    player_paddles[1].position.first = ScreenWidth - player_paddles[1].dimensions.first;
    player_paddles[1].position.second = 0 - player_paddles[1].dimensions.second/2;
    assignColor(player_paddles[1].color, White);
}


 /***************************************************************************//**
 * practiceSetup
 * Authors - Derek Stotz, Charles Parsons
 *
 * Sets up the practice-specific objects
 ******************************************************************************/
void practiceSetup()
{
    cpu_returning = false;
    cpu_offset = 0;
    cpu_offset_max = player_paddles[1].dimensions.second / 2 + cpu_difficulty * game_ball.diameter;
    player_paddles[1].position.first -= 128;
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
        case '-':
            minus_pressed = true;
            break;
        case '=':
        case '+':
            plus_pressed =  true;
            break;
        case 'w':
        case 'W':
            w_pressed = true;
            break;
        case 's':
        case 'S':
            s_pressed = true;
            break;
        case 'a':
        case 'A':
            a_pressed = true;
            break;
        case 'd':
        case 'D':
            d_pressed = true;
            break;
        case 13:
            enter_pressed = true;
            break;
        case ' ':
            space_pressed = true;
            break;
        case 27:
            exit ( 0 );
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
        case '-':
            minus_pressed = false;
            break;
        case '+':
        case '=':
            plus_pressed = false;
            break;
        case 'w':
        case 'W':
            w_pressed = false;
            break;
        case 's':
        case 'S':
            s_pressed = false;
            break;
        case 'a':
        case 'A':
            a_pressed = false;
            break;
        case 'd':
        case 'D':
            d_pressed = false;
            break;
        case '\n':
            enter_pressed = false;
            break;
        case ' ':
            space_pressed = false;
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
 * Authors - Derek Stotz, Charles Parsons
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
 * practice_step
 * Authors - Derek Stotz, Charles Parsons
 *
 * Does a step in the practice game, telling what parts of the game's state
        need to change.
 ******************************************************************************/
void practice_step()
{
    shared_step();

    // if the paddle is "returning", just move it towards the start
    if( cpu_returning && abs((game_ball.position.second) - (player_paddles[1].position.second + player_paddles[1].dimensions.second/2.0)) > 16 )
    {
        cpu_offset = 0.0;
        if(game_ball.position.second > player_paddles[1].position.second + player_paddles[1].dimensions.second/2)
            player_paddles[1].position.second += 15;
        else
            player_paddles[1].position.second -= 15;
    }
    else
    {
        cpu_returning = false;

        // move the cpu paddle
        player_paddles[1].position.second = game_ball.position.second - player_paddles[1].dimensions.second / 2 + cpu_offset;

        // change the CPU's paddle offset

        // change direction if the max will be reached
        if (abs(cpu_offset + cpu_direction) > cpu_offset_max)
            cpu_direction *= -1;
        cpu_offset += cpu_direction;
        player_paddles[1].velocity_vector.second = player_paddles[1].movement_speed.second * cpu_direction;

        // make sure the cpu paddle is not past the bounds
        int nextcoord = player_paddles[1].position.second;

        if( nextcoord >  ScreenHeight - player_paddles[1].dimensions.second)
            player_paddles[1].position.second = ScreenHeight- player_paddles[1].dimensions.second;
        else if(nextcoord < -ScreenHeight)
            player_paddles[1].position.second = -ScreenHeight;
    }
}

 /***************************************************************************//**
 * Game Step
 * Authors - Derek Stotz, Charles Parsons
 *
 * Does a step in the main game, telling what parts of the game's state
        need to change.
 ******************************************************************************/
void game_step()
{
    shared_step();

    // horizontal movement player 2
    if( left_pressed && right_pressed )
         player_paddles[1].velocity_vector.first = 0;
    else if( left_pressed )
         player_paddles[1].velocity_vector.first = -1 * player_paddles[1].movement_speed.first;
    else if( right_pressed )
         player_paddles[1].velocity_vector.first = player_paddles[1].movement_speed.first;
    else
         player_paddles[1].velocity_vector.first /= 1.2;

    // vertical movement player 2
    if( down_pressed && up_pressed )
         player_paddles[1].velocity_vector.second = 0;
    else if( down_pressed )
         player_paddles[1].velocity_vector.second = -1 * player_paddles[1].movement_speed.second;
    else if( up_pressed )
         player_paddles[1].velocity_vector.second = player_paddles[1].movement_speed.second;
    else
         player_paddles[1].velocity_vector.second /= 1.2;

    // apply velocity for player 2
    int nextcoord = player_paddles[1].position.first + player_paddles[1].velocity_vector.first;
    if( nextcoord <  ScreenWidth - player_paddles[1].dimensions.first && nextcoord > 16)
        player_paddles[1].position.first += player_paddles[1].velocity_vector.first;

    nextcoord = player_paddles[1].position.second + player_paddles[1].velocity_vector.second;
    if( nextcoord <  ScreenHeight - player_paddles[1].dimensions.second && nextcoord > -ScreenHeight)
        player_paddles[1].position.second += player_paddles[1].velocity_vector.second;
}


 /***************************************************************************//**
 * Shared Step
 * Authors - Derek Stotz, Charles Parsons
 *
 * Does a step in the game environment, telling what parts of the game's state
        need to change.  Used by the main game and the practice steps.
 ******************************************************************************/
void shared_step()
{
   // check for game pause
   if( space_pressed )
   {
       resume_screen = current_screen;
       current_screen = PAUSE;
       space_pressed = false;
   }

    // horizontal movement player 1
    if( a_pressed && d_pressed )
         player_paddles[0].velocity_vector.first = 0;
    else if( a_pressed )
         player_paddles[0].velocity_vector.first = -1 * player_paddles[0].movement_speed.first;
    else if( d_pressed )
         player_paddles[0].velocity_vector.first = player_paddles[0].movement_speed.first;
    else
         player_paddles[0].velocity_vector.first /= 1.2;

    // vertical movement player 1
    if( s_pressed && w_pressed )
         player_paddles[0].velocity_vector.second = 0;
    else if( s_pressed )
         player_paddles[0].velocity_vector.second = -1 * player_paddles[0].movement_speed.second;
    else if( w_pressed )
         player_paddles[0].velocity_vector.second = player_paddles[0].movement_speed.second;
    else
         player_paddles[0].velocity_vector.second /= 1.2;

    // apply velocity
    int nextcoord = player_paddles[0].position.first + player_paddles[0].velocity_vector.first;
    if( nextcoord <  -player_paddles[0].dimensions.first - 16 && nextcoord > -ScreenWidth)
        player_paddles[0].position.first += player_paddles[0].velocity_vector.first;

    nextcoord = player_paddles[0].position.second + player_paddles[0].velocity_vector.second;
    if( nextcoord <  ScreenHeight - player_paddles[0].dimensions.second && nextcoord > -ScreenHeight)
        player_paddles[0].position.second += player_paddles[0].velocity_vector.second;
   
    nextcoord = game_ball.position.second + game_ball.velocity_vector.second;
    if( nextcoord <  ScreenHeight && nextcoord > -ScreenHeight)
        game_ball.position.second += game_ball.velocity_vector.second;
    else
        game_ball.velocity_vector.second *= -1;

    nextcoord = game_ball.position.first + game_ball.velocity_vector.first;
    if( nextcoord <  ScreenWidth + game_ball.diameter && nextcoord > -ScreenWidth - game_ball.diameter)
        game_ball.position.first += game_ball.velocity_vector.first;
    else
    {
        // score!
        cpu_returning = true;
        if(nextcoord > 0)
            score(PLAYER_ONE, player_scores, end_score, current_screen);
        else
            score(PLAYER_TWO, player_scores, end_score, current_screen);
        game_ball.position.first = 0;
        game_ball.position.second = 0;
        game_ball.velocity_vector.first = 15 * turn;
        game_ball.velocity_vector.second = 0;
        turn *= -1;  //change serving turn

        // reset the paddle size
        paddle_scale = 1.0;
        player_paddles[0].dimensions.second = full_paddlesize * paddle_scale;
        player_paddles[1].dimensions.second = full_paddlesize * paddle_scale;
    }

    // apply relevant ball speedups
    ballSpeedupCheck();

    // apply collisions
    if(applyCollision(game_ball, player_paddles))
    {
        // shrink the paddles if there's a volley
        if(paddle_scale >= paddle_scalemin && abs(game_ball.velocity_vector.first) > 7)
        {
            player_paddles[0].dimensions.second = full_paddlesize * paddle_scale;
            player_paddles[1].dimensions.second = full_paddlesize * paddle_scale;
            paddle_scale -= paddle_scalespeed;
   
            player_paddles[0].position.second += 1;
            player_paddles[1].position.second += 1;
        }
    }
}

 /***************************************************************************//**
 * ballSpeedupCheck
 * Authors - Derek Stotz, Charles Parsons
 *
 * Checks if the ball needs to speed up or slow down based on mouse presses.
 ******************************************************************************/
void ballSpeedupCheck()
{
    // check for ball speedup/slowdown
    // this could be greatly compressed, but then it would not be as clear
    if(plus_pressed)
    {
        if(game_ball.velocity_vector.first > 0)
            game_ball.velocity_vector.first += 1;
        else if (game_ball.velocity_vector.first < 0)
            game_ball.velocity_vector.first -= 1;
 
        if(game_ball.velocity_vector.second > 0)
            game_ball.velocity_vector.second += 1;
        else if (game_ball.velocity_vector.second < 0)
            game_ball.velocity_vector.second -= 1;

        plus_pressed = false;
    }
    if(minus_pressed)
    {
        if(game_ball.velocity_vector.first > 0)
            game_ball.velocity_vector.first -= 1;
        else if (game_ball.velocity_vector.first < 0)
            game_ball.velocity_vector.first += 1;

        if(game_ball.velocity_vector.second > 0)
            game_ball.velocity_vector.second -= 1;
        else if (game_ball.velocity_vector.second < 0)
            game_ball.velocity_vector.second += 1;

        minus_pressed = false;
    }
}
