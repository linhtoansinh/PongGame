#include "continueGame.hpp"

continueGame::continueGame()
{
	std::ifstream fi;

	fi.open("res/file/saveGame.txt");

	if (fi.fail())
	{
		std::cout << "Read file failed\n";
		return;
	}

	fi.seekg(0, std::ios::end); // di chuyển con trỏ từ đầu file đến cuối file
	if (int(fi.tellg()) == 0) // nếu số lượng đọc được là 0
	{
		ballPosX = -1; // set lại hoành độ bóng < 0
		return; // empty file 
	}

	fi.seekg(0); // di chuyển con trỏ về đầu file


	// đọc các thông số về bóng
	fi >> ballPosX;
	fi >> ballPosY;
	fi >> ballVelocX;
	fi >> ballVelocY;

	// đọc các thông số về thanh
	fi >> barAPosY;
	fi >> barBPosY;

	// đọc các thông số về điểm
	fi >> scoreA;
	fi >> scoreB;

	// đọc các thông số về số mạng còn lại
	fi >> healthA;
	fi >> healthB;

	// đọc các thông số về tên người chơi
	fi >> playerA;
	fi >> playerB;

	// đọc chế độ chơi
	fi >> mode;

	fi.close();
}

continueGame::~continueGame()
{

}

int continueGame::runContinueGame(sf::RenderWindow& window)
{
	
	if (ballPosX == -1) // file rỗng
		return 0;

	// thiết lập game với các thông số đã đọc từ file
	ThePong ball(ballPosX, ballPosY, ballVelocX, ballVelocY);
	BackGround bg;
	TheBar barA(true, barAPosY, scoreA, healthA, playerA);
	TheBar barB(false, barBPosY, scoreB, healthB, playerB);
	

	TextShow textshow(std::string("Press Space to continue"), std::string("HACKED.ttf"), _WIDTH_TABLE_GAME_ / 2 + 50, _HEIGH_TABLE_GAME_ - 2 * _DIS_FROM_TOP_);
	bool cont = true;
	bg.setNamePlayer(barA.getNameplayer(), barB.getNameplayer());
	bg.setHealth(barA.getHealth(), barB.getHealth());
	bg.setRate(barA.getScores(), barB.getScores());
	
	// start ball when press space
	while (window.isOpen() && cont) {
		sf::Event event;

		while (window.pollEvent(event) && cont) {
			switch (event.type) {
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					cont = false;
					if (ball.getPosX() == 100 || ball.getPosX() == 1180)
						ball.resetPong(0);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					saveGame(ball, barA, barB, mode);
					return 0;
				}
				break;
			case sf::Event::Closed:
				saveGame(ball, barA, barB, mode);
				window.close();
				break;
			default:
				continue;
			}
		}

		window.clear();
		bg.setHealth(barA.getHealth(), barB.getHealth());
		bg.setRate(barA.getScores(), barB.getScores());
		bg.draw(window);
		barA.draw(window);
		barB.draw(window);
		ball.draw(window);
		textshow.drawText(window);
		window.display();
	}

	// start game
	while (window.isOpen()) {
		if (mode == 0) // PvsC
		{
			processPvsC(ball, barA);
		}

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				saveGame(ball, barA, barB, mode);
				window.close();
			}
			else if (sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					saveGame(ball, barA, barB, mode);
					return 0;
				}
			}
		}

		window.setFramerateLimit(5 * FRAME);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mode == 1) {
			barA.moveBar(window, true, false);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && mode == 1) {
			barA.moveBar(window, false, true);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			barB.moveBar(window, true, false);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			barB.moveBar(window, false, true);
		}
		window.setFramerateLimit(FRAME);

		short prob = ball.moveBall(window, copyPos(barA.getPosX(), barA.getPosY(), barA.getHeigh(), barA.getWidth()), copyPos(barB.getPosX(), barB.getPosY(), barB.getHeigh(), barB.getWidth()), copyPos(barA.getPosX(), barA.getPosY(), barA.getHeigh(), barA.getWidth()));
		if (prob == -1 || prob == 1) // crash to wall left or right
		{
            short toward = 0;
			if (prob == 1)     // lose right
			{
                toward = -1;
				barB.loseHealth();
				if (barB.getHealth() == 0) {
					// lưu điểm
					highScore A;
					A.setGoalDiff(abs(barA.getScores()+barB.getScores()));
					A.writeFile();
					TextShow winner(barA.getNameplayer() + std::string(" Chien thang!"), std::string("HACKED.ttf"), 1, 1);
					winner.setPosition((_WIDTH_SCREEN - winner.getSizeText() / 2) / 2, (_HEIGH_TABLE_GAME_ - winner.getSizeCharacter()) / 2);
					//std::cout << winner.getSizeCharacter() << std::endl;
					winner.scale(2);
					// display winning screen
					while (window.isOpen()) {
						sf::Event event;
						while (window.pollEvent(event)) {
							switch (event.type) {
							case sf::Event::KeyPressed:
								if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
								{
									fileEmpty();
									return 1;
								}
                                break;
							case sf::Event::Closed:
								fileEmpty();
								window.close();
								break;
							default:
								continue;
							}
						}

						window.clear();
						bg.setHealth(barA.getHealth(), barB.getHealth());
						bg.setRate(barA.getScores(), barB.getScores());
						bg.draw(window);
						barA.draw(window);
						barB.draw(window);
						ball.draw(window);
						textshow.drawText(window);
						winner.drawText(window);
						window.display();
					}
					return 1; // end game
				}
			}
			else if (prob == -1)     // lose left
			{
                toward = 1;
				barA.loseHealth();
				if (barA.getHealth() == 0) {
					// lưu điểm
					highScore A;
					A.setGoalDiff(abs(barA.getScores() + barB.getScores()));
					A.writeFile();
					TextShow winner(barB.getNameplayer() + std::string(" Chien thang!"), std::string("HACKED.ttf"), 1, 1);
					winner.setPosition((_WIDTH_SCREEN - winner.getSizeText() / 2) / 2, (_HEIGH_TABLE_GAME_ - winner.getSizeCharacter()) / 2);
					winner.scale(2);

					// display winning screen
					while (window.isOpen()) {
						sf::Event event;
						while (window.pollEvent(event)) {
							switch (event.type) {
							case sf::Event::KeyPressed:
								if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
								{
									fileEmpty();
									return 1;
								}
                                break;
							case sf::Event::Closed:
								fileEmpty();
								window.close();
								break;
							default:
								continue;
							}
						}

						window.clear();
						bg.setHealth(barA.getHealth(), barB.getHealth());
						bg.setRate(barA.getScores(), barB.getScores());
						bg.draw(window);
						barA.draw(window);
						barB.draw(window);
						ball.draw(window);
						textshow.drawText(window);
						winner.drawText(window);
						window.display();
					}
					return 1; // end game
				}
			}
			cont = true;

			while (window.isOpen() && cont) {
				sf::Event event;
				while (window.pollEvent(event) && cont) {
					switch (event.type) {
					case sf::Event::KeyPressed:
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						{
							cont = false;
						}

						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
							saveGame(ball, barA, barB, 1);
							return 0;
						}
						break;
					case sf::Event::Closed:
						saveGame(ball, barA, barB, 1);
						window.close();
						break;
					default:
						continue;
					}
				}

				window.clear();
				bg.setHealth(barA.getHealth(), barB.getHealth());
				bg.setRate(barA.getScores(), barB.getScores());
				bg.draw(window);
				barA.draw(window);
				barB.draw(window);
				ball.draw(window);
				textshow.drawText(window);
				window.display();
			}
			ball.resetPong(toward);

		}
		else {
			if (prob == 2) {
				barB.haveScore();
//				if (barB.getScores() - barA.getScores() > 1) {
//					barB.setScores(barA.getScores() + 1);
//				}
			}
			else if (prob == -2) {
				barA.haveScore();
//				if (barA.getScores() - barB.getScores() > 1) {
//					barA.setScores(barB.getScores() + 1);
//				}
			}
		}
		//>>>>>>>>>>>>>>>>>>>>>

		window.clear();
		bg.setHealth(barA.getHealth(), barB.getHealth());
		bg.setRate(barA.getScores(), barB.getScores());
		bg.draw(window);
		barA.draw(window);
		barB.draw(window);
		ball.draw(window);
		window.display();
	}
	return 0;
}

