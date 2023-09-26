#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayerMenu.h"
#include "Controller.h"

class Window
{
public:
    Window();
    void run();
    void drawWindowTemplate();

private:
    sf::RenderWindow m_window;
    sf::RectangleShape m_rect;
    sf::Texture m_newBtn_texture;
    sf::Sprite m_newBtn;
    PlayerMenu m_playerMenu;
    Controller m_controller;
    sf::RectangleShape m_pcWinningScreen;
    sf::Text m_pcWinning;
    sf::RectangleShape m_userWinningScreen;
    sf::Text m_userWinning;
    sf::Font m_font;
    sf::Texture m_exit_texture;
    sf::Sprite m_exit;
};
