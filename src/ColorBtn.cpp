#include "ColorBtn.h"

ColorBtn::ColorBtn()
	:m_clicked(false)
{}


sf::RectangleShape ColorBtn::getRect() const
{
	return m_btn;
}


void ColorBtn::setRect(const sf::Vector2f size, const sf::Color color, const sf::Color outline, const int j)
{
	m_btn.setSize(size);
	m_btn.setFillColor(color);
	m_btn.setOutlineColor(outline);
	m_btn.setOutlineThickness(1);
	m_btn.setPosition(j * 10, 850);
}


void ColorBtn::setClicked(const bool clicked)
{
	m_clicked = clicked;
}


bool ColorBtn::isClicked() const
{
	return m_clicked;
}