#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include "ColorBtn.h"

const int COLORS = 6;
const int PLAYERS = 2;


class GameData
{
public:
	GameData();
	void run(sf::RenderWindow& window) const;
	bool handleColorClick(const sf::Vector2f location, sf::RenderWindow& window, sf::RectangleShape& rect, sf::Sprite& newBtn, int &colorIndex);
	void playerTurn(const int colorIndex, sf::RenderWindow& window, sf::RectangleShape& rect, sf::Sprite& newBtn);
	int chooseRandColor() const;
	void pcTurn(int& colorIndex);
	void setClickedOfStarterColors(std::vector<int> starterColors);
	int getCurrUserColor() const;
	bool updateUserPercentage(const double numOfShapes, const double numOfUserShapes);
	bool updatePCPercentage(const double numOfShapes, const double numOfPCShapes);
	void resetPlayersPercentage();



private:
	sf::Color m_colors[COLORS] = {
		sf::Color::Red,
		sf::Color(255, 128, 0),
		sf::Color::Yellow,
		sf::Color::Green,
		sf::Color::Blue,
		sf::Color::Magenta
	};

	std::vector<ColorBtn> m_colorsBtns;
	sf::Texture m_xTexture;
	std::vector<sf::Sprite> m_x;
	double m_playerTerritory;
	double m_pcTerritory;
	sf::Font m_font;
	sf::Text m_territoryText[PLAYERS];

	int m_userColorIndex;
	int m_pcColorIndex;
};