#include "bullet.h"
#include "game.h"
#include "asteroid.h"
#include "gameobjecthandler.h"

/* De player class kan bullets maken. */
bullet_c::bullet_c(float x0, float y0) : gameobject_c(x0,y0,BULLET_SPEED_X,BULLET_SPEED_Y,bullet_id)
{
  /* heel analoog aan de bom, enkel beweegt deze langs x ipv y */
  figure = new sf::CircleShape(5,5);
  figure->setFillColor(sf::Color::White);
  figure->setPosition(sf::Vector2f(x0,y0));
}

bullet_c::~bullet_c()
{
  delete figure;
}

void bullet_c::render(sf::RenderWindow *w)
{
/* Buiten beeld? dan mag deze weg. mapPixelToCoords omdat we werken met een camera die beweegt */
if(this->y > GAME_HEIGHT || w->mapPixelToCoords(sf::Vector2i(GAME_WIDTH-width,y)).x < this->x)
{
  this->kill();
  return;
}

/* Nieuwe positie zetten en tekenen.*/
figure->setPosition(this->x, this->y);
w->draw(*figure);
}

void bullet_c::tick(void)
{
  y += vy;
  x += vx;

  /* Collision detection */
  gameobject_c *iterator = gameobject_handler_c::get_handler()->get_list();
  sf::FloatRect bullet_rect = get_bounds();

  /* Door de lijst gaan en elke keer als er een interessant object is kijken of er collision is. */
  while(iterator)
  {
    gameobject_c *next = iterator->get_next();
    if(iterator->get_id() == asteroid_id)
    {
      if(((asteroid_c*)iterator)->get_bounds().intersects(bullet_rect))
      {
        /* Asteroiden raken levert punten. */
        gameobject_handler_c::get_handler()->get_player()->increase_score(1);
        iterator->kill();
        this->kill();
        return;
      }
    }

    iterator = next;
  }
}

/* Net als de bom doen we alsof dit een vierkant is. */
sf::FloatRect bullet_c::get_bounds(void)
{
  return figure->getGlobalBounds();
}
