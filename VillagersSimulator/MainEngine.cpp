#include "MainEngine.h"



MainEngine::MainEngine()
{
}


MainEngine::~MainEngine()
{
	m_mainMenuDialogControler.releaseAllElements();
	m_chooseDialogControler.releaseAllElements();
}

MainEngine::GAMESTAGE MainEngine::getCurrentGameStage() const
{
	return m_gameStage;
}

void MainEngine::changeScene(MainEngine::GAMESTAGE stage)
{

	if (stage == MainEngine::GAMESTAGE::MAPCREATOR)
	{
		if (getCurrentGameStage() == MainEngine::GAMESTAGE::MAPCREATOR)
			return;

		m_gameStage = MainEngine::GAMESTAGE::MAPCREATOR;

		m_mapCreator.setResourcesPtr(&m_resources);
		m_mapCreator.init(*m_pRenderWindow);
		m_mapCreator.setEditAreaCameraPosition(sf::Vector2f(MAP_X_SIZE / 2.0f, MAP_Y_SIZE / 2.0f));
		m_mapCreator.setEditAreaViewport(sf::Rect<float>(0.07, 0.07, 0.86, 0.86));
		m_mapCreator.setEditAreaZoom(1.0f);
		
	}
	else if (stage == MainEngine::GAMESTAGE::MAIN_MENU)
	{
		if (getCurrentGameStage() == MainEngine::GAMESTAGE::MAIN_MENU)
			return;

		m_gameStage = MainEngine::GAMESTAGE::MAIN_MENU;
		mainMenuInit(*m_pRenderWindow);

	}
	else if (stage == MainEngine::GAMESTAGE::SIMULATION)
	{
		if (getCurrentGameStage() == MainEngine::GAMESTAGE::SIMULATION)
			return;

		m_gameStage = MainEngine::GAMESTAGE::SIMULATION;

		MainEngine::simulationInit(*MainEngine::m_pRenderWindow);
	}
	else if (stage == MainEngine::GAMESTAGE::CHOOSE_MAP)
	{
		if (getCurrentGameStage() == MainEngine::GAMESTAGE::CHOOSE_MAP)
			return;

		m_gameStage = MainEngine::GAMESTAGE::CHOOSE_MAP;
		chooseMapInit(*m_pRenderWindow);
	}
}

void MainEngine::moveCamera(sf::Vector2f vector)
{
	m_cameraPosition += vector;
}

void MainEngine::setCameraPosition(sf::Vector2f position)
{
	this->m_cameraPosition = position;
}

sf::Vector2f MainEngine::getCameraPosition() const
{
	return this->m_cameraPosition;
}

void MainEngine::setZoom(float zoom)
{
	if (zoom <= 0)return;
	this->m_zoom = zoom;
}

float MainEngine::getZoom() const
{
	return this->m_zoom;
}

void MainEngine::setViewPort(sf::Rect<float> rect)
{
	this->m_viewPortRect = rect;
}

sf::Rect<float> MainEngine::getViewPort() const
{
	return this->m_viewPortRect;
}

sf::Vector2f MainEngine::getScreenPosOfMapPos(Terrain* terrain, sf::Vector2f mapPosition) const
{
	return sf::Vector2f();
}

sf::Vector2f MainEngine::getScreenPosOfMapPos(Terrain* terrain, sf::Vector2i mapPosition, sf::Vector2f cameraPosition, sf::RenderWindow& window, sf::FloatRect viewPort, float zoom) const
{
	sf::Vector2f frameCenter = sf::Vector2f(viewPort.width * window.getSize().x / 2.0f, viewPort.height * window.getSize().y / 2.0f);

	return ( sf::Vector2f(mapPosition.x, mapPosition.y) - cameraPosition) * zoom + frameCenter + sf::Vector2f(viewPort.left * window.getSize().x, viewPort.top * window.getSize().y);
}

sf::Vector2i MainEngine::getMapCoordFromScreenCoord(sf::Vector2f position, sf::RenderWindow& window)
{
	sf::Vector2f viewportCenter = sf::Vector2f((getViewPort().left + getViewPort().width / 2.0f) * window.getSize().x, (getViewPort().top + getViewPort().height / 2.0f) * window.getSize().y);

	return sf::Vector2i(round((position.x - viewportCenter.x) / m_zoom + m_cameraPosition.x), round((position.y - viewportCenter.y) / m_zoom + m_cameraPosition.y));
}

