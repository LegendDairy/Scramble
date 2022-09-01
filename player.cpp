#include "player.h"
#include "game.h"
#include "bomb.h"
#include "bullet.h"
#include "gameovermenu.h"
#include "map.h"
#include "gameobjecthandler.h"
#include "gameovermenu.h"

player_c::player_c(float x0, float y0) : gameobject_c(x0,y0,GAME_SCROLLING_SPEED,0,player_id)
{
  /* De timer zorgt dat er een delay tussen twee bomben is */
  bomb_timer = 0;
  bullet_timer = 0;

  this->width = PLAYER_WIDTH;
  this->height = PLAYER_HEIGTH;

  texture = new sf::Texture();
  texture->loadFromFile("spritesheet.png", sf::IntRect(1, 1, 32, 32));

  /* De grafische figuur dat de speler voorsteld */
  figure = new sf::RectangleShape(sf::Vector2f(width,height));
  figure->setPosition(sf::Vector2f(x0,y0));
  figure->setTexture(texture, true);
}

void player_c::tick(void)
{
  x += vx;

  if(x >= MAP_LENGTH*MAP_LINE_WIDTH)
  {
    game_c::game_over(GAME_OVER_STATE_WON);
  }

  if(fuel_level == 0)
  {
    game_c::game_over(GAME_OVER_STATE_NO_FUEL);
  }

  if(bomb_timer != 0) {    bomb_timer--; }
  if(bullet_timer != 0) { bullet_timer--; }

  if(fuel_level != 0) { fuel_level--; }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
  {
    this->set_position(sf::Vector2f(x-4,y));
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
  {
    this->set_position(sf::Vector2f(x+4,y));
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
  {
    this->set_position(sf::Vector2f(x,y-3));
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
  {
    this->set_position(sf::Vector2f(x,y+3));
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
  {
    if(bomb_timer==0)
    {
      bomb_c *tmp = new bomb_c(x,y+PLAYER_HEIGTH,vx);
      gameobject_handler_c::get_handler()->add_object_to_game(tmp);
      bomb_timer = BOMB_TIME;
    }
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
  {
    if(bullet_timer==0)
    {
      float player_nose_x = x+PLAYER_WIDTH;
      float player_nose_y = y+(PLAYER_HEIGTH/2);

      bullet_c *tmp = new bullet_c(player_nose_x,player_nose_y);
      gameobject_handler_c::get_handler()->add_object_to_game(tmp);
      bullet_timer = BULLET_TIME;
    }
  }
  /** Map collision detection **/
  if(y + PLAYER_HEIGTH+5> ((map_c*)gameobject_handler_c::get_handler()->get_map())->get_map_height(x))
  {
    game_c::game_over(GAME_OVER_STATE_MAP_CRASH);
  }
}

void player_c::render(sf::RenderWindow *w)
{
  figure->setPosition(x,y);
  clamp(w);
  w->draw(*figure);
}



sf::FloatRect player_c::get_bounds(void)
{
  return figure->getGlobalBounds();
}

unsigned int player_c::get_score()
{
  return score;
}

unsigned int player_c::get_fuel_level()
{
  return fuel_level;
}

void player_c::increase_fuel_level(unsigned int delta)
{
  fuel_level+= delta;
  if(fuel_level > MAX_FUEL_LEVEL)
    fuel_level = MAX_FUEL_LEVEL;
}

void player_c::increase_score(unsigned int delta)
{
  score += delta;
}

/* Functie dit het object vast klempt aan het scherm: ervoor zorgt dat het object niet van het scherm weg kan. */
void player_c::clamp(sf::RenderWindow *w)
{
  if(this->y < 0)
  {
    y=0;
  }
  if(this->y > GAME_HEIGHT-height)
  {
    y=GAME_HEIGHT-height;
  }

  if(this->x>=w->mapPixelToCoords(sf::Vector2i(GAME_WIDTH-width,y)).x)
  {
    this->x  = w->mapPixelToCoords(sf::Vector2i(GAME_WIDTH-width,y)).x;
  }

  if(this->x<=w->mapPixelToCoords(sf::Vector2i(0,y)).x)
  {
    this->x  = w->mapPixelToCoords(sf::Vector2i(0,y)).x;
  }

}
