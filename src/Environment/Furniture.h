
#ifndef GRIDSTEALTH_ENVIRONMENT_FURNITURE_H
#define GRIDSTEALTH_ENVIRONMENT_FURNITURE_H

#include "../GameObject.h"
#include "Item.h"

class Furniture : public GameObject
{
public:
	enum FurnitureType
	{
		Error,
		Table,
		Door
	};
private:
	FurnitureType type = FurnitureType::Error;

	// State
	bool lockable = false;
	int locktype = 0; // 0 - None, 1 - Basic Key
	bool toggleable = false;
	bool container = false;

	bool locked = false;
	bool toggle = false;

public:
	Item* stored_item = nullptr;

	Furniture();
	Furniture(FurnitureType type, sf::Vector2i position);

	bool init();
	void render(sf::RenderWindow& window) override;
	bool interact();
	bool interact(Item item);

	FurnitureType get_type();

	bool is_lockable();
	int get_locktype();
	bool is_toggleable();
	bool is_container();

	bool is_locked();
	bool is_toggled();
	void set_locked(bool locked);
	void set_toggled(bool toggle);

};

#endif // GRIDSTEALTH_ENVIRONMENT_FURNITURE_H