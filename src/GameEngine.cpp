#include "GameEngine.h"
//Constructor
GameEngine::GameEngine()
{

}
//Destructor
GameEngine::~GameEngine()
{

}
//Initialise function - initialises the ships and alien array starting positions, alongside the speed of movement.
void GameEngine::initialise(int ship_x_origin, int alien_x_origin, int speed)
{
  _us_x_origin = ship_x_origin;
  _aa_x_origin = alien_x_origin;
  _speed = speed;
  _boss_check = 0;
  _end_game_const = 0;
  _ship_number = 0;

  //initialises the boss fight, bullet, alien array and user ship.
  _boss.initialise(31, 28, 0, 0, 0, 4, 0, 0);
  _bullet.initialise(0, 42, 0, 0, 0, 0);
  _aliens.initialise(_aa_x_origin, 15, _speed);
  _ship.initialise(1, _us_x_origin, 47);

  //sets all of the aliens in the initial array to be active at the start.
  for(int a = 0; a < 3; a++){
    for(int b = 0; b < 11; b++){
      _aliens.array_active[a][b] = 1;
    }
  }

}

//reads user input - direction of joystick, magnitude of joystick and button presses.
void GameEngine::read_input(Gamepad &pad)
{
  _d = pad.get_direction();
  _mag = pad.get_mag();
  _bullet.check_button_press(pad);

}

//updates game parameters with regards to the game mechanics, such as collisions, movement, score and coins etc.
void GameEngine::update(Gamepad &pad)
{
  _ship.update(_d,_mag);
  _aliens.update();
  _bullet.update();
  if (_boss_check){
    _boss.update();
    check_bomb_ship_collision(pad);
  }
  move_boss(pad);
  set_bullet_position(pad);
  check_alien_wall_collision(pad);
  eliminate_alien_line_0(pad);
  eliminate_alien_line_1_1(pad);
  buy_lives(pad);
  buy_ships(pad);
  give_cheat_coins(pad);
  set_lives_leds(pad);
}

