#ifndef Ball_hpp
#define Ball_hpp

#include <iostream>
#include "TheBarPartical.hpp"
#include <SFML/Graphics.hpp>
#include "BackGround.hpp"
#include "DataPos.hpp"
#include "TextClass.hpp"
#include "Gift.h"
#include <string>
#include <ctime>
#include <math.h>

#define _WIDTH_SCREEN 1280
#define _HEIGH_SCREEN 780

#define _NAME_GAME_ "The Pong Game"

#define sqr(x) x * x

// vận tốc bóng theo x
#define _VELOCITY_X_ 5.0
// vận tốc bóng theo y
#define _VELOCITY_Y_ 5.0
// vận tốc thanh trượt
#define _VELOCITY_Y_BAR_ 3
// tốc độ thay đổi thay trượt
#define _VELOCITY_Y_BAR_STEP_ 0.1
// vận tốc bóng nhanh nhất
#define _MAX_VELOCITY_ 10
// tốc độ thay đổi vận tốc
#define _ACCELERATION_ 1.1
#define _ACCELERATION_BAR_ 5
// cạnh quả bóng
#define _SIZE_PONG_ 25
#define _SMALL_NUMBER_ 0.001
#define _MAX_CHANGE_VELOC_ 3
#define _ANGLE_BUFF_ 0.3

#define _HEIGH_BAR_ 20
#define _WIDTH_BAR_ 180

// FRAME WINDOW
#define MAX_FRAME_LIMIT 300
#define FRAME ((_WIDTH_TABLE_GAME_ * 1.0 / _VELOCITY_X_ < MAX_FRAME_LIMIT) ? (_WIDTH_TABLE_GAME_ * 1.0 / _VELOCITY_X_) : MAX_FRAME_LIMIT)

class ThePong {
private:
	float posX;
	float posY;

	sf::Texture textureBall;
	sf::Sprite imgSpr;

	float posXend;
	float posYend;

	float velocityX;
	float velocityY;
	float acceleration;



public:
	ThePong();
	ThePong(float, float, float, float);
	virtual ~ThePong();

	void setPosX(float x);
	void setPosY(float y);
	float getPosX();
	float getPosY();
	float getVelocityX();
	float getVelocityY();

	void updateVelocityX();
	void updateVelocityY();

	void resetPong(short toward); //     -1 - left ;     0 - random ;    1 - right

	void scale(float width, float heigh);
	short moveBall(sf::RenderWindow& window, Pos positionLeft, Pos positionRight, Pos gift);

	bool checkClashToBar(Pos position, bool side);
	void normalizePosX();
	void normalizePosY();

	void draw(sf::RenderWindow& window);

	//them
	//tra ve vi tri
	Pos getPos();
	//bắt sự kiện chạm vật phẩm
	bool checkClashToGift(Pos position);
};



#endif /* Ball_hpp */
