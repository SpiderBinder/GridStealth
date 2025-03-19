
#ifndef GRIDSTEALTH_GAMEOBJECT_H
#define GRIDSTEALTH_GAMEOBJECT_H

#include <SFML/Graphics.hpp>

enum CollisionType
{
    Solid,
    Transparent,
    Traversable,
    Empty
};

class GameObject
{
    sf::Sprite* sprite = nullptr;
    sf::Vector2f position = sf::Vector2f(0, 0);

public:
    GameObject(sf::Sprite* _sprite);

    sf::Sprite* get_sprite();
    sf::Vector2f get_position();
    void set_position(sf::Vector2f new_position);

};

#endif // GRIDSTEALTH_GAMEOBJECT_H