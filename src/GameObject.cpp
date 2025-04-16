
#include "GameObject.h"

GameObject::GameObject()
{
    //sprite = new sf::Sprite();
}

GameObject::~GameObject()
{
	//delete sprite;
}


void GameObject::init(sf::Texture* _texture)
{
	sprite.setTexture(*_texture);
}

void GameObject::render(sf::RenderWindow& window)
{
	sprite.setPosition(get_float_position());
	window.draw(sprite);
}


sf::Sprite& GameObject::get_sprite()
{
    return sprite;
}

sf::Vector2i GameObject::get_position()
{
    return position;
}

sf::Vector2f GameObject::get_float_position()
{
	return sf::Vector2f(position.x, position.y);
}

void GameObject::set_position(sf::Vector2i new_position)
{
    position = new_position;
}