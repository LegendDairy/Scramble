#include "pausemenu.h"
#include "game.h"

pause_menu_c::pause_menu_c()
{
  x = PAUZE_STRING_X;
  y = PAUZE_STRING_Y;
  font = new sf::Font();
  font->loadFromFile("FontFile.ttf");

  font_arial = new sf::Font();
  font_arial->loadFromFile("arial.ttf");

  pause_text = new sf::Text();
  continue_text = new sf::Text();

  pause_text->setFont(*font);
  pause_text->setFillColor(sf::Color::White);
  continue_text->setFont(*font_arial);
  continue_text->setFillColor(sf::Color::White);

  pause_text->setString("Game Paused");
  pause_text->setCharacterSize(PAUZE_FONT_SIZE);

  continue_text->setString("Press Escape to continue.");
  continue_text->setCharacterSize(PAUZE_CONTINUE_FONT_SIZE);
}
pause_menu_c::~pause_menu_c()
{
  delete pause_text;
  delete continue_text;
  delete font;
  delete font_arial;
}

void pause_menu_c::render(sf::RenderWindow *w)
{
  pause_text->setPosition(w->mapPixelToCoords(sf::Vector2i(this->x,this->y)));
  continue_text->setPosition(w->mapPixelToCoords(sf::Vector2i(this->x,this->y+130)));
  w->draw(*pause_text);
  w->draw(*continue_text);

}

void pause_menu_c::tick(void)
{

}
