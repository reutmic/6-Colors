#include "Board.h"

Board::Board()
    :m_userNumOfShapes(0), m_pcNumOfShapes(0), m_numOfShapes(0), m_difficulty(-1)
{
    resetBoard();
}


void Board::resetBoard()
{
    int moveRowBy, index = 1;
    float posX = 53.0, posY = 55.0, radius = 17.0;

    m_shapesVector.push_back(ShapeNode<sf::CircleShape>());

    for (int row = 1; row <= ROWS; row++)
    {
        if (row % 2 == 0)
        {
            posX += radius;
        }
        for (int col = 1; col <= COLLS; col++)
        {
            // creating a shape node and setting values to it
            sf::Vector2f vector(posX, posY);
            auto shape = ShapeNode<sf::CircleShape>(index);

            shape.setShapeScale(1.0f, 1.0f);
            shape.setShapeRotation(60.f);
            shape.setShapePoistion(vector);
            shape.setShapeRadius(radius);
            shape.setShapePointCount(6);
            shape.setShapeOutline(2.f, sf::Color::Black);

            setBoardColorAndOwners(row, col, index, shape);

            std::set<int, std::less<int>> mySet = createNeighborsList(index, row, col);

            m_shapesMap.emplace(shape, mySet);
            m_shapesVector.push_back(shape);
            index++;

            posX += (shape.getShapeRadius() * 2) - 3;

        }
        posX = 53.0;
        posY += (radius * 1.5) + 2;
    }

    m_numOfShapes = ROWS * COLLS;
}


void Board::resetTerritories()
{
    m_shapesVector.clear();
    m_shapesMap.clear();
    m_starterColors.clear();
    m_userTerritoryBorder.clear();
    m_pcTerritoryBorder.clear();
    m_userTerritory.clear();
    m_pcTerritory.clear();
}


void Board::setBoardColorAndOwners(const int i, const int j, const int index, ShapeNode<sf::CircleShape>& shape)
{
    int randColor = std::rand() % 6;
    shape.setColor(m_colors[randColor]);
    shape.setColorIndex(randColor);

    if (i == 1 && j == COLLS)
    {
        while (m_shapesVector[index - 1].getColorIndex() == randColor)
            randColor = std::rand() % 6;

        shape.setColorIndex(randColor);
        shape.setColor(m_colors[randColor]);
        shape.setOwner(PC);
        m_starterColors.push_back(randColor);
        m_pcTerritoryBorder.push_back(shape);
        m_pcTerritory.push_back(shape);
        m_pcNumOfShapes++;
    }
    else if (i == 2 && j == COLLS - 1)
    {
        while (m_starterColors[0] == randColor)
            randColor = std::rand() % 6;

        shape.setColorIndex(randColor);
        shape.setColor(m_colors[randColor]);
    }
    else if (i == 2 && j == COLLS)
    {
        while (m_starterColors[0] == randColor)
            randColor = std::rand() % 6;

        shape.setColorIndex(randColor);
        shape.setColor(m_colors[randColor]);
    }
    else if (i == ROWS && j == 1)
    {
        while (m_starterColors[0] == randColor || m_shapesVector[index - COLLS].getColorIndex() == randColor)
            randColor = std::rand() % 6;

        shape.setColorIndex(randColor);
        shape.setColor(m_colors[randColor]);
        shape.setOwner(USER);
        m_starterColors.push_back(randColor);
        m_userTerritoryBorder.push_back(shape);
        m_userNumOfShapes++;
    }
    else if (i == ROWS && j == 2)
    {
        while (m_shapesVector[index - 1].getColorIndex() == randColor)
            randColor = std::rand() % 6;
        shape.setColorIndex(randColor);
        shape.setColor(m_colors[randColor]);
    }
}


void Board::run(sf::RenderWindow& window) 
{
    sf::RectangleShape rectangle(sf::Vector2f(756.f, 731.f));
    rectangle.setPosition(48.f, 70.f);
    rectangle.setFillColor(sf::Color(0, 0, 0, 0)); 
    rectangle.setOutlineThickness(22.f);
    rectangle.setOutlineColor(sf::Color(212, 212, 212));

    for (auto it = m_shapesMap.begin(); it != m_shapesMap.end(); ++it) 
    {
        it->first.drawShape(window);
    }

    window.draw(rectangle);
}


