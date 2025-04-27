
#include "Entity.h"

Entity::Entity()
{

}

Entity::Entity(CollisionType collision, sf::Vector2i position, sf::Vector2i direction)
{
	this->collision = collision;
	this->position = position;
	this->direction = direction;
}

Entity::~Entity()
{

}


void Entity::render(sf::RenderWindow& window)
{
	sprite.setPosition(get_real_position());
	window.draw(sprite);
}

sf::Vector2i Entity::get_next_position(MoveType move)
{
	sf::Vector2i new_position = position;

	// Calculate new position from move sequence
	switch (move)
	{
	case Entity::MoveType::Forward:
		new_position += direction;
		break;
	case Entity::MoveType::Right:
		new_position += sf::Vector2i(-direction.y, direction.x);
		break;
	case Entity::MoveType::Backward:
		new_position += this->get_direction() * -1;
		break;
	case Entity::MoveType::Left:
		new_position += sf::Vector2i(direction.y, -direction.x);
		break;
	case Entity::MoveType::RightTurn:
		direction = sf::Vector2i(-direction.y, direction.x);
		break;
	case Entity::MoveType::LeftTurn:
		direction = sf::Vector2i(direction.y, -direction.x);
		break;
	case Entity::MoveType::Flip:
		direction *= -1;
		break;
	case Entity::MoveType::Wait:
		break;
	default:
		break;
	}

	return new_position;
}


sf::Vector2i Entity::get_direction()
{
	return direction;
}

std::vector<Entity::MoveType> Entity::get_move_sequence()
{
	return move_sequence;
}

std::vector<Entity::MoveType> Entity::get_move_collision()
{
	return move_collision;
}


void Entity::set_direction(sf::Vector2i new_direction)
{
	direction = new_direction;
}