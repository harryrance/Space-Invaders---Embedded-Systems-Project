#ifndef MENU_H
#define MENU_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "Boss.h"
#include "Bullet.h"

/** Menu Class
@brief Library for generating the pre-game menu.
@brief Can be used to view the purchasable in-game items, exit the game or start the game running.

@author Harry Rance
@date 2nd May 2017

*/
class Menu
{
public:

  //Constructor
  Menu();

  //Destructor
  ~Menu();

  /** Initialise
  * Initialises the parameters for the menu screen.
  * @param square_pos - sets the initial y position for the selection square to 25.
  * @param all_coins - sets the initial value to 0 for all the coins if the game has just started.
  */
  void initialise(int square_pos, int all_coins);

  /** Draw
  * Draws all of the menu items depending on which screen should currently be showing.
  */
  void draw(N5110 &lcd);

  /** Read Input
  * Reads the input from the buttons and the joystick in order to manipulate the current menu screen.
  */
  void read_input(Gamepad &pad);

  /** Update
  * Updates menu parameters in order to tell where the selection square should be placed, and which screen should show next.
  */
  void update(Gamepad &pad, N5110 &lcd);

  /** Move Selection Square - Y
  * Used to move the selection square in the y direction.
  * Used in the initial screen.
  * @param d - enum value to denote what direction the joystick has been moved in. Used to move the selection square.
  */
  void move_selection_square_y(Direction d);

  /** Move Selection Square - X
  * Used to move the selection square in the x direction.
  * Used in the shop screen.
  * @param d - enum value to denote what direction the joystick has been moved in. Used to move the selection square.
  */
  void move_selection_square_x(Direction d);

  //Integer to total al of the user's current coins in order to be displayed.
  int total_coins();

  //Starts the game running by moving from the menu screen into the GameEngine.
  void run_game();

  //Stops the game from running and returns to the menu.
  void stop_game();

  //Returns an integer value to tell the program to either stay in the menu section, or move into the main game.
  int is_game_active();

private:

  /** Draw Initial Screen
  * Draws the three options, Start Game, Shop ane Exit.
  * Also draws a title at the top of the screen.
  */
  void draw_initial_screen(N5110 &lcd);

  /** Draw Selection Square
  * Draws the selection square in the requires position with regards to the user input.
  */
  void draw_selection_square(N5110 &lcd);

  /** Page Selection
  * Identifies which menu page to display next depending on the position of the selection square and the user input.
  */
  void page_selection(Gamepad &pad);

  /** Step Back
  * Allows the user to use the BACK button in each menu page to step back to the main page.
  */
  void step_back(Gamepad &pad);

  /** Initial Screen Selection
  * Allows the user to run the game from the first menu page.
  */
  void initial_screen_selection(Gamepad &pad);

  /* Draw Shop
  * Calls all 5 draw functions for the shop screen in order to draw the full shop view.
  * Calls draw_shop_ship_1-4 and draw_heart.
  * Also uses a printString statement to print the word "SHOP" at the top of the screen.
  */
  void draw_shop(N5110 &lcd);

  /* Draw Shop Ships
  * The following 4 functions set the required pixels for drawing the shop versions of the pruchasable ships.
  * Shop versions of the ships are twice the size of the in-game ship to be seen more easily.
  */
  void draw_shop_ship_1(N5110 &lcd);
  void draw_shop_ship_2(N5110 &lcd);
  void draw_shop_ship_3(N5110 &lcd);
  void draw_shop_ship_4(N5110 &lcd);

  /** Draw Heart
  * Draws the heart display sprite for the shop screen.
  */
  void draw_heart(N5110 &lcd);

  /** Exit Game
  * Turns LCD screen off and brightness to 0.
  */
  void exit_game(N5110 &lcd, Gamepad &pad);

  int _square_pos_x;
  int _square_pos_y;
  int _square_active;
  int _is_game_active;
  int _all_coins;
  int _page_index;

  Boss _boss;
  Bullet _bullet;

  Direction _d;

};

#endif
