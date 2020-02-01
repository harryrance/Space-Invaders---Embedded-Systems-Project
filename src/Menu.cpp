#include "Menu.h"
//Constructor
Menu::Menu()
{

}
//Destructor
Menu::~Menu()
{

}
//Initialise function - sets the initial square position and coins number.
void Menu::initialise(int square_pos, int all_coins)
{
  _square_pos_y = square_pos;
  _square_pos_x = 70;
  _all_coins = all_coins;
  _is_game_active = 0; //tells the game to not start running initially.
  _page_index = 0; //starts on the first menu page.
}
//Draw function - draws all of the elements of the menu system.
void Menu::draw(N5110 &lcd)
{
  draw_initial_screen(lcd);
  draw_shop(lcd);
  draw_selection_square(lcd);
}
//Update function - used to update the position of the selection square and the screen state depending on user inputs.
void Menu::update(Gamepad &pad, N5110 &lcd)
{
  move_selection_square_y(_d);
  move_selection_square_x(_d);
  initial_screen_selection(pad);
  page_selection(pad);
  step_back(pad);
  exit_game(lcd, pad);
}
//Read Input function - reads the input on the joystick to move selection square.
void Menu::read_input(Gamepad &pad)
{
  _d = pad.get_direction();
}
//Draws the initial start-up menu screen.
void Menu::draw_initial_screen(N5110 &lcd)
{
  lcd.printString("SPACE INVADERS",0,0);
  lcd.printString("BOSS FIGHT",13,1);
  lcd.printString("Start Game", 5, 3);
  lcd.printString("Shop", 5, 4);
  lcd.printString("Exit", 5, 5);
}
//Draws the selection square with a movable x and y origin.
void Menu::draw_selection_square(N5110 &lcd)
{
  lcd.drawRect(_square_pos_x, _square_pos_y, 5, 5, 1);
}
//Used to move selection square in the x position.
void Menu::move_selection_square_x(Direction d)
{
  if (d == CENTRE) { //calling this using the _square_active variable ensures that the selection square
                     //only moves up/down/left/right once per movement of the joystick.
    _square_active = 1;
  }
  if (_page_index == 1){
    if (d == E && _square_active){
      _square_pos_x += 22;
      _square_pos_y = 41;
      _square_active = 0;
    } else if (d == W && _square_active){
      _square_pos_x -= 22;
      _square_pos_y = 41;
      _square_active = 0;
    }
    //resets square position if it moves further than the amount of options.
    if(_square_pos_x < 7){
      _square_pos_x = 73;
    }
    if(_square_pos_x > 73){
      _square_pos_x = 7;
    }
  }
}
//Moves selection square in the y direction.
void Menu::move_selection_square_y(Direction d)
{
  if (d == CENTRE) {
    _square_active = 1;
  }
  if (_page_index == 0 || _page_index == 2){
    _square_pos_x = 70;
    if (d == S && _square_active){
      _square_pos_y += 8;
      _square_pos_x = 70;
      _square_active = 0;
    } else if (d == N && _square_active){
      _square_pos_y -= 8;
      _square_pos_x = 70;
      _square_active = 0;
    }
    if(_square_pos_y < 25){
      _square_pos_y = 41;
    }
    if(_square_pos_y > 41){
      _square_pos_y = 25;
    }
  }
}
//turns off LCD screen and sets brightness to 0 if this option is selected.
void Menu::exit_game(N5110 &lcd, Gamepad &pad)
{
  if (_square_pos_y == 41 && (pad.check_event(Gamepad::A_PRESSED)) && _page_index == 0){
    lcd.turnOff();
    lcd.setBrightness(0.0);
  }
}
//moves into the shop screen if this option is selected. Also sets the x and y position of the square to the correct position for the shop.
void Menu::page_selection(Gamepad &pad)
{
  if (_square_pos_y == 33 && (pad.check_event(Gamepad::A_PRESSED)) && _page_index == 0){
    _page_index = 1;
    _square_pos_x = 7;
    _square_pos_y = 41;
  }
}
//allows the user to use the BACK button to step back to the main screen.
void Menu::step_back(Gamepad &pad)
{
  if (_page_index == 1 && (pad.check_event(Gamepad::BACK_PRESSED))){
    _page_index = 0;
    _square_pos_x = 70;
    _square_pos_y = 33;
  }
  if (_page_index == 2 && (pad.check_event(Gamepad::BACK_PRESSED))){
    _page_index = 0;
    _square_pos_x = 70;
    _square_pos_y = 41;
  }
}
//Draws all of the shop elements.
void Menu::draw_shop(N5110 &lcd)
{
  if(_page_index == 1){
    lcd.clear();
    lcd.printString("SHOP",35,0);
    draw_shop_ship_1(lcd);
    draw_shop_ship_2(lcd);
    draw_shop_ship_3(lcd);
    draw_shop_ship_4(lcd);
    draw_heart(lcd);
    lcd.printString("Life: 100 C",5,3);
    //changes displayed ship price depending on square position.
    if (_square_pos_x == 7){
      lcd.printString("Cost: 50 C",5,2);
    } else if (_square_pos_x == 29) {
      lcd.printString("Cost: 100 C",5,2);
    } else if (_square_pos_x == 51) {
      lcd.printString("Cost: 150 C",5,2);
    } else if (_square_pos_x == 73) {
      lcd.printString("Cost: 200 C",5,2);
    }
  }
}
//sets pixels for the first shop ship.
void Menu::draw_shop_ship_1(N5110 &lcd)
{
  lcd.drawRect(5, 38, 2, 2, 1);
  lcd.drawRect(9, 38, 2, 2, 1);
  lcd.drawRect(13, 38, 2, 2, 1);
  lcd.drawRect(7, 36, 2, 2, 1);
  lcd.drawRect(11, 36, 2, 2, 1);
  lcd.drawRect(5, 34, 10, 2, 1);
  lcd.drawRect(7, 32, 6, 4, 1);
  lcd.drawRect(9, 30, 2, 2, 1);
}
//sets pixels for the second shop ship.
void Menu::draw_shop_ship_2(N5110 &lcd)
{
  lcd.drawRect(29, 38, 6, 2, 1);
  lcd.drawRect(27, 36, 4, 2, 1);
  lcd.drawRect(33, 36, 4, 2, 1);
  lcd.drawRect(27, 34, 10, 2, 1);
  lcd.drawRect(27, 32, 2, 4, 1);
  lcd.drawRect(35, 32, 2, 4, 1);
  lcd.drawRect(31, 32, 2, 2, 1);
}
//sets pixels for the third shop ship.
void Menu::draw_shop_ship_3(N5110 &lcd)
{
  lcd.drawRect(49, 38, 2, 2, 1);
  lcd.drawRect(57, 38, 2, 2, 1);
  lcd.drawRect(51, 36, 2, 2, 1);
  lcd.drawRect(55, 36, 2, 2, 1);
  lcd.drawRect(53, 34, 2, 2, 1);
}
//sets pixels for the fourth shop ship.
void Menu::draw_shop_ship_4(N5110 &lcd)
{
  lcd.drawRect(71, 38, 10, 2, 1);
  lcd.drawRect(73, 36, 2, 2, 1);
  lcd.drawRect(77, 36, 2, 2, 1);
  lcd.drawRect(73, 34, 6, 2, 1);
  lcd.drawRect(71, 32, 2, 4, 1);
  lcd.drawRect(75, 30, 2, 4, 1);
  lcd.drawRect(79, 32, 2, 4, 1);
}
//sets pixels for the shop heart.
void Menu::draw_heart(N5110 &lcd)
{
  lcd.drawRect(41, 32,2,1,0);
  lcd.drawRect(44, 32,2,1,0);
  lcd.drawRect(40, 33,7,1,0);
  lcd.drawRect(39, 34,9,1,0);
  lcd.drawRect(40, 35,7,1,0);
  lcd.drawRect(41, 36,5,1,0);
  lcd.drawRect(42, 37,3,1,0);
  lcd.setPixel(43, 38);
}
//runs the game if this option is selected.
void Menu::initial_screen_selection(Gamepad &pad)
{
  if (_square_pos_y == 25 && (pad.check_event(Gamepad::A_PRESSED)) && _page_index == 0) {
    run_game();
  }
}
//sets the _is_game_active variable to 1. Indicated game should start running.
void Menu::run_game()
{
  _is_game_active = 1;
}
//sets the _is_game_active variable to 0. Indicated game should stop running.
void Menu::stop_game()
{
  _is_game_active = 0;
}
//returns integer value denoting whether game should be running or not
int Menu::is_game_active()
{
  return _is_game_active;
}
//returns integer value containing the number of coins the user currently holds.
int Menu::total_coins()
{
  _all_coins = _boss.get_boss_coins() + _bullet.get_coins();
  return _all_coins;
}
