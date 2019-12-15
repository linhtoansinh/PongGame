#include "Gift.h"
Gift::Gift()
{
	srand(time(nullptr));
	this->posX = float(100 + rand() % (_WIDTH_TABLE_GAME_ + 1 - 100));
	this->posY = float(_DIS_FROM_TOP_ + rand() % ((_HEIGH_TABLE_GAME_ / 2) + 1 - _DIS_FROM_TOP_));

	// load file ảnh và cài đặt thông số cho vật phẩm
	if (!this->textureGift.loadFromFile("res/img/gift1.png")) {
		std::cout << "Load file failed" << std::endl;
	}
	this->imgSprGift.setTexture(this->textureGift);
	this->imgSprGift.scale(_size_gift * 1.0 / this->imgSprGift.getTexture()->getSize().x, _size_gift * 1.0 / this->imgSprGift.getTexture()->getSize().y);

	// getter chiều cao chiều rộng
	this->posXend = this->imgSprGift.getTexture()->getSize().x * this->imgSprGift.getScale().x;
	this->posYend = this->imgSprGift.getTexture()->getSize().y * this->imgSprGift.getScale().y;

	// điều chỉnh vị trí
	this->imgSprGift.setPosition(this->posX - this->posXend * 1.0 / 2, this->posY - this->posYend * 1.0 / 2);

}

Gift::Gift(std::string path)
{
	srand(time(nullptr));
	this->posX = float(100 + rand() % (_WIDTH_TABLE_GAME_ + 1 - 100));
	this->posY = float(_DIS_FROM_TOP_ + rand() % ((_HEIGH_TABLE_GAME_ / 2) + 1 - _DIS_FROM_TOP_));

	// load file ảnh và cài đặt thông số cho vật phẩm
	if (!this->textureGift.loadFromFile(path)) {
		std::cout << "Load file failed" << std::endl;
	}
	this->imgSprGift.setTexture(this->textureGift);
	this->imgSprGift.scale(_size_gift * 1.0 / this->imgSprGift.getTexture()->getSize().x, _size_gift * 1.0 / this->imgSprGift.getTexture()->getSize().y);

	// getter chiều cao chiều rộng
	this->posXend = this->imgSprGift.getTexture()->getSize().x * this->imgSprGift.getScale().x;
	this->posYend = this->imgSprGift.getTexture()->getSize().y * this->imgSprGift.getScale().y;

	// điều chỉnh vị trí
	this->imgSprGift.setPosition(this->posX - this->posXend * 1.0 / 2, this->posY - this->posYend * 1.0 / 2);
}

Gift::Gift(float x, float y)
{
	this->posX = x;
	this->posY = y;

	// load file ảnh và cài đặt thông số bóng
	if (!this->textureGift.loadFromFile("res/img/gift1.jpg")) {
		std::cout << "Load file failed" << std::endl;
	}
	this->imgSprGift.setTexture(this->textureGift);
	this->imgSprGift.scale(_size_gift * 1.0 / this->imgSprGift.getTexture()->getSize().x, _size_gift * 1.0 / this->imgSprGift.getTexture()->getSize().y);
	//chiều cao chiều rộng
	this->posXend = this->imgSprGift.getTexture()->getSize().x * this->imgSprGift.getScale().x;
	this->posYend = this->imgSprGift.getTexture()->getSize().y * this->imgSprGift.getScale().y;
	// chỉnh vị trí theo điểm tâm
	this->imgSprGift.setPosition(this->posX - this->posXend * 1.0 / 2, this->posY - this->posYend * 1.0 / 2);
}

Gift::~Gift()
{

}

void Gift::setPosX(float x) {        // đặt vị trí x
	this->posX = x;
}
void Gift::setPosY(float y) {        // đặt vị trí y
	this->posY = y;
}
float Gift::getPosX() {              // lấy vị trí x
	return this->posX;
}
float Gift::getPosY() {              // lấy vị trí y
	return this->posY;
}
float Gift::getPosYend() {              // lấy vị trí y
	return this->posYend;
}
float Gift::getPosXend() {              // lấy vị trí y
	return this->posXend;
}

void Gift::scale(float width, float heigh) {     // thay đổi kích thước bóng kiểu co giãn
	this->imgSprGift.scale(width, heigh);
}

Pos Gift::getPos()
{
	Pos pos;
	pos.x = this->getPosX();
	pos.y = this->getPosY();
	pos.endX = this->getPosXend();
	pos.endY = this->getPosYend();
	return pos;
}

void Gift::draw(sf::RenderWindow& window) {      // vẽ vật phẩm
	window.draw(this->imgSprGift);
}
