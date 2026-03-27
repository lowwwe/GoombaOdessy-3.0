#include "Goomba.h"


float Goomba::s_frameIncrtement{0.35f};

Goomba::Goomba()
{
	m_frameNo = std::rand() % 20;
	m_frameCounter = static_cast<float>( m_frameNo);
}

void Goomba::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_sprite);
}

void Goomba::setup(sf::Vector2f t_location)
{
	m_sprite.setTexture(textureAtlas);
	m_sprite.setTextureRect(sf::IntRect{ sf::Vector2i{ 0,0},sf::Vector2i{52,54 } });
	m_location = t_location;
	m_sprite.setPosition(m_location);
	m_sprite.setOrigin(sf::Vector2f{ 26.0f, 0.0f });

}

void Goomba::setBoundry(float t_value, bool t_isLeft)
{
	if (t_isLeft && (t_value < m_rightBoundry || m_rightBoundry == -1.0f))
	{
		m_leftBoundry = t_value;
	}
	if (!t_isLeft && t_value > m_leftBoundry)
	{
		m_rightBoundry = t_value;
	}
}

void Goomba::move()
{
	if (m_heading == Direrction::Right)
	{
		m_location.x += 1.2f;

	}
	if (m_heading == Direrction::Left)
	{
		m_location.x -= 1.2f;
	}

}

void Goomba::update()
{
	animate();
	move();
	checkBoundry();
	m_sprite.setPosition(m_location);
}

void Goomba::checkBoundry()
{
	if (m_heading == Direrction::Right && m_location.x > m_rightBoundry)
	{
		m_heading = Direrction::Left;
		m_sprite.setScale(sf::Vector2f{ 1.0f, 1.0f });
	}
	if (m_heading == Direrction::Left && m_location.x < m_leftBoundry)
	{
		m_heading = Direrction::Right;
		m_sprite.setScale(sf::Vector2f{ -1.0f, 1.0f });
	}
}

void Goomba::animate()
{
	int frame;
	int row;
	int column;
	const int FRAME_WIDTH = 52;
	const int FRAME_HEIGHT = 54;
	m_frameCounter += s_frameIncrtement;
	frame = static_cast<int>(m_frameCounter) % 20;
	if (m_frameNo != frame)
	{
		m_frameNo = frame;
		row = frame / 10;
		column = frame % 10;
		m_sprite.setTextureRect(sf::IntRect{ sf::Vector2i{column * FRAME_WIDTH, row * FRAME_HEIGHT},sf::Vector2i{ FRAME_WIDTH, FRAME_HEIGHT} });
	}
}
