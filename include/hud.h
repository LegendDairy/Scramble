#ifndef hud_h
#define hud_h

#include "gameobject.h"
#include "gameobjecthandler.h"
#include "game.h"
#include <SFML/Graphics.hpp>

#define SCORE_FONT_SIZE 60

/* Heads up display: Hier de score en fuel niveau dat de speler te zien krijgt. */
class hud_c : public gameobject_c
{
  private:
    /* tekst en hun fonts om te tonen. */
    sf::Text *score_text;
    sf::Font *font;
    std::string str;

  public:
    void render(sf::RenderWindow *w);
    void tick();
    hud_c();
    ~hud_c();
};

#endif
