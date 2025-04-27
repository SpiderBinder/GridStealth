
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
		break;

	case EnemyType::DemoEnemy2:
		collision = CollisionType::Solid;

		move_sequence = { MoveType::Forward, MoveType::Forward, MoveType::Forward };
		move_collision = { MoveType::Flip };
		break;

	case EnemyType::DemoEnemy3:
		collision = CollisionType::Solid;

		// TODO: Think of move sequence for demo enemy 3
		move_sequence = {  };
		move_collision = {  };
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

	return success;
}


EnemyType Enemy::get_enemy_type()
{
	return enemy_type;
}

std::vector<sf::Vector2i> Enemy::get_view_area()
{
	return view_area;
}