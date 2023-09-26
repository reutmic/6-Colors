#include "GameData.h"

GameData::GameData()
	:m_playerTerritory(0), m_pcTerritory(0)
{
	m_font.loadFromFile("GameDataFont.ttf");

	resetPlayersPercentage();
	
	m_territoryText[0].setPosition(100, 835);
	m_territoryText[1].setPosition(650, 835);

	m_xTexture.loadFromFile("colorX.png");

	for (int i = 0, j = 30; i < COLORS; i++, j+=4)
	{
		ColorBtn btn;
		btn.setRect(sf::Vector2f(30, 30), m_colors[i], sf::Color::Black, j);
		m_colorsBtns.push_back(btn);

		sf::Sprite xSprite;
		xSprite.setTexture(m_xTexture);
		xSprite.setPosition((j * 10)-1, 849);

		m_x.push_back(xSprite);
	}

	for (auto& colorBtn : m_colorsBtns)
		colorBtn.setClicked(false);
}


void GameData::resetPlayersPercentage()
{
	for (auto& text : m_territoryText)
	{
		text.setFont(m_font);
		text.setString("0.000000");
		text.setCharacterSize(40);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Bold);
	}
}


void GameData::run(sf::RenderWindow& window) const
{
	for (auto& territoryText : m_territoryText)
		window.draw(territoryText);

	for (int i = 0; i < m_colorsBtns.size(); i++)
	{
		window.draw(m_colorsBtns[i].getRect());
		if (m_colorsBtns[i].isClicked())
			window.draw(m_x[i]);
	}
}


bool GameData::handleColorClick(const sf::Vector2f location, sf::RenderWindow& window, sf::RectangleShape& rect, sf::Sprite& newBtn, int &colorIndex)
{
	if (m_colorsBtns[0].getRect().getGlobalBounds().contains(location))
	{
		if (!m_colorsBtns[0].isClicked())
		{
			colorIndex = 0;
			playerTurn(0, window, rect, newBtn);
			return true;
		}
	}

	else if (m_colorsBtns[1].getRect().getGlobalBounds().contains(location))
	{
		if (!m_colorsBtns[1].isClicked())
		{
			colorIndex = 1;
			playerTurn(1, window, rect, newBtn);
			return true;
		}
	}

	else if (m_colorsBtns[2].getRect().getGlobalBounds().contains(location))
	{
		if (!m_colorsBtns[2].isClicked())
		{
			colorIndex = 2;
			playerTurn(2, window, rect, newBtn);
			return true;
		}
	}

	else if (m_colorsBtns[3].getRect().getGlobalBounds().contains(location))
	{
		if (!m_colorsBtns[3].isClicked())
		{
			colorIndex = 3;
			playerTurn(3, window, rect, newBtn);
			return true;
		}
	}

	else if (m_colorsBtns[4].getRect().getGlobalBounds().contains(location))
	{
		if (!m_colorsBtns[4].isClicked())
		{
			colorIndex = 4;
			playerTurn(4, window, rect, newBtn);
			return true;
		}
	}

	else if (m_colorsBtns[5].getRect().getGlobalBounds().contains(location))
	{
		if (!m_colorsBtns[5].isClicked())
		{
			colorIndex = 5;
			playerTurn(5, window, rect, newBtn);
			return true;
		}
	}

	return false;
}


void GameData::playerTurn(const int colorIndex, sf::RenderWindow& window, sf::RectangleShape& rect, sf::Sprite& newBtn)
{
	m_colorsBtns[colorIndex].setClicked(true);

	m_colorsBtns[m_userColorIndex].setClicked(false);

	m_userColorIndex = colorIndex;

	sf::Color customColor(212, 212, 212);
	window.clear(customColor);
	window.draw(rect);
	window.draw(newBtn);
	run(window);
	window.display();
}


int GameData::chooseRandColor() const
{
	int randColor = std::rand() % 6;

	while (m_colorsBtns[randColor].isClicked())
	{
		randColor = std::rand() % 6;
	}

	return randColor;
}


void GameData::pcTurn(int& colorIndex)
{
	m_colorsBtns[colorIndex].setClicked(true);

	m_colorsBtns[m_pcColorIndex].setClicked(false);

	m_pcColorIndex = colorIndex;
}


void GameData::setClickedOfStarterColors(std::vector<int> starterColors)
{
	for (auto& btn : m_colorsBtns)
	{
		btn.setClicked(false);
	}

	for (const auto& index : starterColors)
	{
		m_colorsBtns[index].setClicked(true);	 
	}

	m_pcColorIndex = starterColors[0];
	m_userColorIndex = starterColors[1];
}


int GameData::getCurrUserColor() const
{
	return m_userColorIndex;
}


bool GameData::updateUserPercentage(const double numOfShapes, const double numOfUserShapes)
{
	double percentage = ((numOfUserShapes * 100) / numOfShapes);
	std::string newPercentage = std::to_string(percentage);
	m_territoryText[0].setString(newPercentage);

	if (percentage >= 50)
		return true;

	return false;
}

bool GameData::updatePCPercentage(const double numOfShapes, const double numOfPCShapes)
{
	double percentage = ((numOfPCShapes * 100) / numOfShapes);
	std::string newPercentage = std::to_string(percentage);
	m_territoryText[1].setString((newPercentage));

	if (percentage >= 50)
		return true;

	return false;
}

