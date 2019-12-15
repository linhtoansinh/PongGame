#ifndef PlayerVsComputer_hpp
#define PlayerVsComputer_hpp

#include "Ball.hpp"	
#include "highScore.hpp"
#include <fstream>

void processPvsC(ThePong&, TheBar&);

void fileEmpty();

void saveGame(ThePong, TheBar, TheBar, bool);

int playPvsC(sf::RenderWindow& window);

#endif


