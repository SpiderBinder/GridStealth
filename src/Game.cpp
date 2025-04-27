
#include "Game.h"

Game::Game(sf::RenderWindow& game_window)
    : window(game_window)
{

}

bool Game::init()
{
    bool success = true;

    turn_delay_timer = sf::Clock();

	// NOTE: For early builds only, to be replaced by multiple levels
    testlevel = Level("../content/LevelData/testlevel.txt");
    if (!testlevel.init("DemoTileset"))
    {
		std::cout << "Error: Level failed to initalise" << std::endl;
        success = false;
    }
	loaded_level = &testlevel;



    return success;
}

void Game::update(float dt)
{
    if (processing_turn && turn_delay_timer.getElapsedTime().asMilliseconds() >= 1000)
    {
        run_turn = true;
        turn_delay_timer.restart();
    }
    if (processing_turn && run_turn)
    {
        run_turn = false;
        std::cout << "Turn " << turn_iteration << " complete" << std::endl;

        if (loaded_level->process_turn(turn_iteration))
        {
            processing_turn = false;
            turn_iteration = 0;
		}
        else
        {
            turn_iteration++;
        }
    }
    else
    {

    }
}

void Game::render()
{
    loaded_level->render(window);
}


void Game::key_input(sf::Event event)
{
	bool key_down = event.type == sf::Event::KeyPressed;

    switch (event.key.scancode)
    {
    case sf::Keyboard::Scancode::Space:
		if (!processing_turn)
		{
			processing_turn = true;
			run_turn = true;
            turn_delay_timer.restart();
		}
		break;
    }
}

void Game::mouse_input(sf::Event event)
{
	bool mouse_down = event.type == sf::Event::MouseButtonPressed;


}