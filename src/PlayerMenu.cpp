#include "PlayerMenu.h"

PlayerMenu::PlayerMenu()
{
    m_rect.setSize(sf::Vector2f(300, 350));
    m_rect.setOutlineColor(sf::Color::Magenta);
    m_rect.setOutlineThickness(3);
    m_rect.setPosition(270, 270);

    m_exit_texture.loadFromFile("back.png");
    m_exit.setTexture(m_exit_texture);
    m_exit.setPosition(275, 275);

    m_font.loadFromFile("GameDataFont.ttf");

    m_text.setFont(m_font);
    m_text.setString("Select difficulty:");
    m_text.setCharacterSize(65);
    m_text.setFillColor(sf::Color::Black);
    m_text.setStyle(sf::Text::Bold);
    m_text.setPosition(290, 285);


    for (int i = 0, j = 15; i < BTNS; i++, j+=3)
    {
        m_btns_texture[i].loadFromFile(m_btnsFiles[i]);
        sf::Sprite sprite;
        m_btns.push_back(sprite);
        m_btns[i].setTexture(m_btns_texture[i]);
        m_btns[i].setPosition(315, j*26);
    }
}


void PlayerMenu::run(sf::RenderWindow& window) const
{
    window.draw(m_rect);
    window.draw(m_exit);
    window.draw(m_text);
    for (auto& btn : m_btns)
        window.draw(btn);
    
}


bool PlayerMenu::backClicked(const sf::Vector2f location) const
{
    if (m_exit.getGlobalBounds().contains(location))
        return true;

    return false;
}

 
int PlayerMenu::getButton(const sf::Vector2f location) const
{
    if (m_btns[0].getGlobalBounds().contains(location))
        return 0;
    else if (m_btns[1].getGlobalBounds().contains(location))
        return 1;
    else if (m_btns[2].getGlobalBounds().contains(location))
        return 2;
    else
        return -1;
}