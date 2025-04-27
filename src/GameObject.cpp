
#include "GameObject.h"

GameObject::GameObject()
{
    //sprite = new sf::Sprite();
}

GameObject::~GameObject()
{
	//delete sprite;
}


bool GameObject::init()
{
	return true;
}

void GameObject::render(sf::RenderWindow& window)
{
	sprite.setPosition(get_real_position());
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

sf::Vector2f GameObject::get_real_position()
{
	return sf::Vector2f(
		position.x * sprite.getGlobalBounds().width, 
		position.y * sprite.getGlobalBounds().height);
}

CollisionType GameObject::get_collision()
{
	return collision;
}

void GameObject::set_position(sf::Vector2i new_position)
{
    position = new_position;
}