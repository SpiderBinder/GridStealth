
#ifndef GRIDSTEALTH_GAME_H
#define GRIDSTEALTH_GAME_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Environment/Level.h"

class Game
{
    // Rendering
    sf::RenderWindow& window;

    sf::Texture stopwatch_texture;
	sf::Sprite stopwatch_sprite;
    sf::Font stopwatch_font;
	sf::Text stopwatch_text;

    // Game Objects
	Level* loaded_level = nullptr;
	Level testlevel;

    // Gamestates & Gamestate Calculation
    //bool paused = false;
	bool in_menu = false;

    // Player turn items
    sf::Clock turn_timer;
    int action_total = 3;
	int action_remaining = action_total;
    float turn_length = 10.f;
    float aware_mult = 0.5f;
    float alert_mult = 0.2f;
    bool timer_aware = false;
	bool timer_alert = false;
    // Enemy turn items
    bool processing_turn = false;
    int turn_iteration = 0;
    sf::Clock turn_delay_timer;
    float turn_delay = 500.f;
    bool run_turn = false;

    // Debug/Dev stuff
    float framerate = 0;

    bool debug_turns = false;
    //bool debug_view = false;

    enum GamestateRequest
    {
        CanGameplayInput,
		CanMenuInput,

    };
    bool check_gamestate(GamestateRequest request);

	void end_turn();

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