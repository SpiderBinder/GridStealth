
#ifndef GRIDSTEALTH_GAMEOBJECT_H
#define GRIDSTEALTH_GAMEOBJECT_H

#include <iostream>

#include <SFML/Graphics.hpp>

enum CollisionType
{
    Solid,
    Transparent,
    Traversable,
    Null
};

class GameObject
{
protected:
	sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2i position = sf::Vector2i(0, 0);

	CollisionType collision = CollisionType::Null;
    bool is_loaded = false;

public:
    GameObject();
	~GameObject();

    virtual bool init();
    virtual void render(sf::RenderWindow& window);

    sf::Sprite& get_sprite();
    sf::Vector2i get_position();
	sf::Vector2f get_real_position();
	CollisionType get_collision();
    void set_position(sf::Vector2i new_position);

};

#endif // GRIDSTEALTH_GAMEOBJECT_H