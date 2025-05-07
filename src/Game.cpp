
#include "Game.h"

Game::Game(sf::RenderWindow& game_window)
    : window(game_window)
{

}

bool Game::init()
{
    bool success = true;

	turn_timer = sf::Clock();
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

    // TODO: Code for updating current menu

    // Check for next turn calculation
    if (processing_turn && turn_delay_timer.getElapsedTime().asMilliseconds() >= turn_delay)
    {
        run_turn = true;
        turn_delay_timer.restart();
    }
    // Process enemy turn iteration
    if (processing_turn && run_turn)
    {
        run_turn = false;
        //std::cout << "Turn " << turn_iteration << " complete" << std::endl;

        if (loaded_level->process_turn(turn_iteration))
        {
            processing_turn = false;
            turn_iteration = 0;

			turn_timer.restart();
		}
        else
        {
            turn_iteration++;
        }
    }
    else if (!processing_turn)
    {
        timer_aware = loaded_level->is_aware();
		timer_alert = loaded_level->is_alert();

        // Checking for debug turns
        if (debug_turns)
        {
			action_remaining = action_total;

			// Set stopwatch animation for action counter
            stopwatch_text.setString("9:99");
            stopwatch_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
        }
        else
        {
            // Calculate turn timer string
            float turn_length_temp = turn_length * (timer_alert ? alert_mult : (timer_aware ? aware_mult : 1.f));
            int time = turn_length_temp - turn_timer.getElapsedTime().asSeconds();
            if (time < 0)
            {
                time = 0;
            }
            std::string time_string_temp = std::to_string(time % 60);
            if (time % 60 < 10)
            {
                time_string_temp = "0" + time_string_temp;
            }
            stopwatch_text.setString(std::to_string(time / 60) + ":" + time_string_temp);

            sf::Color colour = sf::Color(193, 203, 220);
            if (timer_aware)
            {
                colour = sf::Color(254, 231, 97);
                if (timer_alert)
                {
                    colour = sf::Color(255, 0, 68);
                }
            }
            stopwatch_text.setColor(colour);

            // Check if turn timer is up
            if (time <= 0 && !processing_turn && !debug_turns)
            {
                end_turn();
            }

            // Set stopwatch animation for action counter
            int animation_num = action_total - action_remaining;
            if (animation_num < 0)
            {
                animation_num = 0;
            }
            if (animation_num > action_total)
            {
                animation_num = action_total;
            }
            stopwatch_sprite.setTextureRect(sf::IntRect((animation_num) * 32, 0, 32, 32));
        }
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

    // Toggle debug options
    case sf::Keyboard::Scancode::Num1:
		debug_turns = !debug_turns;
        break;
	case sf::Keyboard::Scancode::Num2:
		//debug_view = !debug_view;
        break;

    // Force the end of a turn for debugging
    case sf::Keyboard::Scancode::Space:
		if (!processing_turn && debug_turns && check_gamestate(GamestateRequest::CanGameplayInput))
		{
            end_turn();
		}
		break;

    // Player movement
    case sf::Keyboard::Scancode::Up:
        if (!in_menu)
        {
            if (!check_gamestate(GamestateRequest::CanGameplayInput))
            {
                break;
            }
			if (action_remaining > 0)
			{
				loaded_level->player_input(Entity::MoveType::Forward);
				action_remaining--;
			}
            if (action_remaining <= 0)
			{
				end_turn();
			}
        }
        else
        {
            // TODO: Add code for navigating current menu
        }
        break;
	case sf::Keyboard::Scancode::Down:
        if (!in_menu)
        {
            if (!check_gamestate(GamestateRequest::CanGameplayInput))
            {
                break;
            }
            /*if (action_remaining > 0)
            {
                loaded_level->player_input(Entity::MoveType::Backward);
                action_remaining--;
            }
            if (action_remaining <= 0)
            {
                end_turn();
            }*/
        }
        else
        {
            // TODO: Add code for navigating current menu
        }
        break;
	case sf::Keyboard::Scancode::Left:
        if (!in_menu)
        {
            if (!check_gamestate(GamestateRequest::CanGameplayInput))
            {
                break;
            }
			loaded_level->player_input(Entity::MoveType::LeftTurn);
            /*if (action_remaining > 0)
            {
                loaded_level->player_input(Entity::MoveType::Left);
                action_remaining--;
            }
            if (action_remaining <= 0)
            {
                end_turn();
            }*/
        }
        else
        {
            // TODO: Add code for navigating current menu
        }
		break;
	case sf::Keyboard::Scancode::Right:
        if (!in_menu)
        {
            if (!check_gamestate(GamestateRequest::CanGameplayInput))
            {
                break;
            }
			loaded_level->player_input(Entity::MoveType::RightTurn);
            /*if (action_remaining > 0)
            {
                loaded_level->player_input(Entity::MoveType::Right);
                action_remaining--;
            }
            if (action_remaining <= 0)
            {
                end_turn();
            }*/
        }
        else
        {
            // TODO: Add code for navigating current menu
        }
        break;

    case sf::Keyboard::Scancode::Z:
        if (!in_menu)
        {
            if (!check_gamestate(GamestateRequest::CanGameplayInput))
            {
                break;
            }
			if (action_remaining > 0)
			{
				loaded_level->player_interact();
				action_remaining--;
			}
            if (action_remaining <= 0)
            {
                end_turn();
            }
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

void Game::end_turn()
{
    processing_turn = true;
    run_turn = true;
    turn_delay_timer.restart();

	//turn_timer.restart();
    action_remaining = action_total;

    stopwatch_sprite.setTextureRect(sf::IntRect(action_total * 32, 0, 32, 32));
	stopwatch_text.setString("0:00");
}