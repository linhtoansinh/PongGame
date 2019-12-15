#ifndef continueGame_hpp
#define continueGame_hpp
#include "Ball.hpp"
#include "TextClass.hpp"
#include "PlayerVsComputer.hpp"
#include "highScore.hpp"
#include <string>
#include <fstream>

class continueGame
{
private:
	float ballPosX;
	float ballPosY;
	float ballVelocX;
	float ballVelocY;

	float barAPosY;

	float barBPosY;

	int scoreA;
	int scoreB;

	int healthA;
	int healthB;

	std::string playerA;
	std::string playerB;

	bool mode; // mode = 0: PvsC; mode = 1: PvsP
public:
	continueGame();
	virtual ~continueGame();

	int runContinueGame(sf::RenderWindow& window);
};
#endif
