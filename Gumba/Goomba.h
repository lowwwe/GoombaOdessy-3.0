#pragma once

#pragma warning (push)
#pragma warning (disable:4275)
#include <SFML/Graphics.hpp>
#include "Globals.h"


class Goomba
{
public:
	Goomba();
	void draw(sf::RenderWindow& t_window);
	void setup(sf::Vector2f t_location);
	Direrction m_heading = Direrction::Left; // direction of walking
	void setBoundry(float t_value, bool t_isLeft);
	void move();
	void update();
	void checkBoundry();
	void animate();
	float m_frameCounter{ 0.0f }; // frame counter

private:
	sf::Vector2f m_location; // location of Goomba
	sf::Texture tempTexture; // used for sprite constructor
	sf::Sprite m_sprite{ tempTexture }; // sprite
	float m_leftBoundry{ -1.0f}; // left barrier
	float m_rightBoundry{-1.0f}; // right barrier
	int m_frameNo{ 0 }; // current frame
	
	static float s_frameIncrtement; // frame increment


};

#pragma warning (pop) 