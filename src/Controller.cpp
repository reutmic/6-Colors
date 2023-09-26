#include "Controller.h"

Controller::Controller()
	:m_winner(-1)
{
	m_data.setClickedOfStarterColors(m_board.getStarterColors());
	m_board.updateUserNumOfShapes();
	m_data.updateUserPercentage(m_board.getNumOfShapes(), m_board.getNumOfUserShapes());
	m_board.updatePCNumOfShapes();
	m_data.updatePCPercentage(m_board.getNumOfShapes(), m_board.getNumOfPCShapes());
}


void Controller::run(sf::RenderWindow& window)
{
	m_data.run(window);
	m_board.run(window);
}


void Controller::colorsHandler(const sf::Vector2f location, sf::RenderWindow& window, sf::RectangleShape& rect, sf::Sprite& newBtn)
{
	int userColorIndex, pcColorIndex;
	if (m_data.handleColorClick(location, window, rect, newBtn, userColorIndex))
	{
		m_board.boardDFS(USER, userColorIndex);
		m_board.updateTerritory(USER);
		m_board.updateTerritoryBorder(USER, userColorIndex);
		m_board.colorTerritory(USER, userColorIndex);
		m_board.updateUserNumOfShapes();
		if (m_data.updateUserPercentage(m_board.getNumOfShapes(), m_board.getNumOfUserShapes()))
		{
			m_winner = 0;
		}

		if (m_winner != 0)
		{
			switch (m_board.getDifficulty())
			{
			case 0:
				pcColorIndex = m_data.chooseRandColor();
				break;
			case 1:
				pcColorIndex = m_board.mediumDifficultyPC();
				if (pcColorIndex == -1)
					pcColorIndex = m_data.chooseRandColor();
				break;
			case 2:
				pcColorIndex = m_board.hardDifficultyPC();
				if (pcColorIndex == -1)
					pcColorIndex = m_data.chooseRandColor();
				break;
			}

			m_data.pcTurn(pcColorIndex);
			m_board.boardDFS(PC, pcColorIndex);
			m_board.updateTerritory(PC);
			m_board.colorTerritory(PC, pcColorIndex);
			m_board.updateTerritoryBorder(PC, pcColorIndex);
			m_board.updatePCNumOfShapes();
			if (m_data.updatePCPercentage(m_board.getNumOfShapes(), m_board.getNumOfPCShapes()))
			{
				m_winner = 1;
			}
		}
		
	}
}


void Controller::getDifficultyBtn(int btn)
{
	m_board.setDifficulty(btn);
}


void Controller::resetBoard()
{
	m_board.resetTerritories();
	m_board.resetBoard();
	m_data.setClickedOfStarterColors(m_board.getStarterColors());
	m_data.resetPlayersPercentage();
}


int Controller::getWinner() const
{
	return m_winner;
}

void Controller::resetWinner()
{
	m_winner = -1;
}
