 /***************************************************************************//**
 * structs.h
 * Authors - Derek Stotz, Charles Parsons
 *
 * This file contains structures, constants, and typedefs used in the Pong game.
 ******************************************************************************/

// function pointer for menus
typedef (*void) fptr;
 
// colors {R, G, B}
const float Black[]	= { 0.0, 0.0, 0.0 };
const float Red[]	= { 1.0, 0.0, 0.0 };
const float Green[]	= { 0.0, 1.0, 0.0 };
const float Blue[]	= { 0.0, 0.0, 1.0 };
const float Magenta[]	= { 1.0, 0.0, 1.0 };
const float Cyan[]	= { 0.0, 1.0, 1.0 };
const float Yellow[]	= { 1.0, 1.0, 0.0 };
const float White[]	= { 1.0, 1.0, 1.0 };

 /***************************************************************************//**
 * Ball
 * Authors - Derek Stotz, Charles Parsons
 *
 * The information which determines the state of the ball in the main game screen
 *
 * Parameters 
            diameter - the diameter of the drawn and colliding ball
            max_velocity - the maximum vertical or horizontal velocity
            velocity_vector - the velocity vector <horizontal, vertical>
            position - the current position <x, y>
            color - the current color {R, G, B}
 ******************************************************************************/
struct Ball
{
    int diameter;
    int max_velocity;
    std::pair<int, int> velocity_vector;
    std::pair<int, int> position;
    float[] color;
}

 /***************************************************************************//**
 * Paddle
 * Authors - Derek Stotz, Charles Parsons
 *
 * The information which determines the state of a Paddle on the game screen
 *
 * Members -
            dimensions - the drawn and colliding dimensions <width, height>
            velocity_vector - the velocity vector <horizontal, vertical>
            position - the current position <x, y>
            movement_speed - the velocity vector applied when the paddle is moved by the player.  Also the maximum speed of the paddle <horizontal, vertical>
            color - the current color {R, G, B}
 ******************************************************************************/
struct Paddle
{
    std::pair<int, int> dimensions;
    std::pair<int, int> velocity_vector;
    std::pair<int, int> position;
    std::pair<int, int> movement_speed;
    float[] color;
}

 /***************************************************************************//**
 * Menu
 * Authors - Derek Stotz, Charles Parsons
 *
 * The information which determines the state of and drawn information in a text menu.
 *
 * Members -
        options - the displayed text options in the menu
        selection_index - the currently selected option number
        option_actions - the function executed when an option is selected
        background_color - the color of the menu background {R, G, B}
        text_color - the color of the menu text {R, G, B}
        selection_color - the color of the selected text option {R, G, B}
 ******************************************************************************/
struct Menu
{
    std::string[] options;
    int selection_index;
    fptr[] option_actions;
    float[] background_color;
    float[] text_color;
    float[] selection_color;
}

 void applyCollision(ball b, paddle p);
 
 void movePaddle(paddle p);