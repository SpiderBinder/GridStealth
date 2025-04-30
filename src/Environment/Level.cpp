
#include "Level.h"

Level::Level()
{
	// NOTE: Ideally this shouldn't be used so idk why I have this tbh
}

Level::Level(std::string directory)
{
	load_from_file(directory);
}

Level::~Level()
{
	
}


// Chonky-ass function to load level details (map, enemies, items etc) from a text file provided
bool Level::load_from_file(std::string directory)
{
	bool success = true;

	std::ifstream filereader;
	filereader.open(directory);
	// Error check if directory given is bad/other
	if (!filereader.good())
	{
		std::cout << "Level file failed to open: " << directory << std::endl;
		return false;
	}
	
	std::vector<std::string> contents;

	// Reads all lines of given text file
	std::string line;
	while (std::getline(filereader, line))
	{
		if (line != "")
		{
			contents.push_back(line);
		}
	}
	filereader.close();

	// Parse the contents of the file
	std::vector<std::string> mapdata;
	std::vector<std::string> objectdata;
	std::vector<std::string> entitydata;

	for (int i = 0; i < contents.size(); i++)
	{
		// Check for 'map' catagory tag
		if (contents[i] == "map:")
		{
			// Read all map data
			for (int j = i + 1; j < contents.size(); j++)
			{
				if (contents[j].back() == ':')
				{
					i = j - 1;
					break;
				}
				mapdata.push_back(contents[j]);
			}
		}
		// Check for 'objects' catagory tag
		else if (contents[i] == "objects:")
		{
			// Read all object data
			for (int j = i + 1; j < contents.size(); j++)
			{
				if (contents[j].back() == ':')
				{
					i = j - 1;
					break;
				}
				objectdata.push_back(contents[j]);
			}
		}
		// Check for 'entities' catagory tag
		else if (contents[i] == "entities:")
		{
			// Read all entity data
			for (int j = i + 1; j < contents.size(); j++)
			{
				if (contents[j].back() == ':')
				{
					i = j - 1;
					break;
				}
				entitydata.push_back(contents[j]);
			}
		}
		// Check for optional (?) 'end' tag
		else if (contents[i] == "end:")
		{
			break;
		}
	}

	// Set up wall_map and collision_map
	int width = 0;
	for (std::string row : mapdata)
	{
		if (row.size() > width)
		{
			width = row.size();
		}
	}
	width /= 2;
	for (int i = 0; i < width; i++)
	{
		wall_map.push_back(std::vector<TileType>());
		collision_map.push_back(std::vector<CollisionType>());
		
		for (int j = 0; j < mapdata.size(); j++)
		{
			wall_map[i].push_back(TileType::Empty);
			collision_map[i].push_back(CollisionType::Null);
		}
	}

	// Parse map data
	// Filters out commas from strings
	for (std::string& row : mapdata)
	{
		std::string newRow = "";
		for (char character : row)
		{
			if (character != ','  && character != ';')
			{
				newRow += character;
			}
		}
		row = newRow;
	}

	// Player start position storing
	sf::Vector2i player_start = sf::Vector2i(0, 0);

	// Converts mapdata numerical characters into TileType enums
	for (int i = 0; i < mapdata.size(); i++)
	{
		for (int j = 0; j < mapdata[i].size(); j++)
		{
			TileType tile;
			switch (mapdata[i][j])
			{
			case '0':
				tile = TileType::Wall;
				break;
			case '1':
				tile = TileType::Window;
				break;
			case '2':
				tile = TileType::Empty;
				break;
			case '3':
				tile = TileType::Start;
				player_start = sf::Vector2i(j, i);
				break;
			case '4':
				tile = TileType::End;
				break;
			default:
				tile = TileType::Empty;
				break;
			}

			wall_map[j][i] = tile;
		}
	}

	// Parse object data
	for (std::string object : objectdata)
	{
		std::vector<std::string> objectinfo;
		
		std::string info = "";
		for (int i = 0; i < object.size(); i++)
		{
			if (object[i] == ',' || object[i] == ';')
			{
				objectinfo.push_back(info);
				info = "";
			}
			else
			{
				info += object[i];
			}
		}

		bool isfurniture;
		CollisionType collision;
		sf::Vector2i position;
		for (std::string info : objectinfo)
		{
			// Seperate info into tag and value
			std::string identifier = info.substr(0, info.find('='));
			info = info.substr(info.find('=') + 1);

			if (identifier == "objtype")
			{
				if (info == "furniture")
					isfurniture = true;
				else
					isfurniture = false;
			}
			else if (identifier == "collision")
			{
				switch (info[0])
				{
				case '0':
					collision = CollisionType::Solid;
					break;
				case '1':
					collision = CollisionType::Transparent;
					break;
				case '2':
					collision = CollisionType::Traversable;
					break;
				default:
					collision = CollisionType::Null;
					break;
				}
			}
			else if (identifier == "posx")
			{
				position.x = std::stoi(info);
			}
			else if (identifier == "posy")
			{
				position.y = std::stoi(info);
			}
		}

		// TODO: Uncomment when Furniture and Item classes are implemented
		if (isfurniture)
		{
			//objects.push_back(Furniture(collision, position));
		}
		else
		{
			//objects.push_back(Item(collision, position));
		}
	}

	// Parse entity data
	for (std::string entity : entitydata)
	{
		std::vector<std::string> entityinfo;

		std::string info = "";
		for (int i = 0; i < entity.size(); i++)
		{
			if (entity[i] == ',' || entity[i] == ';')
			{
				entityinfo.push_back(info);
				info = "";
			}
			else
			{
				info += entity[i];
			}
		}

		// NOTE: May be good to make a 'NULL' enemytype for error checking
		EnemyType enemy_type = EnemyType::DemoEnemy1;
		CollisionType collision;
		sf::Vector2i position;
		sf::Vector2i direction;
		for (std::string info : entityinfo)
		{
			// Seperate info into tag and value
			std::string identifier = info.substr(0, info.find('='));
			info = info.substr(info.find('=') + 1);

			if (identifier == "type")
			{
				if (info == "DemoEnemy1" || info == "0")
				{
					enemy_type = EnemyType::DemoEnemy1;
				}
				else if (info == "DemoEnemy2" || info == "1")
				{
					enemy_type = EnemyType::DemoEnemy2;
				}
				else if (info == "DemoEnemy3" || info == "2")
				{
					enemy_type = EnemyType::DemoEnemy3;
				}
				else
				{
					std::cout << "Invalid enemy type: " << info << std::endl;
					success = false;
				}
			}
			// NOTE: Covered by hardcoded enemy types and currently unused
			// (Potential use for custom enemy types?)
			else if (identifier == "collision")
			{
				switch (info[0])
				{
				case '0':
					collision = CollisionType::Solid;
					break;
				case '1':
					collision = CollisionType::Transparent;
					break;
				case '2':
					collision = CollisionType::Traversable;
					break;
				default:
					collision = CollisionType::Null;
					break;
				}
			}
			else if (identifier == "direction")
			{
				switch (info[0])
				{
				case '0':
					direction = sf::Vector2i(0, -1);
					break;
				case '1':
					direction = sf::Vector2i(1, 0);
					break;
				case '2':
					direction = sf::Vector2i(0, 1);
					break;
				case '3':
					direction = sf::Vector2i(-1, 0);
					break;
				default:
					// NOTE: No current error checking in place to handle this
					direction = sf::Vector2i(0, 0);
					break;
				}
			}
			else if (identifier == "posx")
			{
				position.x = std::stoi(info);
			}
			else if (identifier == "posy")
			{
				position.y = std::stoi(info);
			}
		}

		level_enemies.push_back(Enemy(enemy_type, position, direction));
	}

	// Load Player
	player = Player(player_start);

	return success;
}

