#include "Ball.hpp"

// the pong class
ThePong::ThePong() {
    // khởi động vị trí quả bóng tạo vị trí chính giữa màn hình chơi
	this->posX = (_WIDTH_SCREEN - _WIDTH_TABLE_GAME_) / 2 + _WIDTH_TABLE_GAME_ / 2;
	this->posY = _DIS_FROM_TOP_ + _HEIGH_TABLE_GAME_ / 2;

    // load file ảnh và cài đặt thông số cho quả bóng
	if (!this->textureBall.loadFromFile("res/img/pongball.png")) {
		std::cout << "Load file failed" << std::endl;
	}
	this->imgSpr.setTexture(this->textureBall);
	this->imgSpr.scale(_SIZE_PONG_ * 1.0 / this->imgSpr.getTexture()->getSize().x, _SIZE_PONG_ * 1.0 / this->imgSpr.getTexture()->getSize().y);

    // cài đặt tốc độ và gia tốc
	this->velocityX = _VELOCITY_X_;
	this->velocityY = _VELOCITY_Y_;
	this->acceleration = _ACCELERATION_;

    // getter vị trí cuối cùng quả bóng
	this->posXend = this->imgSpr.getTexture()->getSize().x * this->imgSpr.getScale().x;
	this->posYend = this->imgSpr.getTexture()->getSize().y * this->imgSpr.getScale().y;

    // điều chỉnh vị trí
	this->imgSpr.setPosition(this->posX - this->posXend * 1.0 / 2, this->posY - this->posYend * 1.0 / 2);

}
ThePong::ThePong(float x, float y, float veX, float veY) {
    // set vị trí theo điểm đầu
	this->posX = x;
	this->posY = y;

    // load file ảnh và cài đặt thông số bóng
	if (!this->textureBall.loadFromFile("res/img/pongball.png")) {
		std::cout << "Load file failed" << std::endl;
	}
	this->imgSpr.setTexture(this->textureBall);
	this->imgSpr.scale(_SIZE_PONG_ * 1.0 / this->imgSpr.getTexture()->getSize().x, _SIZE_PONG_ * 1.0 / this->imgSpr.getTexture()->getSize().y);

    // cài đặt tốc độ và gia tốc
	this->velocityX = veX;
	this->velocityY = veY;
	this->acceleration = _ACCELERATION_;

    // lấy vị trí cuối cùng
	this->posXend = this->imgSpr.getTexture()->getSize().x * this->imgSpr.getScale().x;
	this->posYend = this->imgSpr.getTexture()->getSize().y * this->imgSpr.getScale().y;

    // chỉnh vị trí theo điểm tâm
	this->imgSpr.setPosition(this->posX - this->posXend * 1.0 / 2, this->posY - this->posYend * 1.0 / 2);

}
ThePong::~ThePong() {

}

void ThePong::setPosX(float x) {        // đặt vị trí x
	this->posX = x;
}
void ThePong::setPosY(float y) {        // đặt vị trí y
	this->posY = y;
}
float ThePong::getPosX() {              // lấy vị trí x
	return this->posX;
}
float ThePong::getPosY() {              // lấy vị trí y
	return this->posY;
}
float ThePong::getVelocityX()           // lấy tốc độ theo x
{
	return velocityX;
}

float ThePong::getVelocityY()           // lấy tốc độ theo y
{
	return velocityY;
}

