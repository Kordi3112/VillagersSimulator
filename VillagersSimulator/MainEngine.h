#pragma once
#include <SFML/Graphics.hpp>
#include "DialogWindow.h"
#include "Village.h"
#include "Terrain.h"
#include "ApiEvents.h"
#include "Resources.h"
#include "MapCreator.h"
#include "DrawObject.h"

struct GameSettings
{
	///For VillagerPriorities
	PrioritiesChanses prioritiesChanses;
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
		CHOOSE_MAP,
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
	void moveCamera(sf::Vector2f vector);
	void setCameraPosition(sf::Vector2f position);
	sf::Vector2f getCameraPosition() const;
	void setZoom(float zoom);
	float getZoom() const;
	void setViewPort(sf::Rect<float> rect);
	sf::Rect<float> getViewPort() const;
	///
	sf::Vector2f getScreenPosOfMapPos(Terrain* terrain, sf::Vector2f mapPosition) const;
	sf::Vector2f getScreenPosOfMapPos(Terrain* terrain, sf::Vector2i mapPosition, sf::Vector2f cameraPosition, sf::RenderWindow& window, sf::FloatRect viewPort, float zoom) const;
	//
	sf::Vector2i getMapCoordFromScreenCoord(sf::Vector2f position, sf::RenderWindow& window);
	///THREAD
	void ThreadFunction();//this function is for second thread
	///DRAW
	void draw(sf::RenderWindow& window);
	///INPUT
	void readInput(float deltaTime);
	void readKeyPressedInput(sf::Event& event);
	///REFRESH
	void refresh(float deltaTime, sf::RenderWindow& window); //in us
	//
	void loadResources();
	Resources* getResourcesPtr();
	///RENDER WINDOW
	sf::RenderWindow* m_pRenderWindow;
	///JUNKS
	int m_FPS_counter = 0;
	sf::Clock m_clock;
	sf::Mutex m_mutex;
	///
private:

	sf::Vector2f m_cameraPosition;
	float m_zoom = 1.0f;
	sf::Rect<float> m_viewPortRect; // it determines position of the world frame on the whole screen
	//
	//
	void spawnVillagers();
	///MAIN_MENU INIT
	void mainMenuInit(sf::RenderWindow& window);//
	///CHOOSE_MAP INIT
	void chooseMapInit(sf::RenderWindow& window);//
	//DRAW
	void drawMainMenu(sf::RenderWindow& window);//
	void drawChooseMap(sf::RenderWindow& window);//
	///SIMULATION INIT
	void simulationInit(sf::RenderWindow& window);
	bool m_firstSpawnerSet = true;
	///SIMULATION FRAME
	void drawInterface(sf::RenderWindow& window);
	void drawGameFrame(sf::RenderWindow& window);
	void drawObjects(sf::RenderWindow& window);
	//==//
	void drawMapCreatorStage(sf::RenderWindow& window);
	//
	//==//
	void drawLoadingScreenStage(sf::RenderWindow& window, sf::Rect<float> viewPort);
	
	///FIELDS
	Terrain* m_hTerrain;
	std::vector<Village> m_villageContainer;
	//
	MapCreator m_mapCreator;
	//
	ve::ButtonMenu m_villagerInfo;
	//
	ve::DialogWindowControler m_mainMenuDialogControler;
	//
	ve::DialogWindowControler m_chooseDialogControler;
	//
	ApiEvents m_apiEvents;
	GAMESTAGE m_gameStage;
	GameSettings m_gameSettings;
	GameStates m_gameStates;
	//
	//
	Resources m_resources;
};