// Remakes collision map from wall_map as well as the objects and entities in the level
void Level::make_collisionmap()
{
	if (wall_map.size() == 0 || wall_map[0].size() == 0)
	{
		return;
	}

	// TODO: Only rebuild collision map if wall_map or objects have changed

	// Add collision for level walls
	for (int i = 0; i < wall_map.size(); i++)
	{
		for (int j = 0; j < wall_map[0].size(); j++)
		{
			switch (wall_map[i][j])
			{
			case TileType::Wall:
				collision_map[i][j] = CollisionType::Solid;
				break;
			case TileType::Window:
				collision_map[i][j] = CollisionType::Transparent;
				break;
			case TileType::Empty:
				collision_map[i][j] = CollisionType::Traversable;
				break;
			case TileType::Start:
			case TileType::End:
				// TODO: Change to solid when proper levels are implemented?
				collision_map[i][j] = CollisionType::Traversable;
				break;
			default:
				collision_map[i][j] = CollisionType::Null;
				break;
			}
		}
	}

	// TODO: Add objects to collision map

	// Add collision for entities
	for (Entity entity : level_enemies)
	{
		sf::Vector2i position = entity.get_position();
		collision_map[position.x][position.y] = entity.get_collision();
	}
	collision_map[player.get_position().x][player.get_position().y] = CollisionType::Solid;

	return;
}

