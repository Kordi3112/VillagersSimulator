#pragma once
#include <SFML/Graphics.hpp>
#include "Terrain.h"

class MapCreator
{
public:

	MapCreator();
	~MapCreator();
	//
	void drawScene(sf::RenderWindow& RenderWindow);
	//
	void setEditAreaViewport(sf::Rect<float> Viewport);
	void setEditAreaZoom(float Zoom);
	void setEditAreaCameraPosition(sf::Vector2f CameraPosition);
	//
	sf::Rect<float> getEditAreaViewport() const;
	float getEditAreaZoom() const;
	sf::Vector2f getEditAreaCameraPosition() const;

private:

	//EditArea...
	sf::Rect<float> m_viewport;
	float m_zoom;
	sf::Vector2f m_cameraPosition;
	//==//
	void drawEditArea();
	void drawInterface();
};

