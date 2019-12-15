#include "PvsP.hpp"
#include "Ball.hpp"
#include "PvsP.hpp"
#include "Menu.hpp"
#include "Gift.h"	//coi chừng bị overload ball


int play(sf::RenderWindow& window) {

    // khởi tạo sân, bóng, 2 thanh
	BackGround bg;
	ThePong ball;
	TheBar barA(true);
	TheBar barB(false);

	//khởi tạo vật phẩm
	Gift gift("res/img/gift1.png");

    // khởi động chuỗi thông báo và tên
	TextShow textshow(std::string("Press Space to continue"), std::string("HACKED.ttf"), _WIDTH_TABLE_GAME_ / 2 + 50, _HEIGH_TABLE_GAME_ - 2 * _DIS_FROM_TOP_);
	barA.setNamePlayer(std::string("PlayerA"));
	barB.setNamePlayer(std::string("PlayerB"));

    // set tên
	bg.setNamePlayer(barA.getNameplayer(), barB.getNameplayer());

	bool cont = true;
	// start ball when press space
	while (window.isOpen() && cont) {
		sf::Event event;
        // bắt sự kiện
		while (window.pollEvent(event) && cont) {
			switch (event.type) {
			case sf::Event::KeyPressed:         // sự kiện nhấn phím
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
			case sf::Event::Closed:             // sự kiện đóng cửa sổ
				window.close();
				break;
			default:
				continue;
			}
		}
        // vẽ
		window.clear();
		bg.setHealth(barA.getHealth(), barB.getHealth());
		bg.setRate(barA.getScores(), barB.getScores());
		bg.draw(window);
		barA.draw(window);
		barB.draw(window);
		ball.draw(window);
		textshow.drawText(window);
		gift.draw(window);
		
		window.display();
	}

	// start game
	while (window.isOpen()) {
		
		
		sf::Event event;
        // bắt sự kiện
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				saveGame(ball, barA, barB, 1);
				window.close();
			}
			else if (sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					saveGame(ball, barA, barB, 1);
					return 0;
				}
			}
		}
		
        // sự kiện nhấn di chuyển thanh
		window.setFramerateLimit(5 * FRAME);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			barA.moveBar(window, true, false);
			barA.draw(window);	//?????
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			barA.moveBar(window, false, true);
			barA.draw(window);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			barB.moveBar(window, true, false);
			barB.draw(window);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			barB.moveBar(window, false, true);
			barB.draw(window);
		}
		window.setFramerateLimit(FRAME);

        // nhận kết quả sau khi
		short prob = ball.moveBall(window, copyPos(barA.getPosX(), barA.getPosY(), barA.getHeigh(), barA.getWidth()), copyPos(barB.getPosX(), barB.getPosY(), barB.getHeigh(), barB.getWidth()),copyPos(gift.getPosX(), gift.getPosY(), gift.getPosYend(), gift.getPosXend()));
		if (prob == -3)
		{
			barB.getScores();
		

		}
		if (prob == -1 || prob == 1) // crash to wall left or right
		{
            short toward = 0;       // -1 - bóng đi về phía bên trái ; 0 - bóng di chuyển hướng theo hướng ngẫu nhiên ; 1 - bóng đi về hướng bên phải
			if (prob == 1)     // lose right
			{
                toward = -1;        // vì bóng chạm biên phải nên bóng sẽ bắt đầu đi về phía bên trái
				barB.loseHealth();  // trừ máu bên phải
				if (barB.getHealth() == 0) {    // nếu máu giảm về 0, xử lý kết thúc game
					// lưu điểm
					highScore A;                // lưu điểm cao
					A.setGoalDiff(abs(barA.getScores() + barB.getScores()));
					A.writeFile();
                    
                    // dòng chữ thông báo lúc kết thúc game
					TextShow winner(barA.getNameplayer() + std::string(" Chien thang!"), std::string("HACKED.ttf"), 1, 1);
					winner.setPosition((_WIDTH_SCREEN - winner.getSizeText() / 2) / 2, (_HEIGH_TABLE_GAME_ - winner.getSizeCharacter()) / 2);
					winner.scale(2);

					// display winning screen
					while (window.isOpen()) {
						sf::Event event;
						while (window.pollEvent(event)) {
							switch (event.type) {
							case sf::Event::KeyPressed: // sự kiện nhấn keyboard
								if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
								{
									fileEmpty();        // làm rỗng file lưu game vì game đã kết thúc
									return 1;
								}
                                break;
							case sf::Event::Closed:
								fileEmpty();            // làm rỗng file lưu game vì game đã kết thúc
								window.close();
								break;
							default:
								continue;
							}
						}

                        // in thông tin ra màn hình
						window.clear();
						bg.setHealth(barA.getHealth(), barB.getHealth());
						bg.setRate(barA.getScores(), barB.getScores());
						bg.draw(window);
						barA.draw(window);
						barB.draw(window);
						ball.draw(window);
						textshow.drawText(window);
						winner.drawText(window);
						gift.draw(window);
						window.display();
					}
					return 1; // end game
				}
			}
			else if (prob == -1)     // lose left
			{
                toward = 1;          // vì bóng chạm biên trái nên bóng sẽ bắt đầu đi về phía bên phải
				barA.loseHealth();   // trừ máu bên trái
				if (barA.getHealth() == 0) {    // nếu máu giảm về 0, xử lý kết thúc game
					// lưu điểm
					highScore A;
					A.setGoalDiff(abs(barA.getScores() + barB.getScores()));
					A.writeFile();
                    
                    // dòng chữ thông báo lúc kết thúc game
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
									fileEmpty();        // làm file lưu game rỗng vì game đã kết thúc
									return 1;
								}
                                break;
							case sf::Event::Closed:
								fileEmpty();          // làm file lưu game rỗng vì game đã kết thúc
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
						gift.draw(window);
						window.display();
					}
					return 1; // end game
				}
			}
			cont = true;

            // nếu game chạm biên nhưng chưa kết thúc, nhấn space để tiếp tục và ESC để thoát
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
							saveGame(ball, barA, barB, 1);        // lưu game
							return 0;
						}
						break;
					case sf::Event::Closed:
						saveGame(ball, barA, barB, 1);            // lưu game
						window.close();
						break;
					default:
						continue;
					}
				}

                // in ra màn hình game
				window.clear();
				bg.setHealth(barA.getHealth(), barB.getHealth());
				bg.setRate(barA.getScores(), barB.getScores());
				bg.draw(window);
				barA.draw(window);
				barB.draw(window);
				ball.draw(window);
				textshow.drawText(window);
				gift.draw(window);
				window.display();
			}
			ball.resetPong(toward);

		}
		else {      // đây là khu vực nếu thanh bắt được bóng
            
			if (prob == 2) {    // chạm thanh phải
				barB.haveScore();
//				if (barB.getScores() - barA.getScores() > 1) {
//					barB.setScores(barA.getScores() + 1);
//				}
			}
			else if (prob == -2) {    // chạm thanh trái
				barA.haveScore();
//				if (barA.getScores() - barB.getScores() > 1) {
//					barA.setScores(barB.getScores() + 1);
//				}
			}
		}
        
        // in ra màn hình game
		window.clear();
		bg.setHealth(barA.getHealth(), barB.getHealth());
		bg.setRate(barA.getScores(), barB.getScores());
		bg.draw(window);
		barA.draw(window);
		barB.draw(window);
		ball.draw(window);
		gift.draw(window);
		window.display();
	}
	return 0;
}
