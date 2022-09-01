#include "bomb.h"
#include "game.h"
#include "player.h"
#include "fueltank.h"
#include "asteroid.h"
#include "gameobjecthandler.h"

/* Bommen worden gemaakt door de speler. */
bomb_c::bomb_c(float x0, float y0,float vx0) : gameobject_c(x0,y0,vx0,4,bomb_id)
{
  /* Simpel weg een witte gevulde cirkel. */
  figure = new sf::CircleShape(5,5);
  figure->setFillColor(sf::Color::White);
  figure->setPosition(sf::Vector2f(x0,y0));
}

bomb_c::~bomb_c()
{
  delete figure;
}

void bomb_c::render(sf::RenderWindow *w)
{
  figure->setPosition(this->x, this->y);
  w->draw(*figure);
}

void bomb_c::tick(void)
{
  /* Beweging van de bom moet berekend worden. */
  y += vy;
  x += vx;

  /* Collision detection */
  gameobject_c *iterator = gameobject_handler_c::get_handler()->get_list();
  sf::FloatRect bullet_rect = get_bounds();

  /* Door de lijst gaan en elke keer als er een interessant object is kijken of er collision is. */
  while(iterator)
  {
    gameobject_c *next = iterator->get_next();
    if(iterator->get_id() == fuel_id)
    {
      if(((fueltank_c*)iterator)->get_bounds().intersects(bullet_rect))
      {
        player_c *p = gameobject_handler_c::get_handler()->get_player();
        p->increase_fuel_level(500);    // Fuel tanks geven fuel zodat de speler verder kan blijven vliegen.
        iterator->kill();               // Er wordt gewerkt met een kill() methode
        this->kill();                   // aangezien objecten in een lijst zitten en hierdoor nog gebladerd wordt!
        return; // De bullet heeft iets geraakt, we mogen uit de loop want de bullet kan niet ook nog andere zaken raken!
      }
    }
    if(iterator->get_id() == asteroid_id)
    {
      if(((asteroid_c*)iterator)->get_bounds().intersects(bullet_rect))
      {
        /* Asteroide kapot maken levert de speler punten op. */
        gameobject_handler_c::get_handler()->get_player()->increase_score(1);
        iterator->kill();   // opnieuw kill() methode anders memory problemen!
        this->kill();
        return;
      }
    }
    iterator = next;
  }

  /* Bommen vallen naar beneden en de y-as is gericht naar beneden. */
  if(this->y > GAME_HEIGHT)
  {
    this->kill();   // Als de bom uit het scherm is mag deze verwijderd worden.
  }
}

/* Voor de collision detection doen we alsof de bommen vierkanten zijn dit is eenvoudiger. */
sf::FloatRect bomb_c::get_bounds(void)
{
  return figure->getGlobalBounds();
}
