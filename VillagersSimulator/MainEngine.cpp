#include "MainEngine.h"



MainEngine::MainEngine()
{
}


MainEngine::~MainEngine()
{
	
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
		sf::sleep(sf::milliseconds(1000));
		//std::cout << "thread" << std::endl;
	}
	
}

void MainEngine::draw(sf::RenderWindow& window)
{
	if (this->m_gameStage == MainEngine::MAPCREATOR)
	{
	//	this->drawMapCreatorStage();
		return;
	}

	this->drawInterface(window);
	this->drawGameFrame(window);
}

void MainEngine::loadResources()
{
	this->m_resources.load();
}

void MainEngine::drawInterface(sf::RenderWindow& window)
{
}

void MainEngine::drawGameFrame(sf::RenderWindow& window)
{

}

void MainEngine::drawMapCreatorStage(sf::RenderWindow& window)
{
	//drawMapEdit();
	//drawInterface();
}
