/*
@File:              main.cpp
@(#)Purpose:        Main function in which the menu and game run
@(#)Author:         Brennon DeBoer
*/
#include "MainMenu.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

int main()
{
    //Initial boolean variable that will describe whether the game is over
    bool GameOver;
    //Needed for random variables such as random enemy spawning
    srand(time(NULL));

    //Render window & window size
    sf::RenderWindow window(sf::VideoMode(1024, 960), "Starfight");
    
    //Creating main menu buttons
    MainMenu menu(window.getSize().x, window.getSize().y);

    //Setting frame limit for the window
    window.setFramerateLimit(300);

    //Creating background image for menu
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    sf::Texture MenuTexture;
    MenuTexture.loadFromFile("PixelStarfield.png");
    background.setTexture(&MenuTexture);

    //Creating textures for game objects
    sf::Texture playerTex;
    playerTex.loadFromFile("PlayerFighter.png");
    
    sf::Texture enemyTex;
    enemyTex.loadFromFile("EnemyFighter.png");
    
    sf::Texture bulletTex;
    bulletTex.loadFromFile("Bullet.png");

    //Creating game objects
    Player player(&playerTex);
    int shootTimer;
    Enemy enemy(&enemyTex, window.getSize());
    std::vector<Enemy> enemies;

    enemies.push_back(enemy);

    //HP UI
    sf::Text hpText;
    sf::Font hpFont;
    if(!hpFont.loadFromFile("starfieldfont.ttf"))
    {
        std::cout << "Error opening font file!\n";
        exit(1);
    }
    hpText.setFont(hpFont);
    hpText.setCharacterSize(20);
    hpText.setFillColor(sf::Color::White);

    //UI Score
    int gameScore = 0;
    sf::Text score;
    score.setFont(hpFont);
    score.setCharacterSize(30);
    score.setFillColor(sf::Color::Red);
    score.setPosition((window.getSize().x / 2) - 50, 0.f);

    //UI GameOver
    sf::Text gameOver;
    gameOver.setFont(hpFont);
    gameOver.setCharacterSize(50);
    gameOver.setFillColor(sf::Color::Red);
    gameOver.setPosition((window.getSize().x / 2) - 100, (window.getSize().y / 2) - 100);
    gameOver.setString("Game Over");
    
    float enemySpeed = -4.f;

    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            //Close window if x is selected in the top right corner of window
            if(event.type == sf::Event::Closed)
                window.close();
            //Check if a key has been pressed
            else if(event.type == sf::Event::KeyPressed)
            {
                //If escape is pressed at the main menu, game will close
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    window.close();
                }
                //If up or w is pressed, move the selected menu item up
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    menu.MoveUp();
                }
                //If down or s is pressed, move the selected menu item down
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    menu.MoveDown();
                }
                //If enter is pressed, check which menu item has been selected
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
                    //Check if play has been selected
                    if (menu.GetPressedItem() == 0)
                    {
                        //Start game over value at false
                        GameOver = false;
                        //While the game is not over, will run game
                        while (!GameOver)
                        {
                            //Close window if x is selected in the top right corner of window
                            if(event.type == sf::Event::Closed)
                            {
                                GameOver = true;
                                window.close();
                            }
                            //Close window if escape is pressed
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                            {
                                GameOver = true;
                            }
                            //Clear the window of objects
                            window.clear();
                            //Setting the string of the hp meter and the position of the player HP UI
                            hpText.setPosition(player.shape.getPosition().x, player.shape.getPosition().y - (hpText.getGlobalBounds().height + 10));
                            hpText.setString(std::to_string(player.hp) + "/" + std::to_string(player.maxHp));
                            //Update and move the player
                            player.movePlayer(player);
                            //Check if player is within the window
                            player.checkPlayerBounds(window, player);
                            //Update and shoot bullets
                            player.shootBullets(player, bulletTex, window);
                            //Enemy collision with bullets
                            for (int i = 0; i < player.bullets.size(); i++)
                            {
                                for (int k = 0; k < enemies.size(); k++)
                                {
                                    if (player.bullets[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds()))
                                    {
                                        if (enemies[k].hp <= 1)
                                        {
                                            //Update the game score
                                            gameScore += enemies[k].maxHp;
                                            if (gameScore % 10 == 0)
                                            {
                                                enemySpeed -= .5f;
                                            }
                                            //Enemy is dead
                                            enemies.erase(enemies.begin() + k);
                                        }
                                        else
                                            //Enemy hit by bullet
                                            enemies[k].hp--;
                                            //Erase bullet
                                            player.bullets.erase(player.bullets.begin() + i);
                                    }
                                }
                            }
                            //Updating and setting the string of the score
                            score.setString("Score: " + std::to_string(gameScore));
                            //Drawing the background image
                            window.draw(background);
                            //Drawing the player to window
                            window.draw(player.shape);
                            //Drawing the bullets shot by player to window
                            player.drawBullets(window, player);
                            //Update the enemy position
                            enemy.moveEnemy(window, enemies, player, enemySpeed);
                            //Create new enemies
                            enemy.createNewEnemy(enemies, &enemyTex, window);
                            //Drawing the enemies to window
                            enemy.drawEnemy(window, enemies);
                            //Drawing the score UI
                            window.draw(score);
                            //Drawing the player HP UI
                            window.draw(hpText);
                            //Displaying the window
                            window.display();
                            //Check if game over
                            if (player.hp <= 0)
                            {
                                //Draw game over to window
                                window.draw(gameOver);
                                //Create new event to check
                                sf::Event event3;
                                //Do not close window until escape or x button is pressed
                                while(!GameOver)
                                {
                                    while (window.pollEvent(event3))
                                    {
                                        window.display();
                                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                                        {
                                            GameOver = true;
                                            window.close();
                                        }
                                        if(event3.type == sf::Event::Closed)
                                        {
                                            GameOver = true;
                                            window.close();
                                        }
                                    }
                                }
                            }
                        }

                    }
                    //Check if about menu has been selected
                    if (menu.GetPressedItem() == 1)
                    {
                        //Create boolean value to check if user wants to exit About Menu
                        bool ExitAboutMenu = false;
                        while (!ExitAboutMenu)
                        {
                            //Create new event to check
                            sf::Event event2;
                            while (window.pollEvent(event2))
                            {
                                //Close window if user hits x button in top right of window
                                if(event2.type == sf::Event::Closed)
                                {
                                    ExitAboutMenu = true;
                                    window.close();
                                }
                                //Close About Menu if user enters escape
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                                {
                                    ExitAboutMenu = true;
                                }
                                //Creating About Menu text
                                sf::Text aboutText;
                                aboutText.setFont(hpFont);
                                aboutText.setCharacterSize(45);
                                aboutText.setFillColor(sf::Color::Blue);
                                aboutText.setPosition(0.f, 0.f);
                                aboutText.setString("A Project by Brennon DeBoer\nDecember 2022\nFor Educational Purposes Only\n\nControls: \nMove Up: Up Key or W Key\n"
                                "Move Down: Down Key or S Key\nMove Right: Right Key or D Key\nMove Left: Left Key or A Key\nShoot: LMB or Z Key");
                                window.clear();
                                window.draw(aboutText);
                                window.display();
                            }
                        }
                    }
                    //If Exit button is selected, close the window
                    if (menu.GetPressedItem() == 2)
                    {
                        window.close();
                    }
                }
            }
        }
        //Update window of menu
        window.clear();
        window.draw(background);
        menu.draw(window);
        window.display();
    }
}