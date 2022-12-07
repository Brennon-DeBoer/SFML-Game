/*
@File:              Bullet.cpp
@(#)Purpose:        Contains Bullet class constructor definition
@(#)Author:         Brennon DeBoer
*/

#include "Bullet.h"
//Setting bullet texture, size, and position
//Paramater sf::Vector2f pos represents the position of the player
Bullet::Bullet(sf::Texture *texture, sf::Vector2f pos)
{
    this->shape.setTexture(*texture);

    this->shape.setScale(0.05f,0.05f);
    //Positioning bullet to shoot from the end of the spaceship
    this->shape.setPosition(pos.x + 85, pos.y + 47);
}