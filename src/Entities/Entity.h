
#ifndef GRIDSTEALTH_ENTITIES_ENTITY_H
#define GRIDSTEALTH_ENTITIES_ENTITY_H

#include <iostream>
#include <string>
#include <vector>

#include "../GameObject.h"

class Entity : public GameObject
{
public:
	enum MoveType
	{
		Forward,
		Right,
		Backward,
		Left,
		RightTurn,
		LeftTurn,
		Flip,
		Wait,
		End
	};

protected:
	sf::Vector2i direction = sf::Vector2i(0, -1);

	std::vector<MoveType> move_sequence;
	std::vector<MoveType> move_collision;

public:
	Entity();
	Entity(CollisionType collision, sf::Vector2i position, sf::Vector2i direction = sf::Vector2i(0, -1));
	~Entity();

	void render(sf::RenderWindow& window) override;
	sf::Vector2i get_next_position(MoveType move);

	sf::Vector2i get_direction();
	std::vector<MoveType> get_move_sequence();
	std::vector<MoveType> get_move_collision();

	void set_direction(sf::Vector2i new_direction);
};

#endif // GRIDSTEALTH_ENTITIES_ENTITY_H