
#include "Game.h"

Game::Game(sf::RenderWindow& game_window)
    : window(&game_window)
{

}

bool Game::init()
{
    bool success = true;



    return success;
}

void Game::update(float dt)
{

}

void Game::render()
{

}


void Game::key_input(sf::Event event)
{
	bool key_down = event.type == sf::Event::KeyPressed;

    
}

void Game::mouse_input(sf::Event event)
{
	bool mouse_down = event.type == sf::Event::MouseButtonPressed;


}