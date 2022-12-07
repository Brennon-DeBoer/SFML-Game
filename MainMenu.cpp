/*
@File:              MainMenu.cpp
@(#)Purpose:        Contains function definitions for menu buttons
@(#)Author:         Brennon DeBoer
*/

#include "MainMenu.h"

//Setting menu button fonts, color, string, and position
MainMenu::MainMenu(float width, float height)
{
    if(!font.loadFromFile("starfieldfont.ttf"))
    {
        std::cout << "Error opening font file!\n";
        exit(1);
    }

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Blue);
    menu[0].setString("Play Starfight");
    menu[0].setPosition(sf::Vector2f((width / 2) - 105, height / (MaxNumberOfItems + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("About");
    menu[1].setPosition(sf::Vector2f((width / 2) - 60, height / (MaxNumberOfItems + 1) * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f((width / 2) - 40, height / (MaxNumberOfItems + 1) * 3));

    selectedItemIndex = 0;
}
//Default destructor
MainMenu::~MainMenu()
{

}
//Draws menu buttons to the window
void MainMenu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < MaxNumberOfItems; i++)
    {
        window.draw(menu[i]);
    }
}
//Highlights selected button blue
void MainMenu::MoveUp()
{
    if(selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Blue);
    }
}
//Highlights selected button blue
void MainMenu::MoveDown()
{
    if(selectedItemIndex + 1 < MaxNumberOfItems)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Blue);
    }
}