/*
@File:              Player.cpp
@(#)Purpose:        Contains function definitions of all member functions in Player class
@(#)Author:         Brennon DeBoer
*/
#include "Player.h"
//Constructor with texture pointer parameter to set the texture of the player
Player::Player(sf::Texture *texture)
{
    //Setting max hp to 10
    this->maxHp = 10;
    //Setting current hp to max when player is constructed
    this->hp = this->maxHp;

    this->texture = texture;
    this->shape.setTexture(*texture);
    this->shape.setScale(0.07f, 0.07f);
    //Setting shoot timer to 30. Adjust to change the amount of time before the next bullet can be fired
    shootTimer = 30;
}
//Draws bullets to the screen, passes the window and the current player by reference
void Player::drawBullets(sf::RenderWindow &window, Player &player)
{
    for (int i = 0; i < player.bullets.size(); i++)
    {
        window.draw(player.bullets[i].shape);
    }
}
//Moves player around the screen
void Player::movePlayer(Player &player)
{
    //Move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        player.shape.move(0.f, -4.f);
    }
    //Move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player.shape.move(-4.f, 0.f);
    }
    //Move down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        player.shape.move(0.f, 4.f);
    }
    //Move right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.shape.move(4.f, 0.f);
    }
}
//Checks if player has gone out of the rendered window
void Player::checkPlayerBounds(sf::RenderWindow &window, Player &player)
{
    //Left of screen
    if (player.shape.getPosition().x <= 0)
    {
        player.shape.setPosition(0.f, player.shape.getPosition().y);
    }
    //Right of screen
    else if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width)
    {
        player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
    }
    //Top of screen
    else if (player.shape.getPosition().y <= 0)
    {
        player.shape.setPosition(player.shape.getPosition().x, 0.f);
    }
    //Bottom of screen
    else if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height)
    { 
        player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);
    }
}
//Creates a new bullet anytime a the shoot key is pressed and the shoot timer is greater than 30
void Player::shootBullets(Player &player, sf::Texture &bulletTex, sf::RenderWindow &window)
{
    if (shootTimer < 30)
    {
        shootTimer++;
    }
    if((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && shootTimer >= 30)
    {
        player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
        //Sets shoot timer back to 0 since a bullet has just been fired
        shootTimer = 0;
    }
    //Moving each of the bullets to the right of the screen
    for (int i = 0; i < player.bullets.size(); i++)
    {
        //Move bullet right
        player.bullets[i].shape.move(10.f, 0.f);
        //Erase the bullet and clear memory if the bullet has left the screen
        if(player.bullets[i].shape.getPosition().x > window.getSize().x)
        {
            player.bullets.erase(player.bullets.begin() + i);
        }
    }
}
