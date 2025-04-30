
#ifndef GRIDSTEALTH_ENTITIES_ENEMY_H
#define GRIDSTEALTH_ENTITIES_ENEMY_H

#include "Entity.h"

// NOTE: This is kinda scuffed maybe but whatever
enum EnemyType
{
	DemoEnemy1,
	DemoEnemy2,
	DemoEnemy3
};

class Enemy : public Entity
{
	EnemyType enemy_type;

	std::vector<sf::Vector2i> view_area;
	sf::Sprite view_sprite;
	sf::Texture view_texture;

public:
	int collisions = 0;

	Enemy();
	Enemy(EnemyType type, sf::Vector2i position, sf::Vector2i direction = sf::Vector2i(0, -1));

	bool init() override;
	void render(sf::RenderWindow& window) override;

	sf::Sprite& get_view_sprite();
	EnemyType get_enemy_type();
	std::vector<sf::Vector2i> get_view_area();
};

#endif // GRIDSTEALTH_ENTITIES_ENEMY_H