std::set<int, std::less<int>> Board::createNeighborsList(const int index, const int row, const int col) const
{
    std::set<int, std::less<int>> mySet;

    if (row == 1 && col == 1)
    {
        mySet.insert(2);
        mySet.insert(1 + COLLS);
    }
    else if (row == ROWS && col == 1)
    {
        mySet.insert(((ROWS - 2) * COLLS) + 1);
        mySet.insert((ROWS - 1) * COLLS + 2);
    }
    else if (row == 1 && col == COLLS)
    {
        mySet.insert(COLLS - 1);
        mySet.insert((2 * COLLS) - 1);
        mySet.insert(2 * COLLS);
    }
    else if (row == ROWS && col == COLLS)
    {
        mySet.insert((ROWS - 1) * COLLS);
        mySet.insert(((ROWS - 1) * COLLS) - 1);
        mySet.insert((ROWS * COLLS) - 1);
    }
    else if (row == 1 && col >= 2 && col < COLLS)
    {
        mySet.insert(index - 1);
        mySet.insert(index + 1);
        mySet.insert(index + COLLS);
        mySet.insert(index + COLLS - 1);
    }
    else if (row == ROWS && col >= 2 && col < COLLS)
    {
        mySet.insert(index - 1);
        mySet.insert(index + 1);
        mySet.insert(index - COLLS);
        mySet.insert(index - COLLS - 1);
    }
    else if (row >= 2 && row < ROWS && col == 1)
    {
        if (row % 2 == 0)
        {
            mySet.insert(index - COLLS);
            mySet.insert(index - COLLS + 1);
            mySet.insert(index + 1);
            mySet.insert(index + COLLS);
            mySet.insert(index + COLLS + 1);
        }
        else
        {
            mySet.insert(index - COLLS);
            mySet.insert(index + 1);
            mySet.insert(index + COLLS);
        }
    }
    else if (row >= 2 && row < ROWS && col == COLLS)
    {
        if (row % 2 == 0)
        {
            mySet.insert(index + COLLS);
            mySet.insert(index - 1);
            mySet.insert(index - COLLS);
        }
        else
        {
            mySet.insert(index + COLLS);
            mySet.insert(index + COLLS - 1);
            mySet.insert(index - 1);
            mySet.insert(index - COLLS);
            mySet.insert(index - COLLS - 1);
        }
    }
    else
    {
        if (row % 2 == 0)
        {
            mySet.insert(index + 1);
            mySet.insert(index - 1);
            mySet.insert(index - COLLS);
            mySet.insert(index - COLLS + 1);
            mySet.insert(index + COLLS);
            mySet.insert(index + COLLS + 1);
        }
        else
        {
            mySet.insert(index + 1);
            mySet.insert(index - 1);
            mySet.insert(index - COLLS);
            mySet.insert(index - COLLS - 1);
            mySet.insert(index + COLLS);
            mySet.insert(index + COLLS - 1);
        }
    }

    return mySet;
}


std::vector<int> Board::getStarterColors() const
{
    return m_starterColors;
}


void Board::colorTerritory(const OWNED_BY player, const int colorIndex)
{
    std::set<int, std::less<int>> neighborsList;

    for (auto& shape : m_shapesVector)
    {

        if (shape.getOwner() == player)
        {
            if (player == USER)
                shape.setShapeOutline(5.f, sf::Color::White);

            if (player == PC)
                shape.setShapeOutline(5.f, sf::Color(255, 215, 0));

            neighborsList = m_shapesMap[shape];
            m_shapesMap.erase(shape);

            shape.setColorIndex(colorIndex);
            shape.setColor(m_colors[colorIndex]);

            m_shapesMap[shape] = neighborsList;

        }
    }
}


void Board::boardDFS(const OWNED_BY player, const int colorIndex)
{
    m_shapesIndexesToAdd.clear();
    std::set<int, std::less<int>> visitedShapes;

    for (auto& shape : m_shapesVector)
    {
        m_neighborsList = m_shapesMap[shape];
        m_shapesMap.erase(shape);
        shape.setDFSColor(WHITE);
        m_shapesMap[shape] = m_neighborsList;
    }

    for (auto& shape : m_userTerritoryBorder)
    {
        shape.setDFSColor(WHITE);
    }
    for (auto& shape : m_pcTerritoryBorder)
    {
        shape.setDFSColor(WHITE);
    }

    for (auto& shape : player == USER ? m_userTerritoryBorder : m_pcTerritoryBorder)
    {
        if (shape.getDFSColor() == WHITE && visitedShapes.find(shape.getIndex()) == visitedShapes.end())
        {
            DFSVisit(shape, player, colorIndex, visitedShapes);
        }
    }
}


