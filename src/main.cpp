////////// pre-processor directives //////////
#include "mbed.h"
#include "Gamepad.h"
#include "N5110.h"
#include "GameEngine.h"
#include "Menu.h"

#define US_X 42
#define AA_X 2
#define SPEED 1.8

////////// structs //////////
struct UserInput {
  Direction d;
  float mag;
};

////////// objects //////////
N5110 lcd(PTC9,PTC0,PTC7,PTD2,PTD1,PTC11);
Gamepad pad; //gamepad object
GameEngine engine; //GameEngine object
Menu menu; //menu object

////////// prototypes //////////
void init(); //used to call all initialisations
void render(); //used to call all items to be drawn on the LCD screen
void update_game(UserInput input);

////////// functions //////////
int main()
{
  int fps = 30;

  init();
  render();
  wait(1.0f/fps);

  while(1){
    float brightness = pad.read_pot(); //allows user control of screen brightness using potentiometer
    lcd.setBrightness(brightness);
    if (menu.is_game_active() == 1){ //checks if the game should run. If true, run game.
      engine.read_input(pad);
      engine.update(pad);
      if (pad.check_event(Gamepad::START_PRESSED)){ //pauses game bu taking user back to menu if START is pressed.
        menu.stop_game();
      }
      else if (pad.check_event(Gamepad::BACK_PRESSED)){ //restarts game by taking the user to the menu and re-initialising the game engine if BACK is pressed.
        engine.initialise(US_X, AA_X, SPEED);
        menu.stop_game();
      }
    } else if (menu.is_game_active() == 0){ //if the game is not active, display the menu screen
      menu.read_input(pad);
      menu.update(pad, lcd);
    }
    render();
    wait(1.0f/fps);
  }
}

void render()
{
  lcd.clear();
  if (menu.is_game_active() == 1){ //render game engine if game is active
    engine.draw(lcd);
  } else if (menu.is_game_active() == 0) { //render menu if game is not active
    menu.draw(lcd);
  }
  lcd.refresh();
}

void init()
{
  lcd.init();
  pad.init();

  menu.initialise(25, 0);
  engine.initialise(US_X, AA_X, SPEED);

}
