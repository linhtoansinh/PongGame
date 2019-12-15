#include "Help.hpp"

helpMenu::helpMenu()
{

}

helpMenu::helpMenu(float width, float height) :Display(width, height)
{

	// set thông số đồ họa cho tiêu đề
	if (!font.loadFromFile("res/fnt/venus.ttf"))
	{
		std::cout << "Load font failed" << std::endl;
	}

	helpHeadText.setFont(font);
	helpHeadText.setFillColor(sf::Color::Magenta);
	helpHeadText.setString("HELP");
	helpHeadText.setStyle(sf::Text::Underlined);
	helpHeadText.setCharacterSize(50);

	// set thông số đồ họa cho các dòng hướng dẫn
	setPositionText(helpHeadText, 210);

	if (!fontText.loadFromFile("res/fnt/JerseyM54.ttf"))
	{
		std::cout << "Load font failed" << std::endl;
	}

	setText(0, "PLAYER VS PLAYER\n");
	helpText[0].setFillColor(sf::Color::Green);
	setPositionText(helpText[0], 290);

	setText(1, "PLAYER VS COMPUTER\n");
	helpText[1].setFillColor(sf::Color::Green);
	setPositionText(helpText[1], 460);

	setText(4, "PRESS SPACE TO START/CONTINUE GAME\n");
	helpText[4].setFillColor(sf::Color::Green);
	setPositionText(helpText[4], 580);

	setText(5, "PRESS ESC TO COME BACK MAIN MENU ANYTIME\n");
	helpText[5].setFillColor(sf::Color::Magenta);
	helpText[5].setStyle(sf::Text::Bold);
	setPositionText(helpText[5], 640);

	if (!fontText.loadFromFile("res/fnt/Truly.otf"))
	{
		std::cout << "Load font failed" << std::endl;
	}

	setText(2, "Player 1 - Press Up * Move Up\nPlayer 1 - Press Down * Move Down\nPlayer 2 - Press W * Move Up\nPlayer 2 - Press S * Move Down");
	helpText[2].setCharacterSize(25);
	setPositionText(helpText[2], 350);

	setText(3, "Player - Press Up * Move Up\nPlayer - Press Down * Move Down");
	helpText[3].setCharacterSize(25);
	setPositionText(helpText[3], 490);
}

helpMenu::~helpMenu()
{
}

void helpMenu::setText(int select, std::string nameOption)
{
	// set các thông số đồ họa cho Text
	helpText[select].setFont(fontText);
	helpText[select].setCharacterSize(40);
	helpText[select].setFillColor(sf::Color::White);
	helpText[select].setStyle(sf::Text::Regular);
	helpText[select].setString(nameOption);
}

void helpMenu::drawMenu(sf::RenderWindow& window)
{
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {

			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					return;
				}
			}
			window.clear();
			Display::drawMenu(window);
			window.draw(helpHeadText); // in tiêu đề "HELP"

			// in các dòng chữ hướng dẫn
			for (int i = 0; i < 10; i++)
				window.draw(helpText[i]);

			window.display();
		}
	}
}


