
#ifndef GRIDSTEALTH_ENVIRONMENT_LEVEL_H
#define GRIDSTEALTH_ENVIRONMENT_LEVEL_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../Entities/Enemy.h"
#include "../Entities/Player.h"
#include "Furniture.h"
#include "Item.h"

enum TileType
{
	Wall,
	Window,
	Empty,
	Start,
	Exit
};

class Level
{
	sf::Texture tileset;

	std::vector<std::vector<TileType>> wall_map;
	std::vector<std::vector<CollisionType>> collision_map;

	// Furniture and items
	std::vector<GameObject> objects;
	std::vector<Entity> entities;
	Player player;

	void load_from_file(std::string directory);

public:
	Level();
	Level(std::string directory);
	~Level();

	void render(sf::RenderWindow& window);

	CollisionType get_collision(sf::Vector2i position);
	CollisionType get_collision(int x, int y);
	std::vector<Entity>& get_entities();
};

#endif // GRIDSTEALTH_ENVIRONMENT_LEVEL_H