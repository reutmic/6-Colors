#include <SFML/Graphics.hpp>

enum OWNED_BY {
	NONE,
	USER,
	PC
};

enum DFS_COLOR {
	WHITE,
	GRAY,
	BLACK
};

template <class T>
class ShapeNode {

public:
	ShapeNode()
	{};

	ShapeNode(const int index)
		:m_index(index)
	{
		m_ownedBy = NONE;
	};

	int getIndex() const { return m_index; }

	int getColorIndex() const { return m_colorIndex; };

	void setColorIndex(const int colorIndex) { m_colorIndex = colorIndex; };

	sf::Color getColor() const { return m_color; }

	void setColor(sf::Color color) { m_shape.setFillColor(color); }

	void setShapePoistion(const sf::Vector2f location) { m_shape.setPosition(location); }

	void setShapeScale(const float x, const float y) { m_shape.setScale(x, y); }

	void setShapeRotation(const float r) { m_shape.setRotation(r); }

	float getShapeRadius() const { return m_shape.getRadius(); }

	void setShapeRadius(const float r) { m_shape.setRadius(r); }

	void setShapePointCount(const int num) { m_shape.setPointCount(num); }

	void setShapeOutline(const float r, sf::Color color)
	{
		m_shape.setOutlineThickness(r);
		m_shape.setOutlineColor(color);
	}

	OWNED_BY getOwner() const { return m_ownedBy; }

	void setOwner(OWNED_BY ownedBy) { m_ownedBy = ownedBy; }

	bool operator<(const ShapeNode& other) const { return m_index < other.m_index; }

	bool operator>(const ShapeNode& other) const { return m_index > other.m_index; }

	bool operator<=(const ShapeNode& other) const { return m_index <= other.m_index; }

	bool operator>=(const ShapeNode& other) const { return m_index >= other.m_index; }

	bool operator==(const ShapeNode& other) const { return m_index == other.m_index; }

	void drawShape(sf::RenderWindow& window) const { window.draw(m_shape); }

	DFS_COLOR getDFSColor() const { return m_DFSColor; }

	void setDFSColor(const DFS_COLOR color) { m_DFSColor = color; }


private:
	unsigned int m_index;
	int m_colorIndex;
	sf::Color m_color;
	OWNED_BY m_ownedBy;
	T m_shape;
	DFS_COLOR m_DFSColor;
};

