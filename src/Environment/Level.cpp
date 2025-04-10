
#include "Level.h"

Level::Level()
{

}

Level::Level(std::string directory)
{
	load_from_file(directory);
}

Level::~Level()
{
	
}


// Chonky-ass function to load level details (map, enemies, items etc) from a text file provided
void Level::load_from_file(std::string directory)
{
	std::ifstream filereader;
	filereader.open(directory);
	// Error check if directory given is bad/other
	if (!filereader.good())
	{
		std::cout << "Level file failed to open: " << directory << std::endl;
		return;
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

	// NOTE: Remove
	for (int y = 0; y < wall_map.size(); y++)
	{
		for (int x = 0; x < wall_map[y].size(); x++)
		{
			std::cout << wall_map[x][y] << " ";
		}
		std::cout << std::endl;
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
}


// Render the level
void Level::render(sf::RenderWindow& window)
{
	// Render map tiles
	//for (int i = 0; i < )
}