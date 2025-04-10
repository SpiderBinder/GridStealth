
#include "Game.h"

Game::Game(sf::RenderWindow& game_window)
    : window(game_window)
{

}

bool Game::init()
{
    bool success = true;

    if (!testtexture.loadFromFile("../content/defTile.png"))
    {
        std::cout << "Error: Failed to load \'content/defTile.png\'" << std::endl;
		success = false;
    }
    testobject;
	testobject.init(&testtexture);

	// NOTE: For debug only, remove after
    Level testlevel("../content/LevelData/testlevel.txt");



    return success;
}

void Game::update(float dt)
{
    testobject.set_position(sf::Vector2i(100, 100));
}

void Game::render()
{
	testobject.render(window);
}


void Game::key_input(sf::Event event)
{
	bool key_down = event.type == sf::Event::KeyPressed;

    
}

void Game::mouse_input(sf::Event event)
{
	bool mouse_down = event.type == sf::Event::MouseButtonPressed;


}