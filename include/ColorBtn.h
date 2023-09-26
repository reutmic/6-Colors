#include <SFML/Graphics.hpp>


class ColorBtn {
public:
	ColorBtn();
	sf::RectangleShape getRect() const;
	void setRect(const sf::Vector2f size, const sf::Color color, const sf::Color outline, const int j);
	void setClicked(const bool clicked);
	bool isClicked() const;

private:
	sf::RectangleShape m_btn;
	bool m_clicked;
};