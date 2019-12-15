#include "PlayerVsComputer.hpp"

void processPvsC(ThePong &ball, TheBar& computer)
{
	// nếu tung độ bóng lớn hơn vị trí trung tâm thanh và tung độ bóng nhỏ hơn biên dưới sân đấu -> di chuyển lên
	if (ball.getPosY() > computer.getPosY() + computer.getLongBar() / 2 && ball.getPosY() < (_HEIGH_TABLE_GAME_+ _DIS_FROM_TOP_))
	{
		if ((computer.getPosY() + computer.getLongBar() + _VELOCITY_Y_BAR_ + 2) > (_HEIGH_TABLE_GAME_ + _DIS_FROM_TOP_)) {
			computer.setPosY(_HEIGH_TABLE_GAME_ +_DIS_FROM_TOP_ - computer.getLongBar());
		}
		else {
			computer.setPosY(computer.getPosY() + _VELOCITY_Y_BAR_ + 2);
		}
	}

	// nếu tung độ bóng nhỏ hơn vị trí trung tâm thanh -> di chuyển xuống xuống
	else if (ball.getPosY() < computer.getPosY() + computer.getLongBar() / 2)
	{
		if (computer.getPosY() - _VELOCITY_Y_BAR_ < _DIS_FROM_TOP_) {
			computer.setPosY(_DIS_FROM_TOP_);
		}
		else {
			computer.setPosY(computer.getPosY() - (_VELOCITY_Y_BAR_ + 2));
		}
	}
}

void fileEmpty() // làm cho file rỗng
{
	std::ofstream fo; 

	fo.open("res/file/saveGame.txt");
	if (fo.fail())
	{
		std::cout << "Open file failed\n";
		return;
	}

	fo.close();
}

void saveGame(ThePong ball, TheBar barA, TheBar barB, bool mode) // lưu game khi bấm thoát hoặc ESC
{
	std::ofstream fo;

	fo.open("res/file/saveGame.txt");
	if (fo.fail())
	{
		std::cout << "Open file failed\n";
		return;
	}
	
	fo << ball.getPosX() << " ";
	fo << ball.getPosY() << " ";
	fo << ball.getVelocityX() << " ";
	fo << ball.getVelocityY() << " ";

	fo << barA.getPosY() << " ";
	fo << barB.getPosY() << " ";

	fo << barA.getScores() << " ";
	fo << barB.getScores() << " ";

	fo << barA.getHealth() << " ";
	fo << barB.getHealth() << " ";

	fo << barA.getNameplayer() << " ";
	fo << barB.getNameplayer() << " ";

	fo << mode; // lưu chế độ chơi, 0 = PvsC, 1 = PvsP

	fo.close();
}

