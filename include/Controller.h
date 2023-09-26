#include <SFML/Graphics.hpp>
#include "Board.h"
#include "GameData.h"

class Controller
{
public:
	Controller();
	//Controller(sf::RenderWindow& window);
	void run(sf::RenderWindow& window);
	void colorsHandler(const sf::Vector2f location, sf::RenderWindow& window, sf::RectangleShape& rect, sf::Sprite& newBtn);
	void getDifficultyBtn(int btn);
	void resetBoard();
	int getWinner() const;
	void resetWinner();

private:
	Board m_board;
	GameData m_data;
	int m_winner;
};