void MainEngine::ThreadFunction()
{
	m_clock.restart();
	for (;;)
	{
		/**
		if (m_clock.getElapsedTime().asMilliseconds() >= 1000)
		{
			std::cout << "FPS_COUNTER: "<< m_FPS_counter << std::endl;
			m_clock.restart();
			m_FPS_counter = 0;
		}
		m_mutex.lock();
		refresh(0, *m_pRenderWindow);
		m_mutex.unlock();

		m_FPS_counter++;

		sf::sleep(sf::milliseconds(4));
		*/
	}
	
}

void MainEngine::draw(sf::RenderWindow& window)
{
	if (getCurrentGameStage() == MainEngine::MAPCREATOR)
	{
		drawMapCreatorStage(window);
	}
	else if (getCurrentGameStage() == MainEngine::SIMULATION)
	{
		drawGameFrame(window);
		drawInterface(window);
	}

}

void MainEngine::readInput(float deltaTime)
{
	if (getCurrentGameStage() == MainEngine::GAMESTAGE::MAPCREATOR)
	{

		float cameraMovingSpeed = 300.0f / getZoom();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))m_mapCreator.moveEditAreaCamera(sf::Vector2f(0, -cameraMovingSpeed*deltaTime));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))m_mapCreator.moveEditAreaCamera(sf::Vector2f(0, cameraMovingSpeed*deltaTime));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))m_mapCreator.moveEditAreaCamera(sf::Vector2f(-cameraMovingSpeed*deltaTime, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))m_mapCreator.moveEditAreaCamera(sf::Vector2f(cameraMovingSpeed*deltaTime, 0));
	}
	else if (getCurrentGameStage() == MainEngine::GAMESTAGE::SIMULATION)
	{
		

		float cameraMovingSpeed = 300.0f / getZoom();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))moveCamera(sf::Vector2f(0, -cameraMovingSpeed * deltaTime));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))moveCamera(sf::Vector2f(0, cameraMovingSpeed * deltaTime));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))moveCamera(sf::Vector2f(-cameraMovingSpeed * deltaTime, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))moveCamera(sf::Vector2f(cameraMovingSpeed * deltaTime, 0));

	}
}

void MainEngine::readKeyPressedInput(sf::Event& event)
{
	if (getCurrentGameStage() == MainEngine::GAMESTAGE::MAPCREATOR)
	{
		if (event.key.code == sf::Keyboard::W)
		{
			m_mapCreator.setEditAreaZoom(m_mapCreator.getEditAreaZoom() * 2.0f);
		}

		if (event.key.code == sf::Keyboard::S)
		{
			m_mapCreator.setEditAreaZoom(m_mapCreator.getEditAreaZoom() * 0.5f);
		}

		if (event.key.code == sf::Keyboard::Space)
		{
			m_mapCreator.saveMap();
		}
		if (event.key.code == sf::Keyboard::L)
		{
			m_mapCreator.loadMap();
		}

		if (event.key.code == sf::Keyboard::C)
		{
			m_mapCreator.copyTerrain();
		}

		if (event.key.code == sf::Keyboard::R)
		{
			m_mapCreator.swapTerrainPointers();
		}

		if (event.key.code == sf::Keyboard::P)
		{
			m_mapCreator.postTerrainRender();
		}
	}
	else if (getCurrentGameStage() == MainEngine::GAMESTAGE::SIMULATION)
	{
		if (event.key.code == sf::Keyboard::W)
		{
			setZoom(getZoom() * 2.0f);
		}

		if (event.key.code == sf::Keyboard::S)
		{
			setZoom(getZoom() * 0.5f);
		}
	}
}

void MainEngine::refresh(float deltaTime, sf::RenderWindow& window)
{
	if (m_gameStage == MainEngine::GAMESTAGE::MAPCREATOR)
	{
		m_mapCreator.refreshBrushPosRelativeToMap(*m_pRenderWindow);
		m_mapCreator.refresh(deltaTime, window);
		m_mapCreator.refreshUI(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
	}
	if (m_gameStage == MainEngine::GAMESTAGE::SIMULATION)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (m_firstSpawnerSet)
			{
				m_villageContainer[0].setSpawnerPosition(getMapCoordFromScreenCoord(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y), window));
				m_villageContainer[0].setSpawnerRadius(10);
				m_firstSpawnerSet = true;
			}
		}
	}
}