// Checks if a given position is colliding with a wall or object
bool Level::check_collision(sf::Vector2i position)
{
	if ((position.x < 0 || position.x >= collision_map.size()) ||
		(position.y < 0 || position.y >= collision_map[0].size()))
	{
		return true;
	}
	CollisionType tile = collision_map[position.x][position.y];
	if (tile == CollisionType::Solid || tile == CollisionType::Transparent)
	{
		return true;
	}

	return false;
}


// Initialises textures and sprites for the level
// NOTE: Only to be run after load_from_file or entity and object assets will not be loaded
bool Level::init(std::string tileset_name)
{
	bool success = true;

	// Load the tileset texture
	if (!tileset.loadFromFile("../content/Assets/Tilesets/" + tileset_name + ".png"))
	{
		std::cout << "Failed to load tileset: " << tileset_name << std::endl;
		success = false;
	}
	else
	// Assigns texture to environment sprites
	sprite_wall.setTexture(tileset);
	sprite_window.setTexture(tileset);
	sprite_empty.setTexture(tileset);
	sprite_objective.setTexture(tileset);

	sprite_wall.setTextureRect(sf::IntRect(0, 0, 16, 16));
	sprite_window.setTextureRect(sf::IntRect(16, 0, 16, 16));
	sprite_empty.setTextureRect(sf::IntRect(0, 16, 16, 16));
	sprite_objective.setTextureRect(sf::IntRect(16, 16, 16, 16));

	// NOTE: Remove once camera implemented
	sprite_wall.setScale(4.0f, 4.0f);
	sprite_window.setScale(4.0f, 4.0f);
	sprite_empty.setScale(4.0f, 4.0f);
	sprite_objective.setScale(4.0f, 4.0f);

	// NOTE: Uncomment when Furniture and Item classes are implemented
	// Load furniture and item assets
	/*for (GameObject object : level_objects)
	{
		if (!object.init())
		{
			std::cout << "Failed to load object: " << object.get_name() << std::endl;
			success = false;
		}
		object.get_sprite().setScale(2.0f, 2.0f);
	}*/

	// Load enemy assets
	for (Enemy& enemy : level_enemies)
	{
		if (!enemy.init())
		{
			std::string enemy_name;
			switch (enemy.get_enemy_type())
			{
			case EnemyType::DemoEnemy1:
				enemy_name = "DemoEnemy1";
				break;
			case EnemyType::DemoEnemy2:
				enemy_name = "DemoEnemy2";
				break;
			case EnemyType::DemoEnemy3:
				enemy_name = "DemoEnemy3";
				break;
			default:
				enemy_name = "NameError";
				break;
			}

			std::cout << "Failed to load entity: " << enemy_name << std::endl;
			success = false;
		}
		// NOTE: Remove once camera implemented
		enemy.get_sprite().setScale(4.0f, 4.0f);
		enemy.get_view_sprite().setScale(4.0f, 4.0f);
	}

	// Load player assets
	if (!player.init())
	{
		std::cout << "Failed to load player assets" << std::endl;
		success = false;
	}
	player.get_sprite().setScale(4.0f, 4.0f);

	return success;
}

