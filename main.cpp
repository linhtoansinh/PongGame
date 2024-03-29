#include "Menu.hpp"
#include "Ball.hpp"
#include "PvsP.hpp"
#include "PvsP.hpp"
#include "BackGround.hpp"
#include "TheBarPartical.hpp"
#include "PlayerVsComputer.hpp"
#include "Help.hpp"
#include "continueGame.hpp"
#include "modeGame.hpp"
#include "listHighScore.hpp"  

int main(int argc, const char* argv[]) {

	sf::RenderWindow window(sf::VideoMode(_WIDTH_SCREEN, _HEIGH_SCREEN), _NAME_GAME_, sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(FRAME);
	window.setKeyRepeatEnabled(true);
	
	Menu menu(window.getSize().x, window.getSize().y);
	helpMenu help(window.getSize().x, window.getSize().y);
	modeGame mode(window.getSize().x, window.getSize().y);
	listHighScore high(window.getSize().x, window.getSize().y);

	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {

			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				menu.mouseMoved(window);
				break;
			case sf::Event::MouseButtonPressed:
			{
				menu.mouseSelect(window);
				break;
			}

			case sf::Event::KeyPressed:
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					menu.moveUp();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					menu.moveDown();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
					switch (menu.GetPressedItem())
					{
					case 0:
						mode.runModeGame(window);
						break;
					case 1:
					{
						continueGame cont;
						cont.runContinueGame(window);
						break;
					}
					case 2:
						high.drawMenu(window);
						break;
					case 3:
						help.drawMenu(window);
						break;
					case 4:
						window.close();
						break;
					}
					break;
			default:
				break;
				}
			}
		}
		window.clear();
		menu.drawMenu(window);
		window.display();

	}
	return 0;
}