
#ifndef GRIDSTEALTH_GAME_H
#define GRIDSTEALTH_GAME_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Environment/Level.h"

class Game
{
    sf::RenderWindow& window;

	sf::Texture testtexture;
    GameObject testobject;

public:
    Game(sf::RenderWindow& game_window);

    bool init();
    void update(float dt);
    void render();

    void key_input(sf::Event event);
    void mouse_input(sf::Event event);
};

#endif // GRIDSTEALTH_GAME_H