void ThePong::updateVelocityX() {       // cập nhật tốc độ của x
//    this->velocityX /= (myMath::squarerootOf(myMath::squareOf(this->velocityX) + myMath::squareOf(this->velocityY)));
	this->velocityX *= this->acceleration;
	if (myMath::absFloat(this->velocityX) > _MAX_VELOCITY_) {
        if (this->velocityX < 0) {
            this->velocityX = -_MAX_VELOCITY_;
        }
        else this->velocityX = _MAX_VELOCITY_;
	}
}
void ThePong::updateVelocityY() {       // cập nhật tốc độ của x
	this->velocityY *= this->acceleration;
	if (myMath::absFloat(this->velocityY) > _MAX_VELOCITY_) {
        if (this->velocityY < 0) {
            this->velocityY = -_MAX_VELOCITY_;
        }
        else this->velocityY = _MAX_VELOCITY_;
	}
}
void ThePong::resetPong(short toward) { // đặt lại vị trí ban đầu cho bóng, và đặt hướng đi ngẫu nhiên hay về một hướng
    // đưa bóng về giữa sân
	this->posX = (_WIDTH_SCREEN - _WIDTH_TABLE_GAME_) / 2 + _WIDTH_TABLE_GAME_ / 2;
	this->posY = _DIS_FROM_TOP_ + _HEIGH_TABLE_GAME_ / 2;

    // đặt ngẫu nhiên tốc độ bóng
	srand(time(nullptr));
	this->velocityY = _VELOCITY_Y_ * ((rand() % 100) * 1.0 / 100 + 1) * _HEIGH_TABLE_GAME_ / (2 * _WIDTH_TABLE_GAME_);
	this->velocityX = _VELOCITY_X_ * (((rand() % 100) * 1.0 / 50 - 1) >= 0 ? 1 : -1) * (_VELOCITY_X_ / sqrt(sqr(_VELOCITY_X_) + sqr(this->velocityY)));
    
    // điều hướng bóng
    if (toward != 0) {
        this->velocityX = toward * myMath::absFloat(this->velocityX);
    }

    // reset gia tốc
	this->acceleration = _ACCELERATION_;
}

