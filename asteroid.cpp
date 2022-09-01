#include "asteroid.h"
#include "game.h"


unsigned int asteroid_c::n_asteroids = 0;

asteroid_c::asteroid_c(float x0,float y0) : gameobject_c(x0,y0,ASTEROID_SPEED,0,asteroid_id)
{
  /* Het aantal wordt bijgehouden zodanig dat er niet teveel zijn.*/
  n_asteroids++;

  this->width = ASTEROID_WIDTH;
  this->height = ASTEROID_WIDTH;

  /* Texture zorgt dat de asteroide geen wit vierkant is maar een mooi plaatje*/
  texture = new sf::Texture();
  /* meerder sprites in de sheet, sf::IntRect snijd de juiste eruit. */
  texture->loadFromFile("spritesheet.png", sf::IntRect(32, 1, 16, 16));

  /* De grafische figuur dat de asteroide voorstelt. */
  figure = new sf::RectangleShape(sf::Vector2f(width,height));
  figure->setPosition(sf::Vector2f(x0,y0));
  figure->setTexture(texture, true);

}

asteroid_c::~asteroid_c()
{
  n_asteroids--;
  delete figure;
}

void asteroid_c::render(sf::RenderWindow *w)
{
  /* Als de asteroide uit beeld is mag deze verwijderd worden.*/
  if(this->y > GAME_HEIGHT || w->mapCoordsToPixel(sf::Vector2f(this->x,this->y)).x < 0)
  {
    /* "delete this" is te gevaarlijk, we zitten namelijk nog in een itteratie van de gameobject handler.*/
    /* Daarom heeft elke game object een kill methode zodanig dat deze later als het veilig is wordt opgeruimd. */
    this->kill();
    return;
  }

  figure->setPosition(this->x, this->y);
  w->draw(*figure);
}

void asteroid_c::tick(void)
{
  y += vy;
  x += vx;

  /* Collision detection */
  player_c *p = gameobject_handler_c::get_handler()->get_player();
  sf::FloatRect bullet_rect = get_bounds();

  if(p->get_bounds().intersects(bullet_rect))
  {
    /* Spel is gedaan en geven mee dat het is door crash met asteroide. */
    game_c::game_over(GAME_OVER_STATE_ASTEROID_CRASH);
  }
}

/* methode voor collision detection */
sf::FloatRect asteroid_c::get_bounds(void)
{
  return figure->getGlobalBounds();
}
