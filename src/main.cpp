
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
    std::cout << "Hello World!" << std::endl;

    sf::RenderWindow window(sf::VideoMode(1080, 720), "Hello Window!");
    window.setFramerateLimit(60);

    sf::Clock clock;

    Game game(window);

    if (!game.init())
    {
        return 1;
    }

    while (window.isOpen())
    {
        sf::Event event;

        //calculate delta time
        sf::Time time = clock.restart();
        float dt = time.asSeconds();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::KeyReleased)
            {
                game.key_input(event);
            }

            if (event.type == sf::Event::MouseButtonPressed ||
                event.type == sf::Event::MouseButtonReleased)
            {
                game.mouse_input(event);
            }
        }

        window.clear(sf::Color::Black);

        
        window.display();
    }    

    return 0;
}