void ThePong::scale(float width, float heigh) {     // thay đổi kích thước bóng kiểu co giãn
	this->imgSpr.scale(width, heigh);
}
short ThePong::moveBall(sf::RenderWindow& window, Pos positionLeft, Pos positionRight, Pos posGift) {    // hàm di chuyển bóngc
	if (checkClashToGift(posGift))
	{
		return -3;
	
	}
	if ((this->posX <= (_WIDTH_SCREEN - _WIDTH_TABLE_GAME_) / 2) || (this->posX + this->posXend > ((_WIDTH_SCREEN - _WIDTH_TABLE_GAME_) / 2 + _WIDTH_TABLE_GAME_ - _THICK_LINE_))) {
		//                 |
		//                _|_
		// tru hp tai day \|/
		//                 !
		this->velocityY *= 1;
		this->velocityX *= -1;
		this->acceleration = 0;
		this->velocityY *= 0;
		this->velocityX *= 0;

		if (this->posX <= (_WIDTH_SCREEN - _WIDTH_TABLE_GAME_) / 2) { // crash left side
			posX = (_WIDTH_SCREEN - _WIDTH_TABLE_GAME_) / 2;
			return -1;
		}
		else {              // crash right side
			posX = ((_WIDTH_SCREEN - _WIDTH_TABLE_GAME_) / 2 + _WIDTH_TABLE_GAME_ - _THICK_LINE_);
			return 1;
		}

            //                 ^
            //                /|\
            //               /-|-\
            //                 |
	}
    // thay đổi vị trí bóng
	this->posX += this->velocityX;
	this->posY += this->velocityY;

    // điều chỉnh nếu bóng vượt biên
	this->normalizePosX();
	this->normalizePosY();

    float rateDisFromMid = 1;
    bool normalMoveOfX = true;
    
    // kiểm tra chạm thanh
    bool checkCrashToBarLeft = this->checkClashToBar(positionLeft, true);
    bool checkCrashToBarRight = this->checkClashToBar(positionRight, false);

	if (checkCrashToBarLeft || checkCrashToBarRight) {
		float minDis = 0;
		if (checkCrashToBarLeft) {
            
            // trường hợp chạm biên trên của thanh trái
            if ((this->posX + myMath::absFloat(this->velocityX) <= positionLeft.x + positionLeft.endX) && (this->posY + this->posYend + myMath::absFloat(this->velocityY) >= positionLeft.y) && (this->posY + this->posYend + myMath::absFloat(this->velocityY) <= positionLeft.y + positionLeft.endY)) {
                this->velocityY *= -1;
                normalMoveOfX = false;
            }
            // trường hợp chạm biên dưới của thanh trái
            else if ((this->posX + myMath::absFloat(this->velocityX) <= positionLeft.x + positionLeft.endX) && (this->posY - myMath::absFloat(this->velocityY) >= positionLeft.y) && (this->posY - myMath::absFloat(this->velocityY) <= positionLeft.y + positionLeft.endY)) {
                this->velocityY *= -1;
                normalMoveOfX = false;
            }
			// >>>>>>>>>>>>>>>>>>>>>>>>>
			else {
                // lấy khoảng cách nhỏ nhất từ bóng đến điểm chính giữa khi chạm thanh
				minDis = (myMath::absFloat(this->posY - positionLeft.y + (positionLeft.endY) / 2) < myMath::absFloat(this->posY + this->posYend - positionLeft.y + (positionLeft.endY) / 2)) ? myMath::absFloat(this->posY - positionLeft.y + (positionLeft.endY) / 2) : myMath::absFloat(this->posY + this->posYend - positionLeft.y + (positionLeft.endY) / 2);
                // tính tỷ lệ thay đổi hướng trên trục tung
                rateDisFromMid = ((minDis / (positionLeft.endY) / 2));
			}

		}
		else {
            // trường hợp chạm biên trên của thanh phải
            if ((this->posX + this->posXend - myMath::absFloat(this->velocityX) >= positionRight.x) && (this->posY + this->posYend + myMath::absFloat(this->velocityY) >= positionRight.y) && (this->posY + this->posXend + myMath::absFloat(this->velocityY) <= positionRight.y + positionRight.endY)) {
                this->velocityY *= -1;
                normalMoveOfX = false;
            }
            // trường hợp chạm biên dưới của thanh phải
            else if ((this->posX + this->posXend - myMath::absFloat(this->velocityX) >= positionRight.x) && (this->posY - myMath::absFloat(this->velocityY) >= positionRight.y) && (this->posY - myMath::absFloat(this->velocityY) <= positionRight.y + positionRight.endY)) {
                this->velocityY *= -1;
                normalMoveOfX = false;
            }
			// >>>>>>>>>>>>>>>>>>>>>>>>>
			else {
                // lấy khoảng cách nhỏ nhất từ bóng đến điểm chính giữa khi chạm thanh
                minDis = (myMath::absFloat(this->posY - positionRight.y + (positionRight.endY) / 2) < myMath::absFloat(this->posY + this->posYend - positionRight.y + (positionRight.endY) / 2)) ? myMath::absFloat(this->posY - positionRight.y + (positionRight.endY) / 2) : myMath::absFloat(this->posY + this->posYend - positionRight.y + (positionRight.endY) / 2);

                // tính tỷ lệ thay đổi hướng trên trục tung
                rateDisFromMid = ((minDis / (positionRight.endY) / 2));
			}
            

		}
        
        // cập nhật vận tốc trên trục tung nếu có thay đổi
        if (rateDisFromMid != 1) {
            if (myMath::absFloat(rateDisFromMid) > _MAX_CHANGE_VELOC_) {
                if (rateDisFromMid < 0) {
                    rateDisFromMid = -_MAX_CHANGE_VELOC_;
                }
                else rateDisFromMid = _MAX_CHANGE_VELOC_;
                this->velocityY *= (rateDisFromMid);
            }

        }
        if (normalMoveOfX) {
            this->velocityX *= -1;
        }
        else{
            std::cout << "Error" << std::endl;	//whats this
        }
		        
        // cập nhật vận tốc mới vì đã chạm thanh
        this->updateVelocityY();
        this->updateVelocityX();
		
		//
        
	}
    // nếu chạm biên trên và dưới sẽ điều ngược lại trục tung
	if ((this->posY <= _DIS_FROM_TOP_ + _THICK_LINE_) || (this->posY + this->posYend >= (_DIS_FROM_TOP_ + _HEIGH_TABLE_GAME_ - _THICK_LINE_))) {
		this->velocityY *= -1;
	}


	this->imgSpr.setPosition(this->posX, this->posY);

    if (checkCrashToBarLeft) {
        return -2;
    }
    else if (checkCrashToBarRight){
        return 2;
    }
	return 0;  // did not crash

}

bool ThePong::checkClashToBar(Pos position, bool side) {        // bắt sự kiện va vào thanh trượt
	if (side) {
		// trường hợp góc trên trái của bóng chạm thanh trái
		if ((this->posX <= position.x + position.endX) && (this->posY >= position.y) && (this->posY <= position.y + position.endY)) {
			return true;
		}
		// trường hợp góc dưới trái của bóng chạm thanh trái
		else if ((this->posX <= position.x + position.endX) && (this->posY + this->posYend >= position.y) && (this->posY + this->posYend <= position.y + position.endY)) {
			return true;
		}
	}
	else {
		// trường hợp góc trên phải của bóng chạm thanh phải
		if ((this->posX + this->posXend >= position.x) && (this->posY >= position.y) && (this->posY <= position.y + position.endY)) {
			return true;

		}
		// trường hợp góc dưới phải của bóng chạm thanh phải
		else if ((this->posX + this->posXend >= position.x) && (this->posY + this->posYend >= position.y) && (this->posY + this->posXend <= position.y + position.endY)) {
			return true;
		}
	}
	return false;
}

