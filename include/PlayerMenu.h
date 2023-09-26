#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

const int BTNS = 3;

class PlayerMenu {

public:
	PlayerMenu();
	void run(sf::RenderWindow& window) const;
	bool backClicked(const sf::Vector2f location) const;
	int getButton(const sf::Vector2f location) const;

private:
	sf::RectangleShape m_rect;
	sf::Texture m_exit_texture;
	sf::Sprite m_exit;
	sf::Font m_font;
	sf::Text m_text;
	std::string m_btnsFiles[BTNS] = {"menuBtn1.png", "menuBtn2.png", "menuBtn3.png"};
	sf::Texture m_btns_texture[BTNS];
	std::vector<sf::Sprite> m_btns;
};