void Board::DFSVisit(ShapeNode<sf::CircleShape>& shape, const OWNED_BY player, const int colorIndex, std::set<int, std::less<int>>& visitedShapes)
{
    std::set<int, std::less<int>> neighborsList = m_shapesMap[shape];

    m_shapesMap.erase(shape);
    shape.setDFSColor(GRAY);
    m_shapesMap[shape] = neighborsList;

    for (auto& neighbor : neighborsList)
    {
        ShapeNode<sf::CircleShape>& currShape = m_shapesVector[neighbor];

        if (currShape.getDFSColor() == WHITE && currShape.getColorIndex() == colorIndex && visitedShapes.find(currShape.getIndex()) == visitedShapes.end())
        {
            m_shapesIndexesToAdd.push_back(currShape.getIndex());

            DFSVisit(currShape, player, colorIndex, visitedShapes);
        }
        visitedShapes.insert(shape.getIndex());
    }

    neighborsList = m_shapesMap[shape];
    m_shapesMap.erase(shape);
    shape.setDFSColor(BLACK);
    m_shapesMap[shape] = neighborsList;
}


int Board::hardDifficultyPC()
{
    std::set<int, std::less<int>> visitedShapes;

    for (auto& shape : m_shapesVector)
    {
        m_neighborsList = m_shapesMap[shape];
        m_shapesMap.erase(shape);
        shape.setDFSColor(WHITE);
        m_shapesMap[shape] = m_neighborsList;
    }


    for (auto& shape : m_pcTerritoryBorder)
    {
        shape.setDFSColor(WHITE);
    }

    int counters[COLORS_NUM];

    for (auto& shape : m_pcTerritoryBorder)
    {
        std::set<int, std::less<int>> neighborsList = m_shapesMap[shape];

        for (auto& neighbor : neighborsList)
        {
            ShapeNode<sf::CircleShape>& neighborShape = m_shapesVector[neighbor];

            if (neighborShape.getDFSColor() == WHITE && visitedShapes.find(neighborShape.getIndex()) == visitedShapes.end() &&
                neighborShape.getColorIndex() != shape.getColorIndex() && neighborShape.getColorIndex() != m_shapesVector[(ROWS - 1) * COLLS + 1].getColorIndex())
            {
                for (int i = 0; i < COLORS_NUM; i++)
                    counters[i] = 0;

                counters[neighborShape.getColorIndex()]++;  
                hardDifficultyColorsCount(neighborShape, neighborShape.getColorIndex(), visitedShapes, counters);
            }
        }
    }

    bool allZeros = std::all_of(std::begin(counters), std::end(counters), [](int element) {
        return element == 0;
        });

    if (allZeros)
        return -1;

    int max = 0, colorIndex;

    for (int i = 0; i < COLORS_NUM; i++)
    {
        if (counters[i] > max)
        {
            max = counters[i];
            colorIndex = i;
        }
    }

    return colorIndex;
}


void Board::hardDifficultyColorsCount(ShapeNode<sf::CircleShape>& shape, const int colorIndex, std::set<int, std::less<int>>& visitedShapes, int counters[])
{
    std::set<int, std::less<int>> neighborsList = m_shapesMap[shape];

    m_shapesMap.erase(shape);
    shape.setDFSColor(GRAY);
    m_shapesMap[shape] = neighborsList;

    for (auto& neighbor : neighborsList)
    {
        ShapeNode<sf::CircleShape>& currShape = m_shapesVector[neighbor];

        if (currShape.getDFSColor() == WHITE && currShape.getColorIndex() == colorIndex && visitedShapes.find(currShape.getIndex()) == visitedShapes.end())
        {
            counters[colorIndex]++;
            hardDifficultyColorsCount(currShape, currShape.getColorIndex(), visitedShapes, counters);
        }
        visitedShapes.insert(shape.getIndex());
    }

    neighborsList = m_shapesMap[shape];
    m_shapesMap.erase(shape);
    shape.setDFSColor(BLACK);
    m_shapesMap[shape] = neighborsList;

}


void Board::updateTerritory(const OWNED_BY player)
{
    for (auto& index : m_shapesIndexesToAdd)
    {
        ShapeNode<sf::CircleShape>& shape = m_shapesVector[index];

        shape.setOwner(player);

        m_neighborsList = m_shapesMap[shape];
        m_shapesMap.erase(shape);
        shape.setOwner(player);
        m_shapesMap[shape] = m_neighborsList;  
    }

    if (player == PC)
    {
        for (auto shape : m_shapesVector)
        {
            if (shape.getOwner() == PC)
                m_pcTerritory.push_back(shape);
        }
    }
}


