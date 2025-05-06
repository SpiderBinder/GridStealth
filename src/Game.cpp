
#include "Game.h"

Game::Game(sf::RenderWindow& game_window)
    : window(game_window)
{

}

bool Game::init()
{
    bool success = true;

    turn_delay_timer = sf::Clock();

    // Load stopwatch assets
    if (!stopwatch_texture.loadFromFile("../content/Assets/UI/Stopwatch.png"))
    {
        std::cout << "Error: Stopwatch texture failed to load" << std::endl;
        success = false;
    }
    stopwatch_sprite.setTexture(stopwatch_texture);
    stopwatch_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    stopwatch_sprite.setScale(4, 4); // NOTE: Temporary while camera isn't set up
    stopwatch_sprite.setPosition(window.getSize().x - stopwatch_sprite.getGlobalBounds().width - 16, 16);
    if (!stopwatch_font.loadFromFile("../content/Assets/UI/StopwatchNumbers.ttf"))
    {
        std::cout << "Error: Stopwatch font failed to load" << std::endl;
        success = false;
    }
	stopwatch_text.setFont(stopwatch_font);
	stopwatch_text.setCharacterSize(64);// NOTE: "* 4" temporary while camera isn't set up
	stopwatch_text.setFillColor(sf::Color(193, 203, 220));
    stopwatch_text.setPosition(stopwatch_sprite.getPosition() + sf::Vector2f(9 * 4, 8));
    stopwatch_text.setString("0:00");

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
	framerate = 1.0f / dt;

    if (processing_turn && turn_delay_timer.getElapsedTime().asMilliseconds() >= turn_delay)
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

	window.draw(stopwatch_sprite);
    window.draw(stopwatch_text);
}


void Game::key_input(sf::Event event)
{
    // NOTE: Currently unused
	//bool key_down = event.type == sf::Event::KeyPressed;

    switch (event.key.scancode)
    {
    // NOTE: Temporary for debug
    case sf::Keyboard::Scancode::F:
		std::cout << "Framerate: " << framerate << std::endl;
        break;

    // NOTE: Temporary force turnstep for testing
    case sf::Keyboard::Scancode::Space:
		if (!processing_turn)
		{
			processing_turn = true;
			run_turn = true;
            turn_delay_timer.restart();
		}
		break;

    case sf::Keyboard::Scancode::Up:
        if (check_gamestate(GamestateRequest::CanGameplayInput))
        {
            loaded_level->player_input(Entity::MoveType::Forward);
        }
        break;
	case sf::Keyboard::Scancode::Down:
        if (check_gamestate(GamestateRequest::CanGameplayInput))
        {
            loaded_level->player_input(Entity::MoveType::Backward);
        }
        break;
	case sf::Keyboard::Scancode::Left:
		if (check_gamestate(GamestateRequest::CanGameplayInput))
		{
			loaded_level->player_input(Entity::MoveType::Left);
		}
		break;
	case sf::Keyboard::Scancode::Right:
        if (check_gamestate(GamestateRequest::CanGameplayInput))
        {
            loaded_level->player_input(Entity::MoveType::Right);
        }
        break;
    default:
        break;
    }
}

void Game::mouse_input(sf::Event event)
{
	bool mouse_down = event.type == sf::Event::MouseButtonPressed;


}


bool Game::check_gamestate(GamestateRequest request)
{
	bool result = false;

    // NOTE: Update when more gamestates are added (eg main menu, paused, etc)
	switch (request)
	{
	case GamestateRequest::CanGameplayInput:
		result = !processing_turn;
		break;
	case GamestateRequest::CanMenuInput:
		result = !processing_turn;
		break;
	default:
		break;
	}

	return result;
}