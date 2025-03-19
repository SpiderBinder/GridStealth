
#ifndef GRIDSTEALTH_GAME_H
#define GRIDSTEALTH_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
    sf::RenderWindow* window;

public:
    Game(sf::RenderWindow& game_window);

    bool init();
    void update(float dt);
    void render();

    void key_input(sf::Event event);
    void mouse_input(sf::Event event);
};

#endif // GRIDSTEALTH_GAME_H