#include <SFML/Graphics.hpp>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <time.h>
#include <thread>
#include "MainEngine.h"
#include "Random.h"




int main()
{
	
	//JUNKS

	sf::Vector2f cameraPos = sf::Vector2f(500,500);
	int FPS = 0;
	float g_zoom=2.f;
	sf::Clock minute;
	//
	///----CLOCKS
	sf::Clock frameTimeClock;
	///
	sf::ContextSettings contextSettings;
	//setting antialising to 8
	contextSettings.antialiasingLevel = 8;
	//creating window
	sf::RenderWindow hWindow(sf::VideoMode(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 32), "VillagersSimulator", sf::Style::Fullscreen, contextSettings);

	///MainEngine Init
	MainEngine* hMainEngine = new MainEngine();//handle to MainEngine 

	hMainEngine->setViewPort(sf::Rect<float>(0.1f, 0.1f, 0.8f, 0.5f));
	hMainEngine->loadResources();
	//RESOURCES

	///JUNK
	TexturePack texturePack;
	texturePack.loadNewTexture("1", "../data/texturepacks/button1/noneclick.png");
	texturePack.loadNewTexture("2", "../data/texturepacks/button1/onIt.png");
	texturePack.loadNewTexture("3", "../data/texturepacks/button1/click.png");
	
	TexturePack menuBackground;
	menuBackground.loadNewTexture("1", "../data/texturepacks/buttonMenu/buttonMenu1.png");

	
	
	hMainEngine->m_mapCreator;
	hMainEngine->m_mapCreator.setResourcesPtr(hMainEngine->getResourcesPtr());
	hMainEngine->m_mapCreator.init(hWindow);

	hMainEngine->m_mapCreator.setEditAreaCameraPosition(cameraPos);
	hMainEngine->m_mapCreator.setEditAreaViewport(sf::Rect<float>(0.1, 0.1, 0.8, 0.8));
	hMainEngine->m_mapCreator.setEditAreaZoom(g_zoom);
	


	hMainEngine->m_pRenderWindow = &hWindow;
	//


	//IzoMap::Tools::createHoles(&izoMap, fields, radius, shift);
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
		hMainEngine->m_mapCreator.setEditAreaCameraPosition(cameraPos);
		hMainEngine->m_mapCreator.refreshUI(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));

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
		hWindow.clear(sf::Color::Green);

		//
		hMainEngine->m_mapCreator.setBrushSize(5);
		hMainEngine->m_mapCreator.setEditAreaZoom(g_zoom);
		//hMainEngine->draw(hWindow);
		hMainEngine->m_mapCreator.refreshBrushPosRelativeToMap(hWindow);
		hMainEngine->m_mapCreator.refresh(0);

		hMainEngine->m_mapCreator.drawScene(hWindow);
		//
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
	terrain.releaseChunks();
	delete hMainEngine;
	//
	return 0;
}