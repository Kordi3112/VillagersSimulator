#pragma once
#include <SFML/Graphics.hpp>
#include "IzoMap.h"
#include "Terrain.h"
//Buttons etc.
#include "DialogWindow.h"
#include "Resources.h"

//tool used to draw on map
enum BrushShape
{
	CIRCLE_BRUSH,
	SQUARE_BRUSH
};

//
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
	//
	void setHardness(float level);
	void draw();
	//
	void reset();
private:
	BrushShape m_brushShape;
	float m_size;
	//this parameter is responsible for density drawed land
	float m_hardness = 1.0f; //is between 0 and 1
	//position on screen
	sf::Vector2f m_position;
	//Block which is stick to the pen
	Block m_blockPicked;

};

class MapCreator
{
public:

	MapCreator();
	~MapCreator();
	//
	void drawScene(sf::RenderWindow& RenderWindow);
	//
	void init(sf::RenderWindow& RenderWindow);
	//
	void setResourcesPtr(Resources* resources);
	//
	void setEditAreaViewport(sf::Rect<float> Viewport);
	void setEditAreaZoom(float Zoom);
	void setEditAreaCameraPosition(sf::Vector2f CameraPosition);
	//
	sf::Rect<float> getEditAreaViewport() const;
	float getEditAreaZoom() const;
	sf::Vector2f getEditAreaCameraPosition() const;
	//
	void setMousePosition(sf::Vector2i position);
	sf::Vector2i getMousePosition() const;
	//
	sf::Vector2f getMousePosRelativeToMap();
	//
	void refreshBrushPosRelativeToMap(sf::RenderWindow& window);
	void refresh(unsigned deltaTime);
	void refreshUI(sf::Vector2f clickerPosition);
	///BRUSH
	void setBrushSize(float size);
	///Terrain generate stuff
	void generateOcean(); //...and init chunks

	bool m_mouseOnMap;
	///POST RENDERING
	//making the map better looking
	void postTerrainRender();
private:

	//==//
	//
	void drawBackground(sf::RenderWindow& window);
	//
	void drawEditArea(sf::RenderWindow& window);
	///UI
	void drawUI(sf::RenderWindow& window);
	//
	ve::ButtonMenu m_buttonMenu1;
	///TEXTURES
	Resources* m_pResources;
	///
	sf::Vector2i m_mousePos;
	sf::Vector2f m_mousePosRelativeToMap;
	
	//EditArea...
	sf::Rect<float> m_viewport;
	float m_zoom;
	sf::Vector2f m_cameraPosition;
	//
	Terrain* m_terrain;
	//BRUSH
	Brush m_brush;
	
};

