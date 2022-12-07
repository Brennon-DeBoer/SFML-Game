
/*
@File:              Enemy.h
@(#)Purpose:        Header file containing class Enemy inherited from Player
@(#)Author:         Brennon DeBoer
*/
#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

class Enemy: public Player
{
public:
    Enemy(sf::Texture *texture, sf::Vector2u windowSize);
    ~Enemy() {};
    void drawEnemy(sf::RenderWindow &window, std::vector<Enemy> &enemy);
    void moveEnemy(sf::RenderWindow &window, std::vector<Enemy> &enemy, Player &player);
    void createNewEnemy(std::vector<Enemy> &enemies, sf::Texture *texture, sf::RenderWindow &window);
private:
    //Sets the time before the next enemy will spawn
    int enemySpawnTimer;
};

#endif