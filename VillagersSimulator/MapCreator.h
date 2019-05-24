#pragma once
#include <SFML/Graphics.hpp>
#include "Terrain.h"

//tool used to draw on map
enum BrushShape
{
	CIRCLE_BRUSH,
	SQUARE_BRUSH
};

class Brush
{
public:
	Brush();
	~Brush();
	//
	void setBrushShape(BrushShape shape);
	BrushShape getBrushShape() const;
	//
	//if CIRCLE_BRUSH: size is radius, if SQUARE_BRUSH: size is a side/2
	void setSize(float size);
	float getSize() const;
	//
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition() const;
private:
	BrushShape m_brushShape;
	float m_size;
	//position on screen
	sf::Vector2f m_position;

};

class MapCreator
{
public:

	MapCreator();
	~MapCreator();
	//
	void drawScene(sf::RenderWindow& RenderWindow);
	//
	void Init();
	//
	void setEditAreaViewport(sf::Rect<float> Viewport);
	void setEditAreaZoom(float Zoom);
	void setEditAreaCameraPosition(sf::Vector2f CameraPosition);
	//
	sf::Rect<float> getEditAreaViewport() const;
	float getEditAreaZoom() const;
	sf::Vector2f getEditAreaCameraPosition() const;
	///Terrain generate stuff
	void generateOcean(); //...and init chunks

	///POST RENDERING
	//making the map better looking
	void postRenderOfTerrain();
private:

	//EditArea...
	sf::Rect<float> m_viewport;
	float m_zoom;
	sf::Vector2f m_cameraPosition;
	//
	Terrain* m_terrain;
	//==//
	void drawEditArea();
	void drawInterface();
};

