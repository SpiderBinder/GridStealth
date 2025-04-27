
#ifndef GRIDSTEALTH_GAME_H
#define GRIDSTEALTH_GAME_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Environment/Level.h"

class Game
{
    sf::RenderWindow& window;

    // Misc 'Game' items
    sf::Clock turn_delay_timer;
    int turn_iteration = 0;
    bool run_turn = false;

    // Objects
	Level* loaded_level;
	Level testlevel;

    // Gamestates
    bool processing_turn = false;

public:
    Game(sf::RenderWindow& game_window);

    bool init();
    void update(float dt);
    void render();

    void key_input(sf::Event event);
    void mouse_input(sf::Event event);

    // TODO: Write function return an enum for what gamestate the game is in
    // (what kind of inputs can it take eg. can't take movement when processing turn but can pause)
    // Would check the gamestate booleans for this
	// GameState get_gamestate();
    // NOTE: Make this private? Would only be used inside the Game class
};

#endif // GRIDSTEALTH_GAME_H