/*
@File:              MainMenu.h
@(#)Purpose:        Header file containing MainMenu class and its member variable/functions
@(#)Author:         Brennon DeBoer
*/

#ifndef MAINMENU_H
#define MAINMENU_H
#include <SFML/Graphics.hpp>
#include <iostream>

const int MaxNumberOfItems = 3;

class MainMenu
{
public:
    MainMenu(float width, float height);
    ~MainMenu();

    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() {return selectedItemIndex;}

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MaxNumberOfItems];
};


#endif
