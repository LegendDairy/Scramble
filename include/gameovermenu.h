#ifndef gameover_h
#define gameover_h

#include "gameobject.h"
#include "gameobjecthandler.h"
#include <SFML/Graphics.hpp>

#define GAME_OVER_FONT_SIZE               150
#define GAME_OVER_STATE_TEXT_FONT_SIZE    30
#define GAME_OVER_STRING_X                GAME_WIDTH/2 - 120
#define GAME_OVER_STRING_Y                GAME_HEIGHT/2 - 250

/* De verschillende mogelijkheden voor game_over_menu_c::state */
#define GAME_OVER_STATE_WON               0
#define GAME_OVER_STATE_MAP_CRASH         1
#define GAME_OVER_STATE_NO_FUEL           2
#define GAME_OVER_STATE_ASTEROID_CRASH    3

//static const char *game_over_strings[4];

/* Menu dat op het einde van het spel de score verteld en manier dat het einde bereikt werd. */
/* Gaat in de game_over_list van de game_object_hancler_c*/
/* Wordt getoont in de GAME_STATE_PAUSED. */
class game_over_menu_c
{
  private:
    float x,y;
    sf::Text *game_over_text;
    sf::Text *game_over_state_text;
    sf::Font *font;
    sf::Font *font_arial;

    /* Game over kan op verschillende wijzen bereikt worden,
    state bepaalde welke: crash, geen fuel, gewonnen... */
    static int state;
    static unsigned int score;
    friend class game_c;
    /* Vier strings voor de verschillende manieren dat men de game kan beeindigen. */
    static const std::string state_strings_array[4];
  public:
    /* Constructor, input de manier waarop game over bereikt werd (zie GAME_OVER_STATE_* defines) */
    game_over_menu_c(void);
    ~game_over_menu_c();
    void render(sf::RenderWindow *w);
    void tick();
};

#endif
