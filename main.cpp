#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "gameobjecthandler.h"
#include "gameobject.h"
#include "map.h"
#include "player.h"
#include "fueltank.h"
#include "asteroid.h"
#include "hud.h"
#include "pausemenu.h"

int main()
{
    /* Maakt een window waarin gerenderd kan worden */
    sf::RenderWindow window(sf::VideoMode(GAME_WIDTH,GAME_HEIGHT), "Scramble C++ Port");
    /* De view zal zorgen voor een beweegbaar camera zodanig dat het lijkt alsof het schip constant vliegt */
    sf::View view(sf::FloatRect(0.0f, 0.0f, GAME_WIDTH, GAME_HEIGHT));
    /* Frame rate, en dus ook de gameloop hieronder zal gelimiteerd worden tot 60fps.
    Hierdoor zullen de ticks ook min of meer constant zijn, een soort delta t. */
    window.setFramerateLimit(60);

    /* De game class bevat veel algeme zaken die de game draaiend houd. */
    game_c *game = game_c::setup(&window, &view);
    game->game_start();

    /* Deze loop zordt dat er constant gerenderd wordt, dat objecten bewegen en interacties/collisions gedtecteerd worden.*/
    game->game_loop();

    // Dit wordt enkel bereikt als de speler op het kruisje klikt.

    return 0;
}