void Board::updateTerritoryBorder(OWNED_BY player, int colorIndex)
{
    for (auto& index : m_shapesIndexesToAdd)
    {
        if (player == USER)
            m_userTerritoryBorder.push_back(m_shapesVector[index]);
        else if (player == PC)
            m_pcTerritoryBorder.push_back(m_shapesVector[index]);

    }

    std::vector<ShapeNode<sf::CircleShape>>& territoryBorder =
        player == USER ? m_userTerritoryBorder : m_pcTerritoryBorder;

    std::set<int, std::less<int>> indexesToDelete;

    std::for_each(territoryBorder.begin(), territoryBorder.end(), [&](ShapeNode<sf::CircleShape>& shapeNode) {
        const auto& neighborsList = m_shapesMap[shapeNode];

        bool allNeighborsInSameColor = std::all_of(neighborsList.begin(), neighborsList.end(), [this, colorIndex](int value) {
            if (m_shapesVector[value].getColorIndex() == colorIndex)
                return true;
            else
                return false;
            });

        if (allNeighborsInSameColor) {
            auto it = std::find(territoryBorder.begin(), territoryBorder.end(), shapeNode);
            if (it != territoryBorder.end()) {
                indexesToDelete.insert(it->getIndex());
            }
        }
        });

    for (auto& index : indexesToDelete)
    {
        if (player == USER)
        {
            m_userTerritoryBorder.erase(std::remove_if(m_userTerritoryBorder.begin(), m_userTerritoryBorder.end(),
                [index](const ShapeNode<sf::CircleShape>& shapeNode) {
                    return shapeNode.getIndex() == index;
                }), m_userTerritoryBorder.end());
        }

        else
        {
            m_pcTerritoryBorder.erase(std::remove_if(m_pcTerritoryBorder.begin(), m_pcTerritoryBorder.end(),
                [index](const ShapeNode<sf::CircleShape>& shapeNode) {
                    return shapeNode.getIndex() == index;
                }), m_pcTerritoryBorder.end());
        }
    }
}

std::map<ShapeNode<sf::CircleShape>, std::set<int, std::less<int>>> Board::getShapesMap() const
{
    return m_shapesMap;
}


double Board::getNumOfShapes() const
{
    return m_numOfShapes;
}

double Board::getNumOfUserShapes() const
{
    return m_userNumOfShapes;
}

double Board::getNumOfPCShapes() const
{
    return m_pcNumOfShapes;
}

void Board::updateUserNumOfShapes()
{
    int count = std::count_if(m_shapesVector.begin(), m_shapesVector.end(), [](ShapeNode<sf::CircleShape>& shapeNode) {
        return shapeNode.getOwner() == USER;
    });
    m_userNumOfShapes = double(count);
}

void Board::updatePCNumOfShapes()
{
    int count = std::count_if(m_shapesVector.begin(), m_shapesVector.end(), [](ShapeNode<sf::CircleShape>& shapeNode) {
        return shapeNode.getOwner() == PC;
    });
    m_pcNumOfShapes = double(count);
 
}


int Board::getDifficulty() const
{
    return m_difficulty;
}


void Board::setDifficulty(const int difficulty)
{
    m_difficulty = difficulty;
}


int Board::mediumDifficultyPC()
{
    int counters[COLORS_NUM];
    for (int i = 0; i < COLORS_NUM; i++)
        counters[i] = 0;

    int neighborColor, userColor = m_shapesVector[(ROWS-1) * COLLS + 1].getColorIndex();

    std::set<int, std::less<int>> visitedNeighbors;

    for (auto shape : m_pcTerritory)
        visitedNeighbors.insert(shape.getIndex());

    for (auto shape : m_pcTerritoryBorder)
    {
        std::set<int, std::less<int>> neighborsList = m_shapesMap[shape];

        for (auto neighbor : neighborsList)
        {
            neighborColor = m_shapesVector[neighbor].getColorIndex();

            if (visitedNeighbors.find(neighbor) == visitedNeighbors.end() &&
                shape.getColorIndex() != neighborColor && neighborColor != userColor)
                counters[neighborColor]++;

            visitedNeighbors.insert(neighbor);
        }
    }

    bool allZeros = std::all_of(std::begin(counters), std::end(counters), [](int element) {
        return element == 0;
    });

    if (allZeros)
        return -1;

    int max = 0, colorIndex;

    for (int i = 0; i < COLORS_NUM; i++)
    {
        if (counters[i] > max)
        {
            max = counters[i];
            colorIndex = i;
        }
    }

    return colorIndex;
}
