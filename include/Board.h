#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <iterator>
#include "ShapeNode.h"

const int COLORS_NUM = 6;
const int ROWS = 27;
const int COLLS = 25;


class Board
{
public:
	Board();
	void resetBoard();
	void setBoardColorAndOwners(const int i, const int j, const int index, ShapeNode<sf::CircleShape>& shape);
	void resetTerritories();
	void run(sf::RenderWindow& window);
	std::map<ShapeNode<sf::CircleShape>, std::set<int, std::less<int>>> getShapesMap() const;
	std::set<int, std::less<int>> createNeighborsList(const int index, const int row, const int col) const;
	std::vector<int> getStarterColors() const;
	void colorTerritory(const OWNED_BY player, const int colorIndex);
	void boardDFS(const OWNED_BY player, const int colorIndex);
	void DFSVisit(ShapeNode<sf::CircleShape>& shape, const OWNED_BY player, const int colorIndex, std::set<int, std::less<int>>& visitedShapes);
	int hardDifficultyPC();
	void hardDifficultyColorsCount(ShapeNode<sf::CircleShape>& shape, const int colorIndex, std::set<int, std::less<int>>& visitedShapes, int counters[]);
	void updateTerritoryBorder(OWNED_BY player, int colorIndex);
	void updateTerritory(const OWNED_BY player);
	double getNumOfShapes() const;
	double getNumOfUserShapes() const;
	double getNumOfPCShapes() const;
	void updateUserNumOfShapes();
	void updatePCNumOfShapes();
	int getDifficulty() const;
	void setDifficulty(const int difficulty);
	int mediumDifficultyPC();


private:
	sf::Color m_colors[COLORS_NUM] = {
		sf::Color::Red,
		sf::Color(255, 128, 0),
		sf::Color::Yellow,
		sf::Color::Green,
		sf::Color::Blue,
		sf::Color::Magenta
	};

	int m_difficulty;
	std::map<ShapeNode<sf::CircleShape>, std::set<int, std::less<int>>> m_shapesMap;
	std::vector<ShapeNode<sf::CircleShape>> m_shapesVector;
	std::vector<int> m_starterColors;
	std::vector<ShapeNode<sf::CircleShape>> m_userTerritoryBorder;
	std::vector<ShapeNode<sf::CircleShape>> m_pcTerritoryBorder;
	std::vector<int> m_shapesIndexesToAdd;
	std::set<int, std::less<int>> m_neighborsList;
	std::vector<ShapeNode<sf::CircleShape>> m_userTerritory;
	std::vector<ShapeNode<sf::CircleShape>> m_pcTerritory;
	double m_userNumOfShapes;
	double m_pcNumOfShapes;
	double m_numOfShapes;
};

