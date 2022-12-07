/*
@File:              Bullet.h
@(#)Purpose:        Header file containing bullet class and its member functions/variables
@(#)Author:         Brennon DeBoer
*/

#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
public:
    Bullet(sf::Texture *texture, sf::Vector2f pos);
    ~Bullet(){};
    sf::Sprite shape;
};


#endif