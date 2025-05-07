
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
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

	return success;
}


void Player::update_sprite_direction()
{
	if (direction.y == -1)
	{
		sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	}
	else if (direction.x == 1)
	{
		sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
	}
	else if (direction.y == 1)
	{
		sprite.setTextureRect(sf::IntRect(16, 16, 16, 16));
	}
	else if (direction.x == -1)
	{
		sprite.setTextureRect(sf::IntRect(0, 16, 16, 16));
	}

	sprite.setPosition(get_real_position());
}