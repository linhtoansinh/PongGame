#ifndef listHighScore_hpp
#define listHighScore_hpp
#include "highScore.hpp"
#include "Display.hpp"
#include <fstream>
#include <vector>
#include <algorithm>

class highScore;
class listHighScore:public Display
{
private:
	std::vector <highScore> highScores;
	sf::Font fontHead;
	sf::Text textHead;

public:
	listHighScore();
	listHighScore(float, float);
	virtual ~listHighScore();

	void addHighScore(highScore);
	void eraseHighScore();

	void sorthHighScores();

	int readFile();
	void drawMenu(sf::RenderWindow& window);
	int updateFile();
};

#endif