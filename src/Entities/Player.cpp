
#include "Player.h"

Player::Player()
{
	// Default constructor
}

Player::Player(sf::Vector2i position, sf::Vector2i direction)
	: Entity(CollisionType::Solid, position, direction)
{
	// Constructor with position and direction
}


bool Player::init()
{
	bool success = true;

	if (!texture.loadFromFile("../content/Assets/Entities/DemoPlayer.png"))
	{
		std::cout << "Failed to load player texture" << std::endl;
		success = false;
	}
	sprite.setTexture(texture);

	return success;
}