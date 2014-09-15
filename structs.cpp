using namespace std;

// colors
const float Black[]	= { 0.0, 0.0, 0.0 };
const float Red[]	= { 1.0, 0.0, 0.0 };
const float Green[]	= { 0.0, 1.0, 0.0 };
const float Blue[]	= { 0.0, 0.0, 1.0 };
const float Magenta[]	= { 1.0, 0.0, 1.0 };
const float Cyan[]	= { 0.0, 1.0, 1.0 };
const float Yellow[]	= { 1.0, 1.0, 0.0 };
const float White[]	= { 1.0, 1.0, 1.0 };

 /***************************************************************************//**
 * @title Ball
 * @author Derek Stotz, Charles Parsons
 *
 * @par Description:
 *   The information which determines the state of the ball in the main game screen
 *
 * @param diameter - the diameter of the drawn and colliding ball
 * @param max_velocity - the maximum vertical or horizontal velocity
 * @param velocity_vector - the velocity vector <horizontal, vertical>
 * @param position - the current position <x, y>
 * @param color - the current color {R, G, B}
 ******************************************************************************/
struct Ball
{
    int diameter;
    int max_velocity;
    pair<int, int> velocity_vector;
    pair<int, int> position;
    float[] color;
}

 /***************************************************************************//**
 * @title Paddle
 * @author Derek Stotz, Charles Parsons
 *
 * @par Description:
 *   The information which determines the state of a Paddle on the game screen
 *
 * @param dimensions - the drawn and colliding dimensions <width, height>
 * @param velocity_vector - the velocity vector <horizontal, vertical>
 * @param position - the current position <x, y>
 * @param movement_speed - the velocity vector applied when the paddle is moved by the player.  Also the maximum speed of the paddle <horizontal, vertical>
 * @param color - the current color {R, G, B}
 ******************************************************************************/
struct Paddle
{
    pair<int, int> dimensions;
    pair<int, int> velocity_vector;
    pair<int, int> position;
    pair<int, int> movement_speed;
    float[] color;
}

 /***************************************************************************//**
 * @title Menu
 * @author Derek Stotz, Charles Parsons
 *
 * @par Description:
 *   The information which determines the state of and drawn information in a text menu.
 *
 * @param options - the displayed text options in the menu
 * @param selection_index - the currently selected option number
 * @param option_actions - the function executed when an option is selected
 * @param background_color - the color of the menu background {R, G, B}
 * @param text_color - the color of the menu text {R, G, B}
 * @param selection_color - the color of the selected text option {R, G, B}
 ******************************************************************************/
struct Menu
{
    string[] options;
    int selection_index;
    void*[] option_actions;
    float[] background_color;
    float[] text_color;
    float[] selection_color;
}