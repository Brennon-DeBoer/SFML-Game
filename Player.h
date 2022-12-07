/*
@File:              Player.h
@(#)Purpose:        Header file containing Player class and its member functions/variables
@(#)Author:         Brennon DeBoer
*/
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Bullet.h"

class Player
{
public:
    Player(sf::Texture *texture);
    //Needed default constructor so the inherited class Enemys' constructor could work
    Player() {};
    ~Player() {};
    sf::Sprite shape;
    //Vector of bullet objects to create and destroy multiple bullets
    std::vector<Bullet> bullets;
    void drawBullets(sf::RenderWindow &window, Player &player);
    void shootBullets(Player &player, sf::Texture &bulletTex, sf::RenderWindow &window);
    void movePlayer(Player &player);
    void checkPlayerBounds(sf::RenderWindow &window, Player &player);
    sf::Texture *texture;
    //Player's current hp
    int hp;
    //Player's max hp
    int maxHp;
    //Shoot timer measures how long the player must wait until the next bullet can be fired
    int shootTimer;
};


#endif