int playPvsC(sf::RenderWindow& window)
{
	// Khởi tạo thanh người chơi và máy tính
	BackGround bg;
	ThePong ball;

	TheBar player(false); //false thanh nằm bên phải
	TheBar computer(true); // true thanh nằm bên trái 
	Gift gift;

    // khởi tạo dòng thông báo ban đầu
	TextShow textshow(std::string("Press Space to continue"), std::string("HACKED.ttf"), _WIDTH_TABLE_GAME_ / 2 + 50, _HEIGH_TABLE_GAME_ - 2 * _DIS_FROM_TOP_);
    
    // khởi tạo tên
    computer.setNamePlayer(std::string("Computer"));
    player.setNamePlayer(std::string("Player"));
    bg.setNamePlayer(computer.getNameplayer(), player.getNameplayer());
    
	bool cont = true;
	// start ball when press space
	while (window.isOpen() && cont) {
		sf::Event event;

		while (window.pollEvent(event) && cont) {
			switch (event.type) {
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					cont = false;
					ball.resetPong(0);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					return 0;
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				continue;
			}
		}
        // in ra màn hình chơi
		window.clear();
		bg.setHealth(computer.getHealth(), player.getHealth());
		bg.setRate(computer.getScores(), player.getScores());
		bg.draw(window);
		player.draw(window);
		computer.draw(window);
		ball.draw(window);
		textshow.drawText(window);
		window.display();
	}

	// start game
	while (window.isOpen()) {
		processPvsC(ball, computer);
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				saveGame(ball, computer, player, 0);
				window.close();
			}
			else if (sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					saveGame(ball, computer, player, 0);
					return 0;
				}
			}
		}
        
        // sự kiện điều khiển thanh trượt
		window.setFramerateLimit(5 * FRAME);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			player.moveBar(window, true, false);
			player.draw(window);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			player.moveBar(window, false, true);
			player.draw(window);
		}
		window.setFramerateLimit(FRAME);
	
        // bắt sự kiện của quả bóng
		short prob = ball.moveBall(window, copyPos(computer.getPosX(), computer.getPosY(), computer.getHeigh(), computer.getWidth()), copyPos(player.getPosX(), player.getPosY(), player.getHeigh(), player.getWidth()),gift.getPos());
        if (prob == -1 || prob == 1) // crash to wall left or right
        {
            short toward = 0;
            if (prob == 1)     // lose right
            {
                toward = -1;
                player.loseHealth();
                if (player.getHealth() == 0) {
					// lưu điểm
					highScore A;
					A.setGoalDiff(abs(computer.getScores() + player.getScores()));
					A.writeFile();
                    
                    // dòng thông tin chiến thắng
					TextShow winner(computer.getNameplayer() + std::string(" Chien thang!"), std::string("HACKED.ttf"), 1, 1);
                    winner.setPosition((_WIDTH_SCREEN - winner.getSizeText()/2) / 2, (_HEIGH_TABLE_GAME_ - winner.getSizeCharacter())/2);
                    
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
                        bg.setHealth(computer.getHealth(), player.getHealth());
                        bg.setRate(computer.getScores(), player.getScores());
                        bg.draw(window);
                        computer.draw(window);
                        player.draw(window);
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
				computer.loseHealth();
                if (computer.getHealth() == 0) {
					// lưu điểm
					highScore A;
					A.setGoalDiff(abs(computer.getScores() + player.getScores()));
					A.writeFile();
                    
                    // dòng thông tin chiến thắng
                    TextShow winner(player.getNameplayer() + std::string(" Chien thang!"), std::string("HACKED.ttf"), 1, 1);
                    winner.setPosition((_WIDTH_SCREEN - winner.getSizeText()/2) / 2, (_HEIGH_TABLE_GAME_ - winner.getSizeCharacter())/2);
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
                        bg.setHealth(computer.getHealth(), player.getHealth());
                        bg.setRate(computer.getScores(), player.getScores());
                        bg.draw(window);
                        computer.draw(window);
                        player.draw(window);
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
                            saveGame(ball, computer, player, 0);
                            return 0;
                        }
                        break;
                    case sf::Event::Closed:
                        saveGame(ball, computer, player, 0);
                        window.close();
                        break;
                    default:
                        continue;
                    }
                }

                window.clear();
                bg.setHealth(computer.getHealth(), player.getHealth());
                bg.setRate(computer.getScores(), player.getScores());
                bg.draw(window);
                computer.draw(window);
                player.draw(window);
                ball.draw(window);
                textshow.drawText(window);
                window.display();
            }
            ball.resetPong(toward);
            
        }
        else {
            if (prob == 2) {
                player.haveScore();
//                if (player.getScores() - computer.getScores() > 1) {
//                    player.setScores(computer.getScores() + 1);
//                }
            }
            else if (prob == -2) {
                computer.haveScore();
//                if (computer.getScores() - player.getScores() > 1) {
//                    computer.setScores(player.getScores() + 1);
//                }
            }
        }
        
		window.clear();
        bg.setHealth(computer.getHealth(), player.getHealth());
        bg.setRate(computer.getScores(), player.getScores());
		bg.draw(window);
		computer.draw(window);
		player.draw(window);
		ball.draw(window);
		window.display();
	}
	return 0;
}
