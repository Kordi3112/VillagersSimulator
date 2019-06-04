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
	///JUNK
	MapCreator mapCreator;
	mapCreator.init();
	mapCreator.setEditAreaCameraPosition(cameraPos);
	mapCreator.setEditAreaViewport(sf::Rect<float>(0.1, 0.1, 0.8, 0.8));
	mapCreator.setEditAreaZoom(4.0f);
	
	IzoMap izoMap;
	izoMap.create(800, 800);
	izoMap.fillValue(0);

	std::vector<sf::Vector2i> fields;
	fields.push_back(sf::Vector2i(100, 100));
	fields.push_back(sf::Vector2i(300, 300));
	fields.push_back(sf::Vector2i(200, 500));
	
	std::vector<float> radius;
	radius.push_back(100);
	radius.push_back(150);
	radius.push_back(100);

	std::vector<float> shift;
	shift.push_back(0.7f);
	shift.push_back(0.5f);
	shift.push_back(0.3f);

	//IzoMap::Tools::createHoles(&izoMap, fields, radius, shift);
	IzoMap::Tools::gradientRegion(&izoMap, sf::IntRect(100, 100, 600, 600), sf::Vector2i(700, 700), sf::Vector2i(100, 100) , 0, 0.7);
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
		hMainEngine->draw(hWindow);
		//terrain.renderChunks(hWindow, cameraPos, sf::Rect<float>(0.02f, 0.02f, 0.3f, 0.3f), g_zoom);
		mapCreator.drawScene(hWindow);
		//izoMap.draw(hWindow);
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