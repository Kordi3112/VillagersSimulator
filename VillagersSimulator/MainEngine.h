#pragma once
#include <SFML/Graphics.hpp>
#include "DialogWindow.h"
#include "Village.h"
#include "Terrain.h"
#include "ApiEvents.h"
#include "Resources.h"
#include "MapCreator.h"


struct GameSettings
{
	int seed;//its seed for world generator
	int clevernessLevel = 10; //this level determine an desire of villagers to create something
	int vitalityLevel = 10; //Its main ratio of villager's resistance to damage
	int fertilitylevel = 10;//frequency of childbirths

};

struct GameStates
{

};

//class which is responsible for main simulator exists f.e time service. Its also container for all objects
class MainEngine
{
public:
	//
	enum GAMESTAGE {
		LOADING_SCREEN,
		MAIN_MENU,
		CHOOSESETMAP,
		MAPCREATOR
	};
	
	//

	//
	MainEngine();
	~MainEngine();
	//
	void stop();
	void resume();
	void setRunTimeSpeed(float speed);
	void start();
	//
	void setCameraPosition(sf::Vector2f position);
	sf::Vector2f getCameraPosition() const;
	void setZoom(float zoom);
	float getZoom() const;
	void setViewPort(sf::Rect<float> rect);
	sf::Rect<float> getViewPort() const;
	//
	void ThreadFunction();//this function is for second thread
	//
	void draw(sf::RenderWindow& window);
	//
	void loadResources();
private:

	sf::Vector2f m_cameraPosition;
	float m_zoom = 1.0f;
	sf::Rect<float> m_viewPortRect; // it determine position of the world frame on the whole screen
	//
	void generateMap();
	void spawnVillagers();
	//
	void drawInterface(sf::RenderWindow& window);
	void drawGameFrame(sf::RenderWindow& window);
	//==//
	void drawMapCreatorStage(sf::RenderWindow& window);
	//
	void drawMapCreatorEditArea(sf::RenderWindow& window, sf::Vector2f cameraPosition, sf::Rect<float> viewPort, float zoom);//for map editor
	void drawMapCreatorInterface();
	//==//
	void drawLoadingScreenStage(sf::RenderWindow& window, sf::Rect<float> viewPort);

	///FIELDS
	Terrain* m_hTerain;
	std::vector<Village*> m_villageContainer;
	//
	ApiEvents m_apiEvents;
	GAMESTAGE m_gameStage;
	GameSettings m_gameSettings;
	GameStates m_gameStates;
	//
	ve::DialogWindowControler m_dialogWindowControler;//class to distribute buttons at current scene;
	//
	Resources m_resources;
};

