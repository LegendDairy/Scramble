#include "hud.h"

/* Heads up display. Toont de score en fuel level */
hud_c::hud_c() : gameobject_c(20,20,0,0,hud_id)
{
  font = new sf::Font();
  font->loadFromFile("FontFile.ttf");

  score_text = new sf::Text();
  score_text->setFont(*font);
  score_text->setFillColor(sf::Color::White);
  score_text->setCharacterSize(SCORE_FONT_SIZE);
  score_text->setPosition(sf::Vector2f(this->x,this->y));
}

hud_c::~hud_c()
{
  delete score_text;
  delete font;
}

void hud_c::render(sf::RenderWindow *w)
{
  player_c *p = gameobject_handler_c::get_handler()->get_player();
  unsigned int score = p->get_score();
  unsigned int fuel_level = p->get_fuel_level();

  str = "Score: " + std::to_string(score) + "\n Fuel level: " + std::to_string(fuel_level);
  score_text->setString(str);
  score_text->setPosition(w->mapPixelToCoords(sf::Vector2i(this->x,this->y)));
  w->draw(*score_text);
}

void hud_c::tick(void)
{

}
