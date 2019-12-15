#ifndef Gift_h
#define Gift_h
#include "Ball.hpp"


#define _size_gift 50

class Gift
{
private:
	float posX;
	float posY;
	float posXend;	//ở đây hiểu là chiều rộng
	float posYend;	//chiều dài
	sf::Texture textureGift;
	sf::Sprite imgSprGift;
	
public:
	Gift();
	Gift(std::string);
	Gift(float, float); //cài đặt vị trí ban đầu và thông số 
	virtual ~Gift();
	void setPosX(float x);
	void setPosY(float y);
	float getPosX();
	float getPosY();
	float getPosYend();
	float getPosXend();
	void draw(sf::RenderWindow& window); //vẽ vật phẩm
	void scale(float width, float heigh); //điều chỉnh kích thước vật phẩm
	
	//them
	//tra ve vi tri vat pham
	Pos getPos();
};
#endif
