#ifndef TheBarPartical_hpp
#define TheBarPartical_hpp

#include <iostream>
#include <SFML/Graphics.hpp>
#include "BackGround.hpp"
#include "Ball.hpp"

class TheBar {
protected:
    float posX;
    float posY;
    sf::Texture textureBar;
    sf::Sprite imgSpr;
    
    float longBar;
    float heigBar;
    
    float velocityY;
    float acceleration;
    
    std::string namePlayer;
    int health;
    int scores;
    
public:
    TheBar();
    TheBar(bool side);
	TheBar(bool, float, int, int, std::string);
    virtual ~TheBar();
    
    void setNamePlayer(std::string name);
    int getHealth();
    int getScores();
    std::string getNameplayer();
    
    void setScores(int score);
	void setPosY(float y);
    float getPosX();
    float getPosY();
    float getWidth();
    float getHeigh();
	float getLongBar();
    
    void scale(float width, float heigh);
    void moveBar(sf::RenderWindow &window, bool Up, bool Down);
    void draw(sf::RenderWindow &window);
    
    void loseHealth();
    void haveScore();
};



#endif /* TheBarPartical_hpp */
