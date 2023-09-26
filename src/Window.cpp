#include "Window.h"


Window::Window()
    : m_window(sf::VideoMode(850, 900), "6colors", sf::Style::Titlebar | sf::Style::Close)
{
    m_rect.setSize(sf::Vector2f(850, 30));
    m_rect.setFillColor(sf::Color::White);
    m_rect.setPosition(0, 0);

    m_newBtn_texture.loadFromFile("newButton.png");
    m_newBtn.setTexture(m_newBtn_texture);
    m_newBtn.setPosition(0, 0);

    m_pcWinningScreen.setSize(sf::Vector2f(300, 350));
    m_pcWinningScreen.setOutlineColor(sf::Color::Magenta);
    m_pcWinningScreen.setOutlineThickness(3);
    m_pcWinningScreen.setPosition(270, 270);

    m_userWinningScreen.setSize(sf::Vector2f(300, 350));
    m_userWinningScreen.setOutlineColor(sf::Color::Magenta);
    m_userWinningScreen.setOutlineThickness(3);
    m_userWinningScreen.setPosition(270, 270);

    m_font.loadFromFile("GameDataFont.ttf");

    m_pcWinning.setFont(m_font);
    m_pcWinning.setString("You lost :(");
    m_pcWinning.setCharacterSize(65);
    m_pcWinning.setFillColor(sf::Color::Black);
    m_pcWinning.setStyle(sf::Text::Bold);
    m_pcWinning.setPosition(350, 400);

    m_userWinning.setFont(m_font);
    m_userWinning.setString("You won!! :)");
    m_userWinning.setCharacterSize(65);
    m_userWinning.setFillColor(sf::Color::Black);
    m_userWinning.setStyle(sf::Text::Bold);
    m_userWinning.setPosition(350, 400);

    m_exit_texture.loadFromFile("back.png");
    m_exit.setTexture(m_exit_texture);
    m_exit.setPosition(275, 275);
}


void Window::run()
{
    sf::Vector2f location; 
    sf::Event event;

    bool playerMenu = true;
    int button = -1;
    int color = -1;
    bool gameDisplay = false;
    bool renderWindowTemplate = false;
    bool firstGame = true;
    bool gameEnded = false;

    while (m_window.isOpen())
    {
        while (m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonReleased:
            {
                location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });

                // for the menu
                if (m_newBtn.getGlobalBounds().contains(location))
                    playerMenu = true;

                // for the back btn in menu
                if (m_playerMenu.backClicked(location))        
                    playerMenu = false;
               
                // for menu options
                if (playerMenu)
                    button = m_playerMenu.getButton(location);
                else
                    m_controller.colorsHandler(location, m_window, m_rect, m_newBtn);

                if (m_exit.getGlobalBounds().contains(location))
                {
                    m_controller.resetWinner();
                    gameEnded = false;
                    playerMenu = true;
                }

            }
            }
        }

        sf::Color customColor(212, 212, 212);
        m_window.clear(customColor);

        m_controller.run(m_window);
        drawWindowTemplate();

        if (playerMenu)
        {
            m_playerMenu.run(m_window);

            m_controller.getDifficultyBtn(button);

            if (button > -1)
            {
                if (!firstGame)
                    m_controller.resetBoard();

                firstGame = false;
                gameDisplay = true;
                playerMenu = false;
                button = -1;
            }
        }

        if (m_controller.getWinner() == 0 || m_controller.getWinner() == 1) 
        {
            gameEnded = true;
        }

        if (gameEnded)
        {
            if (m_controller.getWinner() == 0)
            {
                m_window.draw(m_userWinningScreen);
                m_window.draw(m_userWinning);
                m_window.draw(m_exit);
            }
            else if (m_controller.getWinner() == 1)
            {
                m_window.draw(m_pcWinningScreen);
                m_window.draw(m_pcWinning);
                m_window.draw(m_exit);
            }
        }

        m_window.display();
    }
}


void Window::drawWindowTemplate()
{
    m_window.draw(m_rect);
    m_window.draw(m_newBtn);
}