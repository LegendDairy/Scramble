#include "gameovermenu.h"
#include "game.h"

const std::string game_over_menu_c::state_strings_array[4] =
{"Congratulations, you won!", "You crashed on the ground!", "You ran out of fuel!",
"You collided with an asteroid!"};

int game_over_menu_c::state = 0;
unsigned int game_over_menu_c::score = 0;


game_over_menu_c::game_over_menu_c(void)
{
  x = GAME_OVER_STRING_X;
  y = GAME_OVER_STRING_Y;

  font = new sf::Font();
  font->loadFromFile("FontFile.ttf");

  font_arial = new sf::Font();
  font_arial->loadFromFile("arial.ttf");

  game_over_text = new sf::Text();
  game_over_text->setFont(*font);
  game_over_text->setFillColor(sf::Color::White);

  game_over_state_text = new sf::Text();
  game_over_state_text->setFont(*font_arial);
  game_over_state_text->setFillColor(sf::Color::White);
}

game_over_menu_c::~game_over_menu_c()
{

  delete game_over_text;
  delete game_over_state_text;
  delete font;
  delete font_arial;
}

void game_over_menu_c::render(sf::RenderWindow *w)
{
  if(state==0)
    game_over_text->setString("The End");
  else
    game_over_text->setString("Game Over");

  game_over_state_text->setString(state_strings_array[state] + "\nScore: " + std::to_string(score) +"\nPress Enter to restart.");

  game_over_text->setCharacterSize(GAME_OVER_FONT_SIZE);
  game_over_state_text->setCharacterSize(GAME_OVER_STATE_TEXT_FONT_SIZE);


  game_over_text->setPosition(w->mapPixelToCoords(sf::Vector2i(this->x,this->y)));
  game_over_state_text->setPosition(w->mapPixelToCoords(sf::Vector2i(this->x,this->y+150)));

  w->draw(*game_over_text);
  w->draw(*game_over_state_text);
}

void game_over_menu_c::tick(void)
{

}