void MainEngine::loadResources()
{
	this->m_resources.load();
}

Resources* MainEngine::getResourcesPtr()
{
	return &m_resources;
}

void MainEngine::mainMenuInit(sf::RenderWindow& window)
{
	/*
	//Start
	ve::RectangleButton* Start = new ve::RectangleButton();
	m_mainMenuDialogControler.addElement("Start", Start);
	Start->setSize(sf::Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.10f));
	Start->setPosition(sf::Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.4f));
	Start->setTextures(m_resources.mainMenu.getTexturePtr("start1"), m_resources.mainMenu.getTexturePtr("start2"), m_resources.mainMenu.getTexturePtr("start3"));

	//Authors
	ve::RectangleButton* Authors = new ve::RectangleButton();
	m_mainMenuDialogControler.addElement("Authors", Authors);
	Authors->setSize(sf::Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.10f));
	Authors->setPosition(sf::Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.55f));
	Authors->setTextures(m_resources.mainMenu.getTexturePtr("authors1"), m_resources.mainMenu.getTexturePtr("authors2"), m_resources.mainMenu.getTexturePtr("authors3"));

	//Exit
	ve::RectangleButton* Exit = new ve::RectangleButton();
	m_mainMenuDialogControler.addElement("Exit", Exit);
	Exit->setSize(sf::Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.10f));
	Exit->setPosition(sf::Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.70f));
	Exit->setTextures(m_resources.mainMenu.getTexturePtr("exit1"), m_resources.mainMenu.getTexturePtr("exit2"), m_resources.mainMenu.getTexturePtr("exit3"));
	*/		
}

void MainEngine::chooseMapInit(sf::RenderWindow& window)
{
}

void MainEngine::simulationInit(sf::RenderWindow& window)
{
	if (m_hTerrain != nullptr)
		m_hTerrain->clear();

	m_hTerrain = new Terrain();
	m_hTerrain->generateBlueBackground();

	setViewPort(sf::FloatRect(0, 0, 1, 1));
	setZoom(2.0f);
	setCameraPosition(sf::Vector2f(MAP_X_SIZE / 2.f, MAP_Y_SIZE / 2.f));
	//
	m_hTerrain->loadFromFile("../data/maptest.map");
	//
	m_hTerrain->refreshTreeCoords();
	//
	///Village
	//first village
	m_villageContainer.push_back(Village());
	m_firstSpawnerSet = true;
	//m_hTerrain->setBlock()
}



void MainEngine::drawInterface(sf::RenderWindow& window)
{


}

void MainEngine::drawGameFrame(sf::RenderWindow& window)
{
	///MAP
	m_hTerrain->renderChunks(window, getCameraPosition(), getViewPort(), getZoom());
	///OBJECTS
	//rendering objects from the most behind to the most forward

	DrawObject drawObjects;
	int treeDrawObj = drawObjects.createObject("tree", m_resources.objects_environment.getTexturePtr("tree"), sf::Vector2f(getZoom(), getZoom()), sf::Vector2f(getZoom() / 2.0f, getZoom()));
	int spawnerDrawObj = drawObjects.createObject("spawner", m_resources.objects_buildings.getTexturePtr("spawner"), sf::Vector2f(getZoom(), getZoom()), sf::Vector2f(getZoom() / 2.0f, getZoom()));
	///trees

	for (int i = 0; i < m_hTerrain->getTreesNumber(); i++)
	{
		drawObjects.addLocation(treeDrawObj, getScreenPosOfMapPos(m_hTerrain, m_hTerrain->getTreeCoord(i).getMain(), getCameraPosition(), window, getViewPort(), getZoom()));
	}
	drawObjects.addLocation(spawnerDrawObj, getScreenPosOfMapPos(m_hTerrain, m_villageContainer[0].getSpawnerPosition(), getCameraPosition(), window, getViewPort(), getZoom()));

	drawObjects.draw(window);

}
void MainEngine::drawMapCreatorStage(sf::RenderWindow& window)
{
	m_mapCreator.drawScene(window);
}
