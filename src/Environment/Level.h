
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
	End
};

class Level
{
	// Rendering
	sf::Texture tileset;
	sf::Sprite sprite_wall;
	sf::Sprite sprite_window;
	sf::Sprite sprite_empty;
	sf::Sprite sprite_objective;

	// Data
	std::vector<std::vector<TileType>> wall_map;
	std::vector<std::vector<CollisionType>> collision_map;

	std::vector<GameObject> level_objects;
	std::vector<Enemy> level_enemies;
	Player player;

	// Levelstate
	bool objective_reached = false;
	bool exit_reached = false;

	bool aware = false;
	int alert_counter = 0;
	bool caught = false;

	// Internal Functions
	bool load_from_file(std::string directory);

	void make_collisionmap();
	bool check_collision(sf::Vector2i position);
	bool is_view_area(sf::Vector2i position);

public:
	Level();
	Level(std::string directory);
	~Level();

	bool init(std::string tileset_name);
	void render(sf::RenderWindow& window);
	bool process_turn(int iteration);

	void player_input(Entity::MoveType input);

	//CollisionType get_collision(sf::Vector2i position);
	//CollisionType get_collision(int x, int y);
	//std::vector<Entity>& get_entities();

	bool is_aware();
	bool is_alert();
	bool is_caught();
};

#endif // GRIDSTEALTH_ENVIRONMENT_LEVEL_H