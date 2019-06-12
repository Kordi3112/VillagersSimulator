#include <SFML/Graphics.hpp>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include "MainEngine.h"
#include "Random.h"
#include "VillagerPriorities.h"



int main()
{
	
	VillagerPriorities priorities;
	priorities.equalDistribution();

	//priorities.addPoints(VillagerPriorities::Priorities::ID_REVOLTING, -20.f);
	priorities.addPoints(VillagerPriorities::Priorities::ID_EATING, 50.f);
	priorities.addPoints(VillagerPriorities::Priorities::ID_DRINKING, 20.0f);

	PrioritiesChanses priorityChanses;
	priorityChanses.setDefault();
	priorityChanses.raging = 10.0f;
	priorityChanses.drinking = 5;
	priorities.setPriorityChances(priorityChanses);

	std::cout << "----------------------------------" << std::endl;
	for (int x = 0; x < priorities.PRIORITIES_NUMBER; x++)
	{
		std::cout << x << ": " << priorities.getPriorityValueById(x) << std::endl;
	}

	std::cout << "----------------------------------" << std::endl;

	for (int i = 0; i < 200; i++)
	{
		std::cout << "i: " << i << " Priority: " << priorities.drawLotsActivity() << std::endl;
	}
	std::cout << "----------------------------------" << std::endl;

	//_getch();
	//JUNKS

	int FPS = 0;
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
	MainEngine hMainEngine; //handle to MainEngine 

	hMainEngine.setViewPort(sf::Rect<float>(0.1f, 0.1f, 0.8f, 0.5f));
	hMainEngine.loadResources();
	
	hMainEngine.m_pRenderWindow = &hWindow;
	//RESOURCES


	//hMainEngine.changeScene(MainEngine::GAMESTAGE::MAPCREATOR);
	hMainEngine.changeScene(MainEngine::GAMESTAGE::SIMULATION);

	//
	//Thread
	sf::Thread thread(&MainEngine::ThreadFunction, &hMainEngine); //thread function is inside MainEngine class
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
				hMainEngine.readKeyPressedInput(event);
			
			}
		}
		///--------------REFRESH COTROLERS

		///
		int timeDifference = frameTimeClock.getElapsedTime().asMicroseconds();
		frameTimeClock.restart();
		float deltaTime = timeDifference / 1000000.0f;

		hMainEngine.refresh(deltaTime, hWindow);
		hMainEngine.readInput(deltaTime);

		///---------RENDER
		hWindow.clear(sf::Color::Green);
		//
		//hMainEngine.m_mutex.lock();
		hMainEngine.draw(hWindow);
		//hMainEngine.m_mutex.unlock();
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
	//
	return 0;
}