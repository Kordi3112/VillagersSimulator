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
	hMainEngine->m_pRenderWindow = &hWindow;
	//RESOURCES


	hMainEngine->changeScene(MainEngine::GAMESTAGE::MAPCREATOR);
	hMainEngine->changeScene(MainEngine::GAMESTAGE::SIMULATION);

	//
	//Thread
	sf::Thread thread(&MainEngine::ThreadFunction, hMainEngine); //thread function is inside MainEngine class
	thread.launch();
	//
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
				///READ INPUT
				hMainEngine->readKeyPressedInput(event);
			
			}
		}
		///--------------REFRESH COTROLERS

		///
		int timeDifference = frameTimeClock.getElapsedTime().asMicroseconds();
		frameTimeClock.restart();
		float deltaTime = timeDifference / 1000000.0f;

		hMainEngine->refresh(deltaTime);
		hMainEngine->readInput(deltaTime);

		///---------RENDER
		hWindow.clear(sf::Color::Green);
		//
		hMainEngine->draw(hWindow);
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
	delete hMainEngine;
	//
	return 0;
}