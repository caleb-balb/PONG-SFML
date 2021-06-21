

#include <iostream>
#include <SFML/graphics.hpp>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include <windows.h>
#include <thread>
bool longbeep = false;
bool shortbeep = false;
void makebeep()
{
    while (true)
    {
        if (shortbeep)
        {
            Beep(500, 150);
            shortbeep = false;
        }
        else if (longbeep)
        {
            Beep(300, 300);
            longbeep = false;
        }
    }
}
int main()
{
    float ballspeed = 1;
    std::cout << "pong!\n";
    sf::RenderWindow window(sf::VideoMode(600, 600), "PONG", sf::Style::Close | sf::Style::Resize);
    int reclefty = 0;
    int recrighty = 0;
    int score1 = 0;
    int score2 = 0;
    window.setFramerateLimit(120);
    sf::RectangleShape recleft(sf::Vector2f(5, 100));
    sf::RectangleShape recright(sf::Vector2f(5, 100));
    sf::CircleShape ball;
    ball.setRadius(10);
    ball.setOrigin(10, 10);
    int ballposX = window.getSize().x / 2.f;
    int ballposY = window.getSize().y / 2.f;
    ball.setPosition(ballposX, ballposY);
    //ball random start posiion
    srand(time(NULL));
    float xoffset = (rand() % 2) + 1;
    float yoffset = (rand() % 2) + 1;
    //create gamename and font
    sf::Font font;
    if (!font.loadFromFile("font.ttf"))
    {
        std::cout << "could not load file!" << std::endl;
        return 0;
    }
    sf::Text gamename;
    gamename.setFont(font);
    gamename.setString("PONG");
    gamename.setPosition(250, 10);
    // finish section
    //create score
    sf::Text scoreone;
    scoreone.setFont(font);
    scoreone.setPosition(125, 10);
    sf::Text scoretwo;
    scoretwo.setFont(font);
    scoretwo.setPosition(475, 10);
    //speed
    sf::Text ballspeedX;
    ballspeedX.setFont(font);
    ballspeedX.setCharacterSize(15);
    ballspeedX.setPosition(260, 50);
    std::thread dobeep(&makebeep);
    while (window.isOpen())
    {
        
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == evnt.Closed)
            {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        if (score1 == 11)
        {
            sf::Text playeroneW;
            playeroneW.setFont(font);
            playeroneW.setPosition(ballposX - 200, ballposY);
            playeroneW.setCharacterSize(25);
            playeroneW.setString("player one is the winner!");
            window.draw(playeroneW);
            window.display();
            Sleep(10000);
            return 0;
        }
        if (score2 == 11)
        {
            sf::Text playertwoW;
            playertwoW.setFont(font);
            playertwoW.setPosition(ballposX - 200, ballposY);
            playertwoW.setCharacterSize(25);
            playertwoW.setString("player two is the winner!");
            window.draw(playertwoW);
            window.display();
            Sleep(10000);
            return 0;
        }
        //movment left bar
        if (reclefty > 0 && reclefty < 500)
        {
            if (GetAsyncKeyState('W')) reclefty -= 4;
            if (GetAsyncKeyState('S')) reclefty += 4;
        }
        if (reclefty == 0)
        {
            if (GetAsyncKeyState('S')) reclefty += 4;
        }
        else if (reclefty == 500)
        {
            if (GetAsyncKeyState('W')) reclefty -= 4;
        }
        //movement right bar
        if (recrighty > 0 && recrighty < 500)
        {
            if (GetAsyncKeyState('O')) recrighty -= 4;
            if (GetAsyncKeyState('L')) recrighty += 4;
        }
        if (recrighty == 0)
        {
            if (GetAsyncKeyState('L')) recrighty += 4;
        }
        else if (recrighty == 500)
        {
            if (GetAsyncKeyState('O')) recrighty -= 4;
        }
        //ball movment
        if (ball.getPosition().x <= -2)
        {
            ball.setPosition(ballposX, ballposY);
            ballspeed = 1;
            srand(time(NULL));
            float xoffset = (rand() % 6) + 1;
            float yoffset = (rand() % 6) + 1;
            if (yoffset > 3)
            {
                yoffset *= -1;
            }
            longbeep = true;
            score2++;
        }
        else if (ball.getPosition().x >= 603)
        {
            ball.setPosition(ballposX, ballposY);
            srand(time(NULL));
            ballspeed = 1;
            float xoffset = ((rand() % 6) + 1);
            float yoffset = ((rand() % 6) + 1);
            if (yoffset > 3)
            {
                yoffset *= -1;
            }
            if (xoffset > 3)
            {
                xoffset *= -1;
            }
            longbeep = true;
            score1++;
        }
        if (ball.getPosition().y < 0)
        {
            srand(time(NULL));
            yoffset = (rand() % 2 + 1);

        }
        else if (ball.getPosition().y > 600)
        {
            srand(time(NULL));
            yoffset = -(rand() % 2 + 1);
        }
        if (ball.getPosition().x < 1 && ball.getPosition().y >= recleft.getPosition().y && ball.getPosition().y <= recleft.getPosition().y + 100)
        {
            shortbeep = true;
            ballspeed += 0.5;
            xoffset = 2;
            yoffset = (rand() % 3 + 1);
        }
        if (ball.getPosition().x > 599 && ball.getPosition().y >= recright.getPosition().y && ball.getPosition().y <= recright.getPosition().y + 100)
        {
            shortbeep = true;
            ballspeed += 0.5;
            xoffset = -2;
            yoffset = -(rand() % 3 + 1);
        }
        scoreone.setString(std::to_string(score1));
        scoretwo.setString(std::to_string(score2));
        std::string speedball = std::to_string(ballspeed);
        std::string newballstring;
        for (int i = 0; i < speedball.size(); i++)
        {
            if (speedball[i] != '0')
            {
                newballstring += speedball[i];
            }
        }
        std::string speed = "Speed: " + newballstring;
        ballspeedX.setString(speed);
        ball.move(xoffset * ballspeed, yoffset * ballspeed);
        //std::cout << "y pos left: " << reclefty << std::endl;
        //std::cout << "y pos right: " << recrighty << std::endl;
        recleft.setPosition(0, reclefty);
        recright.setPosition(595, recrighty);
        window.draw(recleft);
        window.draw(recright);
        window.draw(ball);
        window.draw(gamename);
        window.draw(scoreone);
        window.draw(scoretwo);
        window.draw(ballspeedX);
        window.display();
    }
}


