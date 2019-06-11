#include "MainEngine.h"



MainEngine::MainEngine()
{
}


MainEngine::~MainEngine()
{
	
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
	}
	else if (stage == MainEngine::GAMESTAGE::SIMULATION)
	{
		if (getCurrentGameStage() == MainEngine::GAMESTAGE::SIMULATION)
			return;

		m_gameStage = MainEngine::GAMESTAGE::SIMULATION;

		if(m_hTerrain != nullptr)
			m_hTerrain->clear();

		m_hTerrain = new Terrain();
		m_hTerrain->generateBlueBackground();
		MainEngine::setViewPort(sf::FloatRect(0,0,1,1));
		MainEngine::setCameraPosition(sf::Vector2f(MAP_X_SIZE / 2.0f, MAP_Y_SIZE / 2.0f));
		MainEngine::setZoom(1.0f);
	}
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

void MainEngine::ThreadFunction()
{
	for (;;)
	{
		sf::sleep(sf::seconds(1));
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

		float cameraMovingSpeed = 300.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))m_mapCreator.moveEditAreaCamera(sf::Vector2f(0, -cameraMovingSpeed*deltaTime));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))m_mapCreator.moveEditAreaCamera(sf::Vector2f(0, cameraMovingSpeed*deltaTime));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))m_mapCreator.moveEditAreaCamera(sf::Vector2f(-cameraMovingSpeed*deltaTime, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))m_mapCreator.moveEditAreaCamera(sf::Vector2f(cameraMovingSpeed*deltaTime, 0));
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
	}

}

void MainEngine::refresh(float deltaTime)
{
	if (m_gameStage == MainEngine::GAMESTAGE::MAPCREATOR)
	{
		m_mapCreator.refreshBrushPosRelativeToMap(*m_pRenderWindow);
		m_mapCreator.refresh(deltaTime);
		m_mapCreator.refreshUI(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
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

void MainEngine::simulationInit()
{
	setViewPort(sf::FloatRect(0, 0, 1, 1));
	setZoom(2.0f);
	setCameraPosition(sf::Vector2f(MAP_X_SIZE / 2.f, MAP_Y_SIZE / 2.f));
}

void MainEngine::drawInterface(sf::RenderWindow& window)
{
}

void MainEngine::drawGameFrame(sf::RenderWindow& window)
{
	std::vector<sf::Vector2f> treePos;

	///MAP
	m_hTerrain->renderChunks(window, getCameraPosition(), getViewPort(), getZoom());
	///OBJECTS
	//rendering objects from the most behind to the most forward

	sf::RenderTexture bufor;
	bufor.create(getViewPort().width, getViewPort().height);
	bufor.clear();

	const sf::Vector2f frameCenter = sf::Vector2f(bufor.getSize().x / 2.0f, bufor.getSize().y / 2.0f);
	//trees
	sf::RectangleShape treeSprite;

	//load texture
	treeSprite.setTexture(m_resources.objects_environment.getTexturePtr("tree"));
	treeSprite.setSize(sf::Vector2f(getZoom(), getZoom()));
	//set origin
	treeSprite.setOrigin(sf::Vector2f(treeSprite.getSize().x / 2.0f, treeSprite.getSize().y));//origin is at the bot side at the middle

	/*
	for (int i = 0; i < m_hTerrain->getTreesNumber(); i++)
	{
		treeSprite.setPosition()
	}
	*/
	for (int i = 0; i < treePos.size(); i++)
	{
		//treeSprite.setPosition()
	}
}
void MainEngine::drawMapCreatorStage(sf::RenderWindow& window)
{
	m_mapCreator.drawScene(window);
}