void ThePong::normalizePosX() {         // điều chỉnh bóng không vượt biên trên Ox
	if (this->posX < (_WIDTH_SCREEN - _WIDTH_TABLE_GAME_) / 2) {
		this->posX = (_WIDTH_SCREEN - _WIDTH_TABLE_GAME_) / 2;
	}
	if (this->posX > (_WIDTH_SCREEN - _WIDTH_TABLE_GAME_) / 2 + _WIDTH_TABLE_GAME_) {
		this->posX = (_WIDTH_SCREEN - _WIDTH_TABLE_GAME_) / 2 + _WIDTH_TABLE_GAME_;
	}
}
void ThePong::normalizePosY() {         // điều chỉnh bóng không vượt biên trên Oy
	if (this->posY < _DIS_FROM_TOP_) {
		this->posY = _DIS_FROM_TOP_;
	}
	if (this->posY > _DIS_FROM_TOP_ + _HEIGH_TABLE_GAME_) {
		this->posY = _DIS_FROM_TOP_ + _HEIGH_TABLE_GAME_;
	}
}

void ThePong::draw(sf::RenderWindow& window) {      // vẽ bóng
	window.draw(this->imgSpr);
}

Pos ThePong::getPos()
{
	Pos pos;
	pos.x = posX;
	pos.y = posY;
	pos.endX = posXend;
	pos.endY = posYend;
	return pos;
}

bool ThePong::checkClashToGift(Pos posGift)	//position truyen vao la vi tri vat pham
{
	//phải trên trái bóng chạm bên phải vật phẩm
	if ((this->posX == posGift.x + posGift.endX) && (this->posY <= posGift.y + posGift.endY) && (this->posY >= posGift.y)) {
		return true;
	}
	
	// góc trên phải bóng chạm 
	else if ((this->posX + this->posXend == posGift.x) && (this->posY <= posGift.y + posGift.endY)&&(this->posY >= posGift.y)) {
		return true;

	}
	
	//cạnh trên bóng chạm cạnh dưới vật phẩm
	else if ((this->posX + this->posXend >= posGift.x) && (this->posX + this->posXend <= posGift.x + posGift.endX) && (this->posY == posGift.y + posGift.endY)) {
		return true;
	}

	//cạnh dưới bóng chạm cạnh trên vật phẩm
	else if ((this->posX + this->posXend >= posGift.x) && (this->posX + this->posXend <= posGift.x + posGift.endX) && (this->posY + this->posYend == posGift.y)) {
		return true;
	}

	/*//trường hợp bóng ở bên trái vật phẩm
	if (this->posX + this->posXend >= posGift.x)
	{
		if (this->posY >= posGift.y && this->posY <= posGift.y + posGift.endY)
		{
			return true;
		}
		else if (this->posY + this->posYend >= posGift.y && this->posY + this->posYend <= posGift.y + posGift.endY)
		{
			return true;
		}
	}

	//trường hợp bóng ở bên phải vật phẩm
	if (this->posX == posGift.x + posGift.endX)
	{
		if (this->posY >= posGift.y && this->posY <= posGift.y + posGift.endY)
		{
			return true;
		}
		else if (this->posY + this->posYend >= posGift.y && this->posY + this->posYend <= posGift.y + posGift.endY)
		{
			return true;
		}
	}

	//trường hợp bóng ở phía trên vật phẩm
	if (this->posY + this->posYend == posGift.y)
	{
		if (this->posX >= posGift.x && this->posX <= posGift.x + posGift.endX)
		{
			return true;
		}
		else if (this->posX + this->posXend >= posGift.x && this->posX + this->posXend <= posGift.x + posGift.endX)
		{
			return true;
		}
	}

	//trường hợp bóng ở phía dưới vật phẩm
	if (this->posY == posGift.y +posGift.endY)
	{
		if (this->posX >= posGift.x && this->posX <= posGift.x + posGift.endX)
		{
			return true;
		}
		else if (this->posX + this->posXend >= posGift.x && this->posX + this->posXend <= posGift.x + posGift.endX)
		{
			return true;
		}
	}*/

	return false;
}
