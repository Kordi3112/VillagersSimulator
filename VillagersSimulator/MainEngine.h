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
		MAPCREATOR,
		SIMULATION, //game
	};

	//
	MainEngine();
	~MainEngine();
	//
	void stop();
	void resume();
	void setRunTimeSpeed(float speed);
	void start();
	///INIT

	///CHANGING SCENE
	MainEngine::GAMESTAGE getCurrentGameStage() const;
	void changeScene(MainEngine::GAMESTAGE stage);
	//
	void setCameraPosition(sf::Vector2f position);
	sf::Vector2f getCameraPosition() const;
	void setZoom(float zoom);
	float getZoom() const;
	void setViewPort(sf::Rect<float> rect);
	sf::Rect<float> getViewPort() const;
	//
	void ThreadFunction();//this function is for second thread
	///DRAW
	void draw(sf::RenderWindow& window);
	///INPUT
	void readInput(float deltaTime);
	void readKeyPressedInput(sf::Event& event);
	///REFRESH
	void refresh(float deltaTime); //in us
	//
	void loadResources();
	Resources* getResourcesPtr();
	//
	sf::RenderWindow* m_pRenderWindow;
private:

	sf::Vector2f m_cameraPosition;
	float m_zoom = 1.0f;
	sf::Rect<float> m_viewPortRect; // it determine position of the world frame on the whole screen
	//
	void spawnVillagers();
	///SIMULATION INIT
	void simulationInit();
	///SIMULATION FRAME
	void drawInterface(sf::RenderWindow& window);
	void drawGameFrame(sf::RenderWindow& window);
	//==//
	void drawMapCreatorStage(sf::RenderWindow& window);
	//
	//==//
	void drawLoadingScreenStage(sf::RenderWindow& window, sf::Rect<float> viewPort);

	///FIELDS
	Terrain* m_hTerrain;
	std::vector<Village*> m_villageContainer;
	//
	MapCreator m_mapCreator;
	//
	ApiEvents m_apiEvents;
	GAMESTAGE m_gameStage;
	GameSettings m_gameSettings;
	GameStates m_gameStates;
	//
	//
	Resources m_resources;
};

