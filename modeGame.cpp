﻿#include "modeGame.hpp"

modeGame::modeGame()
{

}

modeGame::~modeGame()
{

}

modeGame::modeGame(float width, float height):Display(width, height)
{
	if(!fontMode.loadFromFile("res/fnt/JerseyM54.ttf"))
	{
		std::cout << "Load font failed" << std::endl;
	}

	// set dòng chữ hiện chế độ đối kháng
	textMode[0].setFont(fontMode);
	textMode[0].setCharacterSize(60);
	textMode[0].setFillColor(sf::Color::White);
	textMode[0].setStyle(sf::Text::Bold);
	textMode[0].setString("PLAYER VS PLAYER");
	setPositionText(textMode[0], 300);

	// set dòng chữ hiện chế độ PvsPC
	textMode[1].setFont(fontMode);
	textMode[1].setCharacterSize(40);
	textMode[1].setFillColor(sf::Color::Red);
	textMode[1].setStyle(sf::Text::Bold);
	textMode[1].setString("PLAYER VS COMPUTER");
	setPositionText(textMode[1], 380);

	select = 0;
}

void modeGame::drawMenu(sf::RenderWindow& window)
{
	Display::drawMenu(window); // vẽ lại Background trong Display
	for (int i = 0; i < 2; i++)
	{
		window.draw(textMode[i]); // vẽ các dòng chữ thể hiện chế độ chơi
	}
}

void modeGame::moveUp() // nhấn phím UP
{
	if (select - 1 >= 0)
	{
		textMode[select].setFillColor(sf::Color::Red);
		textMode[select].setCharacterSize(40);

		// update position because changing size
		setPositionText(textMode[select], 300 + select * 80);

		select--;

		textMode[select].setFillColor(sf::Color::White);
		textMode[select].setCharacterSize(60);

		// update position because changing size
		setPositionText(textMode[select], 300 + select * 80);
	}
}

void modeGame::moveDown() // nhấn phím Down
{
	if (select + 1 < 2)
	{
		textMode[select].setFillColor(sf::Color::Red);
		textMode[select].setCharacterSize(40);

		// update position because changing size
		setPositionText(textMode[select], 300 + select * 80);

		select++;
		textMode[select].setFillColor(sf::Color::White);
		textMode[select].setCharacterSize(60);

		// update position because changing size
		setPositionText(textMode[select], 300 + select * 80);
	}
}

void modeGame::mouseMoved(sf::RenderWindow& windows) // di chuyển chuột
{
	/*  khi di chuyển chuột đên một dòng chữ nào đó
		dòng chữ đó sẽ đổi sang màu trắng và size lớn hơn bình thường
		các dòng chữ còn lại màu đỏ và size bình thường
		cập nhật là select
	*/
	if (clickMouse(textMode[0], windows)) 
	{
		select = 0;

		textMode[0].setFillColor(sf::Color::White);
		textMode[1].setFillColor(sf::Color::Red);

		textMode[0].setCharacterSize(60);
		textMode[1].setCharacterSize(40);

		// update position because changing size
		setPositionText(textMode[0], 300);
		setPositionText(textMode[1], 380);
	}

	if (clickMouse(textMode[1], windows))
	{
		select = 1;

		textMode[0].setFillColor(sf::Color::Red);
		textMode[1].setFillColor(sf::Color::White);

		textMode[0].setCharacterSize(40);
		textMode[1].setCharacterSize(60);

		// update position because changing size
		setPositionText(textMode[0], 300);
		setPositionText(textMode[1], 380);
	}
}

void modeGame::mouseSelect(sf::RenderWindow& window) // bắt sự kiện click chuột
{
	if (clickMouse(textMode[0], window))
	{
		play(window); // chạy chế độ PvsP
	}
	if (clickMouse(textMode[1], window))
	{
		playPvsC(window); // chạy chế độ PvsC
	}
}

void modeGame::runModeGame(sf::RenderWindow& window)
{
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {

			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				mouseMoved(window); // di chuyển chuột
				break;
			case sf::Event::MouseButtonPressed:
			{
				mouseSelect(window); // click chuột
				break;
			}

			case sf::Event::KeyPressed:
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					moveUp(); // di chuyển lên
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					moveDown(); // di chuyển xuống
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					return;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
					switch (GetPressedItem())
					{
					case 0:
						play(window); //  chạy PvcP
						break;
					case 1:
						playPvsC(window); // chạy PvsC
						break;
					}
					break;
			default:
				break;
				}
			}
		}
		window.clear();
		drawMenu(window);
		window.display();
	}
}

int modeGame::GetPressedItem() // lấy giá trị select
{
	return select;
}