// Render the level
void Level::render(sf::RenderWindow& window)
{
	// Draw tiles
	for (int y = 0; y < wall_map[0].size(); y++)
	{
		for (int x = 0; x < wall_map.size(); x++)
		{
			switch (wall_map[x][y])
			{
			case TileType::Wall:
				sprite_wall.setPosition(x * 64, y * 64);
				window.draw(sprite_wall);
				break;
			case TileType::Window:
				sprite_window.setPosition(x * 64, y * 64);
				window.draw(sprite_window);
				break;
			case TileType::Empty:
				sprite_empty.setPosition(x * 64, y * 64);
				window.draw(sprite_empty);
				break;
			case TileType::Start:
				if (!objective_reached)
				{
					sprite_empty.setPosition(x * 64, y * 64);
					window.draw(sprite_empty);
				}
				else
				{
					sprite_objective.setPosition(x * 64, y * 64);
					window.draw(sprite_objective);
				}
				break;
			case TileType::End:
				if (objective_reached)
				{
					sprite_empty.setPosition(x * 64, y * 64);
					window.draw(sprite_empty);
				}
				else
				{
					sprite_objective.setPosition(x * 64, y * 64);
					window.draw(sprite_objective);
				}
				break;
			default:
				break;
			}
		}
	}

	// NOTE: Uncomment when Furniture and Item classes are implemented
	// Draw Furniture and Items
	/*for (GameObject &object : level_objects)
	{
		object.render(window);
	}*/

	// Draw entities
	for (Enemy& enemy : level_enemies)
	{
		enemy.render(window);
	}
	player.render(window);
}

// Calculates movement of entities and specific level events
bool Level::process_turn(int iteration)
{
	bool finished = true;

	// Force ends the turn after 10 iterations of movement
	// NOTE: May make a less 'hacked' solution to infinite collision loops later
	if (iteration > 10)
	{
		return true;
	}

	// Remake collision_map with any new wall_map or object updates
	make_collisionmap();

	for (Enemy& enemy : level_enemies)
	{
		// Reset enemy collision count at the start of turn processing
		if (iteration == 0)
		{
			enemy.collisions = 0;
		}
		// Check if enemy movement has finished processing
		if (iteration < (enemy.get_move_sequence().size() + (enemy.collisions * enemy.get_move_collision().size())))
		{
			finished = false;

			// TODO: Check if collision movement is still being calculated
			// NOTE: This can kinda wait for a min since all collision movement is currently a single movement instruction

			int move_iteration = iteration - enemy.collisions * enemy.get_move_collision().size();

			// Get next position from enemy
			sf::Vector2i new_position = enemy.get_next_position(enemy.get_move_sequence()[move_iteration]);

			// Checks for collision
			if (check_collision(new_position))
			{
				enemy.collisions++;
				new_position = enemy.get_next_position(enemy.get_move_collision()[0]);
				if (check_collision(new_position))
				{
					new_position = enemy.get_position();
				}
			}

			enemy.set_position(new_position);

			// Update collision_map with new enemy position
			make_collisionmap();
		}
	}

	// Process non-entity movement
	// NOTE: Currently no non-entity movement

	return finished;
}


// Receives player move and 
void Level::player_input(Entity::MoveType input)
{
	sf::Vector2i new_position = player.get_next_position(input);

	make_collisionmap();
	if (check_collision(new_position))
	{
		new_position = player.get_position();
	}

	TileType tile = wall_map[new_position.x][new_position.y];
	if (!objective_reached && tile == TileType::End)
	{
		objective_reached = true;
	}
	else if (objective_reached && tile == TileType::Start)
	{
		exit_reached = true;
		std::cout << "Level finished!" << std::endl;
	}

	player.set_position(new_position);
}