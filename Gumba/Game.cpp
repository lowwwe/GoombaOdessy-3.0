/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include "Globals.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ sf::Vector2u{800U, 600U}, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	
	
	setupSprite(); // load texture
	setupGoombas();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but method needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	while (const std::optional newEvent = m_window.pollEvent())
	{
		if (newEvent->is<sf::Event::Closed>()) // close window message 
		{
			m_exitGame = true;
		}
		if (newEvent->is<sf::Event::KeyPressed>()) //user pressed a key
		{
			processKeys(newEvent);
		}

	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed* newKeypress = t_event->getIf<sf::Event::KeyPressed>();
	if (sf::Keyboard::Key::Escape == newKeypress->code)
	{
		m_exitGame = true;
	}
}
/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	for (int i = 0; i < NO_OF_GOOMBAS; i++)
	{
		m_goombas[i].update();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_background);
	for (int i = 0; i < NO_OF_GOOMBAS; i++)
	{
		m_goombas[i].draw(m_window);
	}
	m_window.draw(m_logoSprite);
	m_window.display();
}



/// <summary>
/// load the texture and setup the sprite the game
/// 
void Game::setupSprite()
{
	if (!textureAtlas.loadFromFile("ASSETS\\IMAGES\\atlas.png"))
	{
		std::cout << "problem with atlas";
	}
	m_background.setTexture(textureAtlas);
	m_background.setTextureRect(sf::IntRect{ sf::Vector2i{0,507},sf::Vector2i{1280,800} });
	m_background.setScale(sf::Vector2f{ 800.0f / 1280.0f, 600.0f / 800.0f });
	
	m_logoSprite.setTexture(textureAtlas);
	m_logoSprite.setTextureRect(sf::IntRect{ sf::Vector2i{520,0},sf::Vector2i{684,507 } });
	m_logoSprite.setPosition(sf::Vector2f{ 0.0f, 0.0f });
	m_logoSprite.setScale(sf::Vector2f{ 0.5f, 0.5f });
}

void Game::setupGoombas()
{
	m_goombas[0].setup(sf::Vector2f{ 15.0f,445.f });
	m_goombas[0].m_heading = Direrction::Left;
	m_goombas[0].setBoundry(36.0f, true);
	m_goombas[0].setBoundry(105.0f, false);

	m_goombas[1].setup(sf::Vector2f{ 400.0f, 365.0f });
	m_goombas[1].m_heading = Direrction::Left;
	m_goombas[1].setBoundry(400.0f, true);
	m_goombas[1].setBoundry(485.0f, false);

	m_goombas[2].setup(sf::Vector2f{ 26.0f, 520.0f });
	m_goombas[2].m_heading = Direrction::Left;
	m_goombas[2].setBoundry(25.0f, true);
	m_goombas[2].setBoundry(770.0f, false);

}
