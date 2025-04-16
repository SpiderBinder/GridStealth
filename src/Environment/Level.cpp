
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
				break;
			case '4':
				tile = TileType::Exit;
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

		// TODO: Add enemy type loading
		CollisionType collision;
		sf::Vector2i position;
		for (std::string info : entityinfo)
		{
			// Seperate info into tag and value
			std::string identifier = info.substr(0, info.find('='));
			info = info.substr(info.find('=') + 1);

			if (identifier == "type")
			{
				// TODO: Add enemy type loading
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

		// TODO: Uncomment when Enemy class is implemented
		//entities.push_back(Enemy());
	}

	return true;
}

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

	sprite_wall.setTextureRect(sf::IntRect(0, 0, 16, 16));
	sprite_window.setTextureRect(sf::IntRect(16, 0, 16, 16));
	sprite_empty.setTextureRect(sf::IntRect(0, 16, 16, 16));

	sprite_wall.setScale(4.0f, 4.0f);
	sprite_window.setScale(4.0f, 4.0f);
	sprite_empty.setScale(4.0f, 4.0f);

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

	// NOTE: Uncomment when Enemy class is implemented
	// Load enemy assets
	/*for (Entity entity : level_entities)
	{
		if (!entity.init())
		{
			std::cout << "Failed to load entity: " << entity.get_name() << std::endl;
			success = false;
		}
		entity.get_sprite().setScale(2.0f, 2.0f);
	}*/

	// NOTE: Uncomment when Player class is implemented
	// Load player assets
	/*if (!player.init())
	{
		std::cout << "Failed to load player: " << player.get_name() << std::endl;
		success = false;
	}
	player.get_sprite().setScale(2.0f, 2.0f);*/

	return success;
}

// Render the level
void Level::render(sf::RenderWindow& window)
{
	// Draw tiles
	for (int y = 0; y < wall_map.size(); y++)
	{
		for (int x = 0; x < wall_map[y].size(); x++)
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
			case TileType::Start:
			case TileType::Exit:
				sprite_empty.setPosition(x * 64, y * 64);
				window.draw(sprite_empty);
				break;
			default:
				break;
			}
		}
	}

	// NOTE: Remove when gameobject classes are implemented
	return;

	// Draw Furniture and Items
	for (GameObject &object : level_objects)
	{
		object.render(window);
	}

	// Draw entities
	for (Entity& entity : level_entities)
	{
		entity.render(window);
	}
	player.render(window);
}