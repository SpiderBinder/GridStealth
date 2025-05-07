
#ifndef GRIDSTEALTH_ENTITIES_PLAYER_H
#define GRIDSTEALTH_ENTITIES_PLAYER_H

#include "Entity.h"

class Player : public Entity
{

public:
	Player();
	Player(sf::Vector2i position, sf::Vector2i direction = sf::Vector2i(0, -1));

	bool init() override;

	void update_sprite_direction();
};

#endif // GRIDSTEALTH_ENTITIES_PLAYER_H