//draws all of the game's objects with regards to what has been updated in the update function.
void GameEngine::draw(N5110 &lcd)
{
  _aliens.draw(lcd);
  _bullet.draw(lcd);
  if (_boss_check){
    _boss.draw(lcd);
    boss_fight_health_bar(lcd);
  }
  int lives_remaining = _boss.lives();
  if (lives_remaining < 0) {
    end_game(lcd);
  }
  print_score_coins(lcd);
  check_end_game(lcd);

  //changes the user ship if a different ship has been purchased.
  if (_ship_number == 1) {
    _ship.draw_ship_1(lcd);
  } else if (_ship_number == 2) {
    _ship.draw_ship_2(lcd);
  } else if (_ship_number == 3) {
    _ship.draw_ship_3(lcd);
  } else if (_ship_number == 4) {
    _ship.draw_ship_4(lcd);
  } else {
    _ship.draw_default_ship(lcd);
  }
}
//checks whether an alien should be alive or not, and eliminates it if needed. (1st line)
void GameEngine::eliminate_alien_line_0(Gamepad &pad)
{
  Vector2D alien_pos_check = _aliens.get_pos();
  Vector2D bullet_pos = _bullet.get_position();
  //checks whether the bullet is within each individual aliens hitbox whilst the sprite is active.
  if ((((alien_pos_check.x/8)+13) <= bullet_pos.x) && (((alien_pos_check.x/8)+16) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+10)) && _aliens.array_active[0][0]){
        _aliens.array_active[0][0] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+18) <= bullet_pos.x) && (((alien_pos_check.x/8)+21) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+10)) && _aliens.array_active[0][1]){
        _aliens.array_active[0][1] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+23) <= bullet_pos.x) && (((alien_pos_check.x/8)+26) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+10)) && _aliens.array_active[0][2]){
        _aliens.array_active[0][2] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+28) <= bullet_pos.x) && (((alien_pos_check.x/8)+31) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+10)) && _aliens.array_active[0][3]){
        _aliens.array_active[0][3] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+33) <= bullet_pos.x) && (((alien_pos_check.x/8)+36) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+10)) && _aliens.array_active[0][4]){
        _aliens.array_active[0][4] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+38) <= bullet_pos.x) && (((alien_pos_check.x/8)+41) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+10)) && _aliens.array_active[0][5]){
        _aliens.array_active[0][5] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+43) <= bullet_pos.x) && (((alien_pos_check.x/8)+46) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+10)) && _aliens.array_active[0][6]){
        _aliens.array_active[0][6] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+48) <= bullet_pos.x) && (((alien_pos_check.x/8)+51) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+10)) && _aliens.array_active[0][7]){
        _aliens.array_active[0][7] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+53) <= bullet_pos.x) && (((alien_pos_check.x/8)+56) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+10)) && _aliens.array_active[0][8]){
        _aliens.array_active[0][8] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+58) <= bullet_pos.x) && (((alien_pos_check.x/8)+61) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+10)) && _aliens.array_active[0][9]){
        _aliens.array_active[0][9] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+63) <= bullet_pos.x) && (((alien_pos_check.x/8)+66) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+10)) && _aliens.array_active[0][10]){
        _aliens.array_active[0][10] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  }

}
//checks whether an alien should be alive or not, and eliminates it if needed. (2nd line)
void GameEngine::eliminate_alien_line_1_1(Gamepad &pad)
{
  Vector2D alien_pos_check = _aliens.get_pos();
  Vector2D bullet_pos = _bullet.get_position();

  if ((((alien_pos_check.x/8)+13) <= bullet_pos.x) && (((alien_pos_check.x/8)+16) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+16)) && _aliens.array_active[1][0]){
        _aliens.array_active[1][0] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+18) <= bullet_pos.x) && (((alien_pos_check.x/8)+21) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+16)) && _aliens.array_active[1][1]){
        _aliens.array_active[1][1] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+23) <= bullet_pos.x) && (((alien_pos_check.x/8)+26) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+16)) && _aliens.array_active[1][2]){
        _aliens.array_active[1][2] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+28) <= bullet_pos.x) && (((alien_pos_check.x/8)+31) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+16)) && _aliens.array_active[1][3]){
        _aliens.array_active[1][3] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+33) <= bullet_pos.x) && (((alien_pos_check.x/8)+36) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+16)) && _aliens.array_active[1][4]){
        _aliens.array_active[1][4] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+38) <= bullet_pos.x) && (((alien_pos_check.x/8)+41) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+16)) && _aliens.array_active[1][5]){
        _aliens.array_active[1][5] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+43) <= bullet_pos.x) && (((alien_pos_check.x/8)+46) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+16)) && _aliens.array_active[1][6]){
        _aliens.array_active[1][6] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+48) <= bullet_pos.x) && (((alien_pos_check.x/8)+51) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+16)) && _aliens.array_active[1][7]){
        _aliens.array_active[1][7] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+53) <= bullet_pos.x) && (((alien_pos_check.x/8)+56) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+16)) && _aliens.array_active[1][8]){
        _aliens.array_active[1][8] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+58) <= bullet_pos.x) && (((alien_pos_check.x/8)+61) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+16)) && _aliens.array_active[1][9]){
        _aliens.array_active[1][9] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  } else if ((((alien_pos_check.x/8)+63) <= bullet_pos.x) && (((alien_pos_check.x/8)+66) >= bullet_pos.x)
      && (bullet_pos.y <=(alien_pos_check.y+16)) && _aliens.array_active[1][10]){
        _aliens.array_active[1][10] = 0;
        reset_bullet();
        play_elimination_tone(pad);
  }

}
//resets bullet parameters when called. Also updates score and coins.
void GameEngine::reset_bullet()
{
  _bullet._button_check = 0; //allows bullet to be fired more than once
  _bullet._speed = 0;
  _bullet._y = 42;
  _bullet.add_coins();
  _bullet.add_score();

}
//called whenever an alien is hit with a bullet to play a tone.
void GameEngine::play_elimination_tone(Gamepad &pad)
{
  pad.tone(700, 0.1);
}
//stops bullet from moving with ship's x direction movement.
void GameEngine::set_bullet_position(Gamepad &pad)
{
  Vector2D bullet_pos = _bullet.get_position();
  Vector2D ship_pos = _ship.get_pos();
  //if the bullet has been active for one pixel worth of y direction movement, set it's following x position to it's current x position.
  //this allows for independent ship and bullet movement.
  if (bullet_pos.y > 39) {
    bullet_pos.x = ship_pos.x;
    _set_bullet_x = ship_pos.x;
  } else if (bullet_pos.y <= 39){
    bullet_pos.x = _set_bullet_x;
  }

  _bullet.set_position(bullet_pos);
}
//checks whether the alien array has reached the edge of the screen and updates movement vector accordingly.
void GameEngine::check_alien_wall_collision(Gamepad &pad)
{
  Vector2D alien_pos = _aliens.get_pos();
  Vector2D alien_vel = _aliens.get_velocity();

  if (alien_pos.x > 122) {
    alien_pos.x = 122;
    alien_pos.y += 3;
    alien_vel.x = (-alien_vel.x) - 0.5;
  } else if (alien_pos.x <= -100) {
    alien_pos.x = -100;
    alien_pos.y += 3;
    alien_vel.x = (-alien_vel.x) + 0.5;
  }

  _aliens.set_pos(alien_pos);
  _aliens.set_velocity(alien_vel);
}
//checks whether the boss has reached its x direction movement limits, and updates movement accordingly.
void GameEngine::move_boss(Gamepad &pad)
{
  Vector2D boss_pos = _boss.get_pos();
  Vector2D boss_vel = _boss.get_velocity();

  if (boss_pos.x > 360) {
    boss_pos.x = 360;
    boss_vel.x = -boss_vel.x;
  }else if (boss_pos.x < 130) {
    boss_pos.x = 130;
    boss_vel.x = -boss_vel.x;
  }
  _boss.set_pos(boss_pos);
  _boss.set_velocity(boss_vel);
}
//resets the bullet for the boss fight section and updates score and coins for end game screen accordingly.
void GameEngine::reset_bullet_for_boss()
{
  _bullet._button_check = 0;
  _bullet._speed = 0;
  _bullet._y = 42;
  _boss.add_boss_coins();
  _boss.add_boss_score();
}
//checks whether the user bullet has hit the boss, and decrements the health bar by 2 each time this is true.
void GameEngine::boss_fight_health_bar(N5110 &lcd)
{
  Vector2D bullet_pos = _bullet.get_position();
  Vector2D boss_pos = _boss.get_pos();
  int health_constant = _boss.get_health_bar_constant();

  if ((bullet_pos.x >= (boss_pos.x/8)) && (bullet_pos.x <= ((boss_pos.x/8) + 21)) && (bullet_pos.y <= boss_pos.y + 29)) {
    _boss.decrement_health_constant();
    reset_bullet();
  } if (health_constant < 0) { //sets game over conditions (if boss health is < 0)
    health_constant = 0;
    check_fight_complete(lcd);
    if (_end_game_const == 0){
      reset_bullet_for_boss();
    }
    _end_game_const = 1;
  }
}
//allows the user to buy extra lives if lives have been lost and the user has the correct amount of coins (max 3 lives).
void GameEngine::buy_lives(Gamepad &pad)
{
  int coins = _bullet.get_coins();
  if (coins >= 100 && (pad.check_event(Gamepad::L_PRESSED))) {
    _boss.inc_lives();
    _bullet.dec_coins_for_life();
  }
}
//allows the user to buy different ships, and updates the ship number variable depending on which has been purchased.
void GameEngine::buy_ships(Gamepad &pad)
{
  int coins = _bullet.get_coins();
  if (coins >= 50 && pad.check_event(Gamepad::X_PRESSED)) {
    _ship_number = 1;
    _bullet.dec_coins_for_x();
  }
  if (coins >= 100 && pad.check_event(Gamepad::Y_PRESSED)) {
    _ship_number = 2;
    _bullet.dec_coins_for_y();
  }
  if (coins >= 150 && pad.check_event(Gamepad::B_PRESSED)) {
    _ship_number = 3;
    _bullet.dec_coins_for_b();
  }
  if (coins >= 200 && pad.check_event(Gamepad::R_PRESSED)) {
    _ship_number = 4;
    _bullet.dec_coins_for_r();
  }
}
//checks whether a boss bomb has collided with the user ship, and decrements lives if so. Also plays a tone when ship is hit.
void GameEngine::check_bomb_ship_collision(Gamepad &pad)
{
  Vector2D ship_pos = _ship.get_pos();
  Vector2D boss_pos = _boss.get_pos();
  Vector2D bomb_pos = _boss.get_bomb_pos();

  if (((boss_pos.x/8) >= (ship_pos.x - 2)) &&
     ((boss_pos.x/8) <= (ship_pos.x + 2)) && (bomb_pos.y > 360)) {
       _boss.dec_lives();
       bomb_pos.y = 160;
       pad.tone(500,0.1);
  } else if ((((boss_pos.x/8) + 10) >= (ship_pos.x - 2)) &&
    (((boss_pos.x/8) + 10) <= (ship_pos.x + 2)) && (bomb_pos.y > 360)) {
      _boss.dec_lives();
      bomb_pos.y = 160;
      pad.tone(500,0.1);
  } else if ((((boss_pos.x/8) + 20) >= (ship_pos.x - 2)) &&
    (((boss_pos.x/8) + 20) <= (ship_pos.x + 2)) && (bomb_pos.y > 360)) {
      _boss.dec_lives();
      bomb_pos.y = 160;
      pad.tone(500,0.1);
  }
  _boss.set_bomb_pos(bomb_pos);
}
//prints the current user score in the top left of the screen, and coins in the top right of the screen.
void GameEngine::print_score_coins(N5110 &lcd)
{
  int user_score = _bullet.get_score();
  int user_coins = _bullet.get_coins();

  char buffer_score[14];
  sprintf(buffer_score,"%2d",user_score);
  char buffer_coins[14];
  sprintf(buffer_coins,"%2d",user_coins);
  lcd.printString(buffer_score, 4, 0);
  lcd.printString(buffer_coins, 62, 0);
}
//called when the boss has been defeated to add extra score and show the end game screen.
void GameEngine::check_fight_complete(N5110 &lcd)
{
  int score = _bullet.get_score();
  int boss_score = _boss.get_boss_score();

  int total_score = score + boss_score;

  lcd.clear();

  char buffer_score[14];
  char buffer_complete[14];

  sprintf(buffer_score,"Score: %2d",total_score);
  sprintf(buffer_complete,"Game Complete!");

  lcd.printString(buffer_score,2,3);
  lcd.printString(buffer_complete,2,2);
  lcd.printString("Press Back",2,4);
}
//called when the boss defeats the user and updates the end game screen accordingly.
void GameEngine::end_game(N5110 &lcd)
{
  int score = _bullet.get_score();
  int boss_score = _boss.get_boss_score();

  int total_score = score + boss_score;

  lcd.clear();

  char buffer_score[14];
  char buffer_complete[14];

  sprintf(buffer_score,"Score: %2d",total_score);
  sprintf(buffer_complete,"Game Over!");

  lcd.printString(buffer_score,2,3);
  lcd.printString(buffer_complete,2,2);
  lcd.printString("Press Back",2,4);
}
//checks whether the first section of the game (aliens array) should end and move onto the boss fight.
void GameEngine::check_end_game(N5110 &lcd)
{
  Vector2D alien_pos = _aliens.get_pos();

  if (alien_pos.y >= 25) {
    for(int a = 0; a < 3; a++){
      for(int b = 0; b < 11; b++){
        _aliens.array_active[a][b] = 0;
      }
    }
    _boss_check = 1;
  }
}
//used for demonstration purposes to give coins in order to demonstrate shop functionality.
void GameEngine::give_cheat_coins(Gamepad &pad)
{
  if (pad.check_event(Gamepad::JOY_PRESSED) ){
     _bullet.add_coins();
   }
}
//sets 6 on board LEDs high.
void GameEngine::set_six_leds(Gamepad &pad)
{
  pad.led(1,1.0);
  pad.led(2,1.0);
  pad.led(3,1.0);
  pad.led(4,1.0);
  pad.led(5,1.0);
  pad.led(6,1.0);
}
//sets 4 on board LEDs high.
void GameEngine::set_four_leds(Gamepad &pad)
{
  pad.led(1,1.0);
  pad.led(2,1.0);
  pad.led(3,1.0);
  pad.led(4,1.0);
  pad.led(5,0.0);
  pad.led(6,0.0);
}
//sets 2 on board LEDs high.
void GameEngine::set_two_leds(Gamepad &pad)
{
  pad.led(1,1.0);
  pad.led(2,1.0);
  pad.led(3,0.0);
  pad.led(4,0.0);
  pad.led(5,0.0);
  pad.led(6,0.0);
}
//sets all on board LEDs low.
void GameEngine::set_zero_leds(Gamepad &pad)
{
  pad.led(1,0.0);
  pad.led(2,0.0);
  pad.led(3,0.0);
  pad.led(4,0.0);
  pad.led(5,0.0);
  pad.led(6,0.0);
}
//chooses how many LEDs to have lit depending on how many lives the user has.
void GameEngine::set_lives_leds(Gamepad &pad)
{
  int lives = _boss.lives();
  if (lives == 3){
    set_six_leds(pad);
  } else if (lives == 2){
    set_four_leds(pad);
  } else if (lives == 1) {
    set_two_leds(pad);
  } else {
    set_zero_leds(pad);
  }
}
