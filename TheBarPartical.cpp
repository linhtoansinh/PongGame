#include "TheBarPartical.hpp"

// the bar class
TheBar::TheBar(){
    
}
TheBar::TheBar(bool side){  // true = side A - left     false = side B - right          constructor: set theo bên
    if (side) {             // side == true => thanh bar bên trái được tạo
        this->textureBar.loadFromFile("res/img/barRed.png");
        this->posX =  (_WIDTH_SCREEN - _WIDTH_TABLE_GAME_) / 2 + 4 * _THICK_LINE_; // set vị trí bên trái
    }
    else {                  // side == false => thanh bar bên phải được tạo
        this->textureBar.loadFromFile("res/img/barBlue.png");
        this->posX =  (_WIDTH_SCREEN - _WIDTH_TABLE_GAME_) / 2 + _WIDTH_TABLE_GAME_ - _THICK_LINE_ / 2; // set vị trí bên trái
    }
    this->imgSpr.setTexture(this->textureBar);      // set sprite theo texture
    this->imgSpr.rotate(90.f);                      // xoay góc 90 độ theo chiều kim đồng hồ
    
    this->heigBar = this->imgSpr.getTexture()->getSize().y;     // lấy kích thước theo chiều dài Oy
    this->longBar = this->imgSpr.getTexture()->getSize().x;     // lấy kích thước theo chiều rộng Ox
    
    this->imgSpr.scale( _WIDTH_BAR_ * 1.0 / this->longBar, _HEIGH_BAR_ * 1.0 / this->heigBar);      // scale để có kích thước chính xác là (_WIDTH_BAR_, _HEIGH_BAR_)
    
    // get lại kích thước mới
    this->heigBar = this->heigBar * this->imgSpr.getScale().y;
    this->longBar = this->longBar * this->imgSpr.getScale().x;    
    
    // set vị trí Oy
    this->posY = _DIS_FROM_TOP_ + (_HEIGH_TABLE_GAME_ - this->longBar) / 2 - 2 * _THICK_LINE_;
    
    // set tốc độ di chuyển theo chiều Oy
    this->velocityY = _VELOCITY_Y_BAR_;
    this->acceleration = _ACCELERATION_BAR_;
    
    // set default information
    this->namePlayer = "Player";
    this->health = 3;
    this->scores = 0;

}

TheBar::TheBar(bool side, float posY, int score, int health, std::string name)  // true = side A - left     false = side B - right          constructor: set theo thông tin ban đầu
{
	if (side) {             // side == true => thanh bar bên trái được tạo
		this->textureBar.loadFromFile("res/img/barRed.png");
		this->posX = (_WIDTH_SCREEN - _WIDTH_TABLE_GAME_) / 2 + 4 * _THICK_LINE_; // set vị trí bên trái
	}
	else {                  // side == false => thanh bar bên phải được tạo
		this->textureBar.loadFromFile("res/img/barBlue.png");
		this->posX = (_WIDTH_SCREEN - _WIDTH_TABLE_GAME_) / 2 + _WIDTH_TABLE_GAME_ - _THICK_LINE_ / 2; // set vị trí bên trái
	}
	this->imgSpr.setTexture(this->textureBar);      // set sprite theo texture
	this->imgSpr.rotate(90.f);                      // xoay góc 90 độ theo chiều kim đồng hồ

	this->heigBar = this->imgSpr.getTexture()->getSize().y;     // lấy kích thước theo chiều dài Oy
	this->longBar = this->imgSpr.getTexture()->getSize().x;     // lấy kích thước theo chiều rộng Ox

	this->imgSpr.scale(_WIDTH_BAR_ * 1.0 / this->longBar, _HEIGH_BAR_ * 1.0 / this->heigBar);      // scale để có kích thước chính xác là (_WIDTH_BAR_, _HEIGH_BAR_)
    
    // get lại kích thước mới
	this->heigBar = this->heigBar * this->imgSpr.getScale().y;
	this->longBar = this->longBar * this->imgSpr.getScale().x;
	
    // set vị trí Oy
	this->posY = posY;

    // set tốc độ di chuyển theo chiều Oy
	this->velocityY = _VELOCITY_Y_BAR_;
	this->acceleration = _ACCELERATION_BAR_;

    // set default information
	this->namePlayer = name;
	this->health = health;
	this->scores = score;
}

TheBar::~TheBar(){
    
}

void TheBar::setNamePlayer(std::string name){               // đặt tên người chơi
    this->namePlayer = name;
}
int TheBar::getHealth(){                                    // lấy về số mạng còn lại
    return this->health;
}
int TheBar::getScores(){                                    // lấy về số điểm đang có
    return this->scores;
}
std::string TheBar::getNameplayer(){                        // lấy về tên người chơi
    return this->namePlayer;
}

void TheBar::setScores(int score){                          // cài đặt số điểm hiện có
    this->scores = score;
}

void TheBar::setPosY(float y){                              // cài vị trí thanh hiện đang ở đâu theo Y
    this->posY = y;
}
float TheBar::getPosX(){                                    // lấy vị trí thanh hiện đang ở đâu theo X
    return this->posX;
}
float TheBar::getPosY(){                                    // lấy vị trí thanh hiện đang ở đâu theo Y
    return this->posY;
}
float TheBar::getWidth(){                                   // lấy chiều dài thanh
    return this->longBar;
}
float TheBar::getHeigh(){                                   // lấy chiều cao thanh
    return this->heigBar;
}

float TheBar::getLongBar()                                  // lấy chiều dài thanh
{
	return this->longBar;
}

void TheBar::scale(float width, float heigh){               // cài đặt độ phóng của thanh
    this->imgSpr.scale(heigh * 1.0 / this->heigBar, width * 1.0 / this->longBar);
}
void TheBar::moveBar(sf::RenderWindow &window, bool Up, bool Down){     // di chuyển thanh -> bool lên , bool xuống
    // lưu vị trí cũ
    float pastY = this->posY;
    
    // nếu thanh di chuyển lên
    if (Up) {
        // đặt vị trí Y
        if (this->posY - this->velocityY < _DIS_FROM_TOP_) {
            this->posY = _DIS_FROM_TOP_;
        }
        else {
            this->posY -= this->velocityY;
        }
        
    }
    // nếu thanh đi xuống
    if (Down) {
        // đặt vị trí Y
        if ((this->posY + this->longBar + this->velocityY) > (_HEIGH_TABLE_GAME_ + _DIS_FROM_TOP_)) {
            this->posY = _HEIGH_TABLE_GAME_  + _DIS_FROM_TOP_ - this->longBar;
        }
        else {
            this->posY += this->velocityY;
        }
    }
    
    // dịch chuyển thanh
    this->imgSpr.move(0, this->posY - pastY);
    window.draw(this->imgSpr);
    
}
void TheBar::draw(sf::RenderWindow &window){            // thể hiện trên màn hình
    this->imgSpr.setPosition(this->posX, this->posY);
    window.draw(this->imgSpr);
    
}
void TheBar::loseHealth(){                              // giảm máu
    this->health--;
}
void TheBar::haveScore(){                               // tăng điểm
    this->scores++;
}
