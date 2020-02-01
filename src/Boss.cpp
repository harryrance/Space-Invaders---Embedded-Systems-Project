#include "Boss.h"
//Constructor
Boss::Boss()
{

}
//Destructor
Boss::~Boss()
{

}
// Initialise function - initialises all parameters for the boss fight to begin with.
void Boss::initialise(int x_origin, int y_origin, int health_x, int health_y,
                      int health, int speed, int coins, int score)
{
  _x = x_origin; //sets the _x movement variable equal to the initialised x origin.
  _boss_y = y_origin; //sets the _boss_y movement variable equal to the initialised y origin.
  _health_bar_constant = 52;
  _boss_lives = 3;
  _heart_x = 35; //x and y origins for the first heart.
  _heart_y = 1;
  _heart_var = 15; //sets distance between hearts.
  _boss_coins = coins;
  _boss_score = score;

  int direction = 0;
  //movement direction and velocity indicator for the boss and bombs.
  if (direction == 0) {
    _velocity.x = speed;
    _b_velocity.y = -speed * 1.2;
  } else if (direction == 1) {
    _velocity.x = -speed;
  }
}
//Draw function - calls the functions to be drawn on the LCD screen.
void Boss::draw(N5110 &lcd)
{
  boss_sprite(lcd);
  health_bar_draw(lcd);
  draw_bombs(lcd);
  draw_lives(lcd);
}
//Update function - updates the velociy parameters for the boss and bomb movement.
void Boss::update()
{
  _x += _velocity.x;
  _y += _velocity.y;
  _b_x += _b_velocity.x;
  _b_y -= _b_velocity.y;
}
//Boss Sprite function - sets the required pixels for the boss sprite to be displayes, with regards to the x direciton movement.
void Boss::boss_sprite(N5110 &lcd)
{
  _boss_x = _x/8;
  lcd.drawRect(_boss_x + 4, _boss_y - 14, 2, 2, 0);   //1
  lcd.drawRect(_boss_x + 16, _boss_y - 14, 2, 2, 0);  //2
  lcd.drawRect(_boss_x + 6, _boss_y - 12, 2, 2, 0);   //3
  lcd.drawRect(_boss_x + 14, _boss_y - 12, 2, 2, 0);  //4
  lcd.drawRect(_boss_x + 4, _boss_y - 10, 14, 2, 0);  //5
  lcd.drawRect(_boss_x + 2, _boss_y - 8, 4, 2, 0);    //6
  lcd.drawRect(_boss_x + 8, _boss_y - 8, 6, 2, 0);    //7
  lcd.drawRect(_boss_x + 16, _boss_y - 8, 4, 2, 0);   //8
  lcd.drawRect(_boss_x + 2, _boss_y - 6, 18, 2, 0);   //9
  lcd.drawRect(_boss_x, _boss_y - 6, 2, 6, 0);        //10
  lcd.drawRect(_boss_x + 20, _boss_y - 6, 2, 6, 0);   //11
  lcd.drawRect(_boss_x + 4, _boss_y - 4, 14, 2, 0);   //12
  lcd.drawRect(_boss_x + 4, _boss_y - 2, 2, 2, 0);    //13
  lcd.drawRect(_boss_x + 16, _boss_y - 2, 2, 2, 0);   //14
  lcd.drawRect(_boss_x + 6, _boss_y, 4, 2, 0);        //15
  lcd.drawRect(_boss_x + 12, _boss_y, 4, 2, 0);       //16
}
//Health Bar Draw Function - draws the inner and outer sections of the health bar, and sets the length of the inner health bar
//with regards to the health integer variable.
void Boss::health_bar_draw(N5110 &lcd)
{
  lcd.drawRect(15, 8, 53, 5, 0); //health bar outline
  lcd.drawRect(16, 9, _health_bar_constant, 3, 1); //inner health bar
}
//Draw Bombs function - sets pixels for the bombs and resets their y-position if they have reached the screen boundary.
void Boss::draw_bombs(N5110 &lcd)
{
  _bomb_x = _x/8; //bombs move in the x direction at the same velocity as the boss in order to increase difficulty.
  _bomb_y = _b_y/8;
  lcd.setPixel(_bomb_x, _bomb_y);
  lcd.setPixel(_bomb_x + 1, _bomb_y - 1);
  lcd.setPixel(_bomb_x, _bomb_y - 2);
  lcd.setPixel(_bomb_x + 1, _bomb_y - 3);
  lcd.setPixel(_bomb_x, _bomb_y - 4);

  lcd.setPixel(_bomb_x + 20, _bomb_y);
  lcd.setPixel(_bomb_x + 21, _bomb_y - 1);
  lcd.setPixel(_bomb_x + 20, _bomb_y - 2);
  lcd.setPixel(_bomb_x + 21, _bomb_y - 3);
  lcd.setPixel(_bomb_x + 20, _bomb_y - 4);

  lcd.setPixel(_bomb_x + 10, _bomb_y);
  lcd.setPixel(_bomb_x + 11, _bomb_y - 1);
  lcd.setPixel(_bomb_x + 10, _bomb_y - 2);
  lcd.setPixel(_bomb_x + 11, _bomb_y - 3);
  lcd.setPixel(_bomb_x + 10, _bomb_y - 4);
  if (_b_y > 384){
    _b_y = 200;
  }
}
//Draw Lives function - sets the pixels in the shape of a heart, and draws 0, 1, 2 or 3 instances with regards to how many lives are left.
void Boss::draw_lives(N5110 &lcd)
{
  if (_boss_lives == 3) {
    _heart_var = 15;
  } else if (_boss_lives == 2) {
    _heart_var = 8;
  } else if (_boss_lives == 1) {
    _heart_var = 1;
  }

  if (_boss_lives > 0) {
    for(int i = 0; i < _heart_var; i += 7) {
      lcd.drawRect((_heart_x + i)  - 2, _heart_y,2,1,0);
      lcd.drawRect((_heart_x + i) + 1, _heart_y,2,1,0);
      lcd.drawRect((_heart_x + i) - 3, _heart_y + 1,7,1,0);
      lcd.drawRect((_heart_x + i) - 4, _heart_y + 2,9,1,0);
      lcd.drawRect((_heart_x + i) - 3, _heart_y + 3,7,1,0);
      lcd.drawRect((_heart_x + i) - 2, _heart_y + 4,5,1,0);
      lcd.drawRect((_heart_x + i) - 1, _heart_y + 5,3,1,0);
      lcd.setPixel((_heart_x + i), _heart_y + 6);
    }
  }
}
//Decrement health function - recudes boss health by 2 every time this is called.
void Boss::decrement_health_constant()
{
  _health_bar_constant -= 2;
}
//Get Health function - returns the integer value of boss health.
int Boss::get_health_bar_constant()
{
  return _health_bar_constant;
}
//Get Bomb Velocity function - returns a 2D vector with x and y members of the bomb velocity.
Vector2D Boss::get_bomb_vel()
{
  Vector2D b_vel = {_b_velocity.x,_b_velocity.y};
  return b_vel;
}
//Get Bomb Position function - returns a 2D vector with x and y members of the bomb position.
Vector2D Boss::get_bomb_pos()
{
  Vector2D b_pos = {_b_x,_b_y};
  return b_pos;
}
//Get Boss Velocity function - returns 2D vector with x and y memebers of the boss velocity.
Vector2D Boss::get_velocity()
{
  Vector2D v = {_velocity.x,_velocity.y};
  return v;
}
//Get Boss Position funciton - returns 2D vector with x and y members of the boss position.
Vector2D Boss::get_pos()
{
  Vector2D p = {_x,_y};
  return p;
}
// sets the velocity of the bomb in the x and y directions.
void Boss::set_bomb_vel(Vector2D b_vel)
{
  _b_velocity.x = b_vel.x;
  _b_velocity.y = b_vel.y;
}
// sets the x and y position of the bombs.
void Boss::set_bomb_pos(Vector2D b_pos)
{
  _b_x = b_pos.x;
  _b_y = b_pos.y;
}
// sets the x and y velocity of the boss.
void Boss::set_velocity(Vector2D v)
{
  _velocity.x = v.x;
  _velocity.y = v.y;
}
// sets x and y position of the boss.
void Boss::set_pos(Vector2D p)
{
  _x = p.x;
  _y = p.y;
}
// increments score by 100 if boss fight is complete.
void Boss::add_boss_score()
{
  _boss_score += 100;
}
// returns integet value of the boss score.
int Boss::get_boss_score()
{
  return _boss_score;
}
// increments coins by 1000 if boss fight is complete.
void Boss::add_boss_coins()
{
  _boss_coins += 1000;
}
// returns integer value of amount of coins in boss fight.
int Boss::get_boss_coins()
{
  return _boss_coins;
}
//increments the lives variable by 1 (used when purchasing lives).
void Boss::inc_lives()
{
  _boss_lives += 1;
}
//decrements life variable by 1 each time user is hit by a bomb.
void Boss::dec_lives()
{
  _boss_lives -= 1;
}
//returns integer value of remaining user lives.
int Boss::lives()
{
  return _boss_lives;
}
