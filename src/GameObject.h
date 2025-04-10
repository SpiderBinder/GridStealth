
#ifndef GRIDSTEALTH_GAMEOBJECT_H
#define GRIDSTEALTH_GAMEOBJECT_H

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
    sf::Sprite* sprite = nullptr;
    sf::Vector2i position = sf::Vector2i(0, 0);

    bool is_loaded = false;

public:
    GameObject();
	~GameObject();

    virtual void init(sf::Texture* _texture);
    virtual void render(sf::RenderWindow& window);

    sf::Sprite* get_sprite();
    sf::Vector2i get_position();
	sf::Vector2f get_float_position();
    void set_position(sf::Vector2i new_position);

};

#endif // GRIDSTEALTH_GAMEOBJECT_H