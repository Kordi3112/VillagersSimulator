#include <SFML/Graphics.hpp>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <time.h>
#include <thread>
#include "MainEngine.h"

#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-system-d.lib")



int main()
{

	
	//JUNKS
	sf::Vector2f cameraPos = sf::Vector2f(GetSystemMetrics(SM_CXSCREEN)/2.0f, GetSystemMetrics(SM_CYSCREEN) /2.0f);
	int FPS = 0;
	float g_zoom=1.f;
	sf::Clock minute;
	//
	///----CLOCKS
	sf::Clock frameTimeClock;
	///
	sf::ContextSettings contextSettings;
	//setting antialising to 8
	contextSettings.antialiasingLevel = 8;
	//creating window
	//sf::RenderWindow hWindow(sf::VideoMode(1080, 720, 32), "VillagersSimulator", sf::Style::Default, contextSettings);
	sf::RenderWindow hWindow(sf::VideoMode(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 32), "VillagersSimulator", sf::Style::Fullscreen, contextSettings);

	//MainEngine Init
	MainEngine* hMainEngine = new MainEngine();//handle to MainEngine 

	hMainEngine->setViewPort(sf::Rect<float>(0.1f, 0.1f, 0.8f, 0.5f));
	//JUNK
	TexturePack buttonTexturePack1;
	buttonTexturePack1.loadNewTexture("noneclick", "../data/texturepacks/button2/noneclick.png");
	buttonTexturePack1.loadNewTexture("onIt", "../data/texturepacks/button2/onIt.png");
	buttonTexturePack1.loadNewTexture("click", "../data/texturepacks/button2/click.png");

	std::cout << buttonTexturePack1.getTextureName(0);
	std::cout << buttonTexturePack1.getTextureName(1);
	std::cout << buttonTexturePack1.getTextureName(2);

	
	ve::CircleButton* circleButton = new ve::CircleButton();
	circleButton->setTexture1(buttonTexturePack1.getTexturePtr("noneclick"));
	circleButton->setTexture2(buttonTexturePack1.getTexturePtr(1));
	circleButton->setTexture3(buttonTexturePack1.getTexturePtr(2));

	circleButton->setPosition(sf::Vector2f(300,300));
	circleButton->setRadius(141);
	circleButton->setAdditionalParameters(ve::LOCK_WHEN_CLICKED);

	//circleButton->setColor(sf::Color::Red);
	//circleButton->setPosition(sf::Vector2f(300, 300));
	//circleButton->setRadius(100);
	

	//delete dialog;

	//Thread
	sf::Thread thread(&MainEngine::ThreadFunction, hMainEngine); //thread function is inside MainEngine class
	thread.launch();
	//
	Terrain terrain;
	terrain.generateMap(time(NULL));
	terrain.refreshAllChunksTexture();
	std::cout << (int)sf::Color::Green.b << std::endl;
	//
	minute.restart();
	frameTimeClock.restart();
	//
	while (hWindow.isOpen())
	{
		///------------EVENTS
		sf::Event event;
		while (hWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				hWindow.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)hWindow.close();
				//
				if (event.key.code == sf::Keyboard::W)g_zoom *= 2;
				if (event.key.code == sf::Keyboard::S)g_zoom /= 2;
				

			}
		}
		///--------------REFRESH COTROLERS
		circleButton->checkButtonStatus(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
		//
		int refreshTimeUs = frameTimeClock.getElapsedTime().asMicroseconds();
		frameTimeClock.restart();
		float splitSecond = refreshTimeUs / 1000000.0f;
		//
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))cameraPos.x -= 200 * splitSecond;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))cameraPos.x += 200 * splitSecond;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))cameraPos.y -= 200 * splitSecond;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))cameraPos.y += 200 * splitSecond;

		///
		///---------RENDER
		hWindow.clear();
		//
		hMainEngine->draw(hWindow);
		terrain.renderChunks(hWindow, cameraPos, sf::Rect<float>(0.02f, 0.02f, 0.3f, 0.3f), g_zoom);
		//
		//circleButton->draw(hWindow);
		hWindow.display();
		FPS++;
		//
		if (minute.getElapsedTime().asMilliseconds() >= 1000)
		{
			
			std::cout << FPS << std::endl;
			minute.restart();
			FPS = 0;
		}
	}
	//delete thread
	thread.terminate();
	//clean memory
	delete circleButton;
	terrain.releaseChunks();
	delete hMainEngine;
	//
	return 0;
}