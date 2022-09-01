#include "fueltank.h"

/* Fuel tanks liggen verspreid over de map en moeten met bommen geraakt worden om verder te kunnen blijven vliegen. */
fueltank_c::fueltank_c(float x0, float y0, float vx0, float vy0, ID id) : gameobject_c(x0,y0,vx0,vy0,id)
{
  this->x = x0;
  this->y = y0-FUEL_HEIGTH;
  this->vx = 0;
  this->vy = 0;
  this->id = fuel_id;

  this->width = FUEL_WIDTH;
  this->height = FUEL_HEIGTH;

  /* texture zorgt dat het een mooie afbeelding is en niet gewoon een vierkant. */
  texture = new sf::Texture();
  texture->loadFromFile("fuel.png", sf::IntRect(1, 1, 32, 32));

  figure = new sf::RectangleShape(sf::Vector2f(width,height));
  figure->setPosition(sf::Vector2f(x0,y0));
  figure->setTexture(texture, true);

}

void fueltank_c::tick(void)
{

}

fueltank_c::~fueltank_c()
{
  delete figure;
  delete texture;
}


void fueltank_c::render(sf::RenderWindow *w)
{
figure->setPosition(x, y);
w->draw(*figure);
}
/* Levert de rand van de figuur om botsingen te detecteren. */
sf::FloatRect fueltank_c::get_bounds(void)
{
  return figure->getGlobalBounds();
}
