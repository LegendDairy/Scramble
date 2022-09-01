#ifndef pausemenu_h
#define pausemenu_h

#include "gameobject.h"
#include "gameobjecthandler.h"
#include <SFML/Graphics.hpp>

#define PAUZE_FONT_SIZE             100
#define PAUZE_CONTINUE_FONT_SIZE    20
#define PAUZE_STRING_X              GAME_WIDTH/2 - 120
#define PAUZE_STRING_Y              GAME_HEIGHT/2 - 200


class pause_menu_c
{
  private:
    /* Variabelen voor de tekst en fonts die op het scherm moeten*/
    float x,y;
    sf::Text *pause_text;
    sf::Text *continue_text;
    sf::Font *font;
    sf::Font *font_arial;


  public:
    void render(sf::RenderWindow *w);
    void tick();
    pause_menu_c();
    ~pause_menu_c();
};

#endif
