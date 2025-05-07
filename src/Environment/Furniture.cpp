
#include "Furniture.h"

Furniture::Furniture()
	: type(FurnitureType::Error)
{

}

Furniture::Furniture(FurnitureType type, sf::Vector2i position)
	: type(type)
{
	this->position = position;

	switch (type)
	{
	case Table:
		collision = CollisionType::Solid;
		lockable = false;
		toggleable = false;
		container = true;
		break;
	case Door:
		collision = CollisionType::Solid;
		lockable = true;
		toggleable = true;
		container = false;
		locktype = 1; // Basic Key

		locked = false;
		toggle = true;
		break;
	default:
		break;
	}
}


bool Furniture::init()
{
	bool success = true;

	switch (type)
	{
	case Table:
		if (!texture.loadFromFile("../content/Assets/LevelObjects/DemoTable.png"))
		{
			std::cout << "Error: Table texture failed to load" << std::endl;
			success = false;
		}
		sprite.setTexture(texture);
		break;
	case Door:
		if (!texture.loadFromFile("../content/Assets/LevelObjects/DemoDoor.png"))
		{
			std::cout << "Error: Door texture failed to load" << std::endl;
			success = false;
		}
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
		break;
	}

	sprite.setScale(4, 4);

	return success;
}

void Furniture::render(sf::RenderWindow& window)
{
	sprite.setTextureRect(sf::IntRect(16 * (toggle ? 1 : 0), 16 * (locked ? 1 : 0), 16, 16));
	sprite.setPosition(get_real_position());

	window.draw(sprite);
}

bool Furniture::interact()
{
	if (type == Door)
	{
		if (!locked)
		{
			toggle = !toggle;
			collision = toggle ? CollisionType::Solid : CollisionType::Traversable;
			sprite.setTextureRect(sf::IntRect(16 * (toggle ? 1 : 0), 16 * (locked ? 1 : 0), 16, 16));
		}
	}

	return false;
}

bool Furniture::interact(Item item)
{
	if (lockable && locked)
	{
		// TODO: Check for interaction with compatible key
		// Return true if successful to delete key item
	}

	return false;
}


Furniture::FurnitureType Furniture::get_type()
{
	return type;
}


bool Furniture::is_lockable()
{
	return lockable;
}

int Furniture::get_locktype()
{
	return locktype;
}

bool Furniture::is_toggleable()
{
	return toggleable;
}

bool Furniture::is_container()
{
	return container;
}


bool Furniture::is_locked()
{
	return locked;
}

bool Furniture::is_toggled()
{
	return toggle;
}

void Furniture::set_locked(bool locked)
{
	this->locked = locked;
}

void Furniture::set_toggled(bool toggle)
{
	this->toggle = toggle;
}