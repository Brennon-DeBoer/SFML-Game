/*
@File:              Enemy.cpp
@(#)Purpose:        Contains function definitions for the enemy class
@(#)Author:         Brennon DeBoer
*/
#include "Enemy.h"
//Enemy constructor that sets the spawn timer at 0, gives enemy objects a random hp between 1 and 3, and sets the texture, size, and position of the enemy object
Enemy::Enemy(sf::Texture *texture, sf::Vector2u windowSize)
{
    this->enemySpawnTimer = 0;
    //Choosing a max hp between 1-3
    this->maxHp = rand()%3 + 1;
    this->hp = this->maxHp;

    this->shape.setTexture(*texture);

    this->shape.setScale(0.1f, 0.1f);
    //Setting random y positions for the ships
    this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, rand() % (int)(windowSize.y - (this->shape.getGlobalBounds().height + 20)));
}
//Draws enemy to the window as well as the hp meter above the enemy objects
void Enemy::drawEnemy(sf::RenderWindow &window, std::vector<Enemy> &enemy)
{
    //Creating the text object for the hp meter
    sf::Text enemyHpText;
    sf::Font enemyHpFont;
    if(!enemyHpFont.loadFromFile("starfieldfont.ttf"))
    {
        std::cout << "Error opening font file!\n";
        exit(1);
    }
    enemyHpText.setFont(enemyHpFont);
    enemyHpText.setCharacterSize(20);
    enemyHpText.setFillColor(sf::Color::Red);
    //Setting the string and position of each of the hp meters for each enemy object   
    for (int i = 0; i < enemy.size(); i++)
    {
        enemyHpText.setString(std::to_string(enemy[i].hp) + "/" + std::to_string(enemy[i].maxHp));
        enemyHpText.setPosition(enemy[i].shape.getPosition().x, enemy[i].shape.getPosition().y - (enemyHpText.getGlobalBounds().height + 10));
        //Drawing enemy
        window.draw(enemy[i].shape);
        //Drawing enemy hp meter
        window.draw(enemyHpText);
    }
}
//Moves the enemy to the left of the screen
void Enemy::moveEnemy(sf::RenderWindow &window, std::vector<Enemy> &enemy, Player &player, float enemySpeed)
{
    for (int i = 0; i < enemy.size(); i++)
    {
        //Each enemy moving left
        enemy[i].shape.move(enemySpeed, 0.f);
        //Erase enemy if it goes of the left of the screen
        if (enemy[i].shape.getPosition().x <= 0 - enemy[i].shape.getGlobalBounds().width)
        {
            enemy.erase(enemy.begin() + i);
        }
        //Erase enemy if it hits the player
        if (enemy[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
        {
            enemy.erase(enemy.begin() + i);
            //Player take damage
            player.hp--;
        }
        
    }
}
//Creates a new enemy when the spawn timer reaches 30
void Enemy::createNewEnemy(std::vector<Enemy> &enemies, sf::Texture *texture, sf::RenderWindow &window)
{
    //Checking spawn timer and adding to it if it is not 30
    if (enemySpawnTimer < 20)
    {
        enemySpawnTimer++;
    }
    //When timer hits 30, create new enemy and reset timer
    if (enemySpawnTimer >= 20)
    {
        enemies.push_back(Enemy(texture, window.getSize()));
        this->enemySpawnTimer = 0;
    }
}
