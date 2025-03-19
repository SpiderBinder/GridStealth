
#include "GameObject.h"

GameObject::GameObject(sf::Sprite* _sprite)
    : sprite(_sprite)
{

}


sf::Sprite* GameObject::get_sprite()
{
    return sprite;
}

sf::Vector2f GameObject::get_position()
{
    return position;
}

void GameObject::set_position(sf::Vector2f new_position)
{
    position = new_position;
}