
#include "Enemy.h"

Enemy::Enemy()
	: Enemy(EnemyType::DemoEnemy1, sf::Vector2i(0, 0))
{
	
}

Enemy::Enemy(EnemyType type, sf::Vector2i position, sf::Vector2i direction)
{
	enemy_type = type;
	this->position = position;
	this->direction = direction;
	
	// Hardcoded enemy move patterns and view areas are assigned here
	switch (enemy_type)
	{
	case EnemyType::DemoEnemy1:
		collision = CollisionType::Solid;

		move_sequence = { MoveType::Forward, MoveType::Forward };
		move_collision = { MoveType::RightTurn };

		view_area = { sf::Vector2i(0, -1) };
		break;

	case EnemyType::DemoEnemy2:
		collision = CollisionType::Solid;

		move_sequence = { MoveType::Forward, MoveType::Forward, MoveType::Forward };
		move_collision = { MoveType::Flip };

		view_area = { sf::Vector2i(0, -1), sf::Vector2i(1, -1), sf::Vector2i(-1, -1) };
		break;

	case EnemyType::DemoEnemy3:
		collision = CollisionType::Solid;

		move_sequence = { MoveType::LeftTurn };
		move_collision = {  };

		view_area = { sf::Vector2i(0, -1), sf::Vector2i(1, -1), sf::Vector2i(-1, -1), sf::Vector2i(0, -2), sf::Vector2i(1, -2), sf::Vector2i(-1, -2) };
		break;
	}
}


bool Enemy::init()
{
	bool success = true;

	switch (enemy_type)
	{
	case EnemyType::DemoEnemy1:
		if (!texture.loadFromFile("../content/Assets/Entities/DemoEnemy1.png"))
		{
			std::cout << "Failed to load enemy texture: DemoEnemy1.png" << std::endl;
			success = false;
		}
		sprite.setTexture(texture);
		break;
	case EnemyType::DemoEnemy2:
		if (!texture.loadFromFile("../content/Assets/Entities/DemoEnemy2.png"))
		{
			std::cout << "Failed to load enemy texture: DemoEnemy2.png" << std::endl;
			success = false;
		}
		sprite.setTexture(texture);
		break;
	case EnemyType::DemoEnemy3:
		if (!texture.loadFromFile("../content/Assets/Entities/DemoEnemy3.png"))
		{
			std::cout << "Failed to load enemy texture: DemoEnemy3.png" << std::endl;
			success = false;
		}
		sprite.setTexture(texture);
		break;
	default:
		break;
	}

	if (!view_texture.loadFromFile("../content/Assets/Entities/ViewSquare.png"))
	{
		std::cout << "Failed to load view area texture" << std::endl;
		success = false;
	}
	view_sprite.setTexture(view_texture);

	//set_direction(direction);

	return success;
}

void Enemy::render(sf::RenderWindow& window)
{
	sprite.setPosition(position.x * 64, position.y * 64);
	window.draw(sprite);

	// Draw view area
	for (sf::Vector2i offset : view_area)
	{
		if (direction.y == -1)
		{
			view_sprite.setPosition((position.x + offset.x) * 64, (position.y + offset.y) * 64);
		}
		else if (direction.y == 1)
		{
			view_sprite.setPosition((position.x - offset.x) * 64, (position.y - offset.y) * 64);
		}
		else if (direction.x == -1)
		{
			view_sprite.setPosition((position.x + offset.y) * 64, (position.y - offset.x) * 64);
		}
		else if (direction.x == 1)
		{
			view_sprite.setPosition((position.x - offset.y) * 64, (position.y + offset.x) * 64);
		}

		window.draw(view_sprite);
	}
}

sf::Sprite& Enemy::get_view_sprite()
{
	return view_sprite;
}

EnemyType Enemy::get_enemy_type()
{
	return enemy_type;
}

std::vector<sf::Vector2i> Enemy::get_view_area()
{
	std::vector<sf::Vector2i> return_area;

	// NOTE: In memory of when I used '=' instead of '==' like a buffoon
	// NOTE: An utter dolt
	// NOTE: A complete fool
	// Return absolute positions instead of relative to Enemy
	for (sf::Vector2i area : view_area)
	{
		if (direction.y == 1)
		{
			area = sf::Vector2i(-area.x, -area.y);
		}
		else if (direction.x == -1)
		{
			area = sf::Vector2i(area.y, -area.x);
		}
		else if (direction.x == 1)
		{
			area = sf::Vector2i(-area.y, area.x);
		}

		area += position;

		return_area.push_back(area);
	}

	return return_area;
}