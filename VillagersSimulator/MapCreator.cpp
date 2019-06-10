#include "MapCreator.h"



MapCreator::MapCreator()
{
}


MapCreator::~MapCreator()
{
	//delete terrain
	delete m_terrain;
	//ButtonMenu
	m_buttonMenu1.releaseAllComponents();
}

void MapCreator::drawScene(sf::RenderWindow& window)
{
	//
	drawBackground(window);
	//
	drawEditArea(window);
	//drawUI
	drawUI(window);
}

void MapCreator::init(sf::RenderWindow& window)
{
	//create terrain
	m_terrain = new Terrain();
	//default piece of terrain
	generateOcean();

	//create map bitmaps
	m_terrain->refreshAllChunksTexture();

	///INIT UI
	//INit Button
	m_buttonMenu1.initButton();
	m_buttonMenu1.setButtonSize(sf::Vector2f(window.getSize().y * 0.6f * 0.1f, window.getSize().y * 0.6f));
	m_buttonMenu1.setButtonPosition(sf::Vector2f(window.getSize().x - window.getSize().y * 0.6f * 0.1f, window.getSize().y / 2.0f));
	m_buttonMenu1.setButtonTextures(m_pResources->mapCreator_Buttons.getTexturePtr("rightPanelInit"), m_pResources->mapCreator_Buttons.getTexturePtr("rightPanelInit"), m_pResources->mapCreator_Buttons.getTexturePtr("rightPanelInit"));
	//Background
	m_buttonMenu1.setSize(sf::Vector2f(0.2f * window.getSize().x, m_buttonMenu1.getButtonSize().y * 1.5f));
	m_buttonMenu1.setBackgroundTexture(m_pResources->mapCreator_Backgrounds.getTexturePtr("rightPanel"));
	m_buttonMenu1.setPosition(sf::Vector2f(m_buttonMenu1.getButtonPosition().x - 3.5f*m_buttonMenu1.getButtonSize().x, m_buttonMenu1.getButtonPosition().y));
	//Choose Brush Buttons
	ve::RectangleButton* brushType1 = new ve::RectangleButton();
	brushType1->setTextures(m_pResources->mapCreator_Buttons.getTexturePtr("circleBrush_noClicked"), m_pResources->mapCreator_Buttons.getTexturePtr("circleBrush_onIt"), m_pResources->mapCreator_Buttons.getTexturePtr("circleBrush_clicked"));
	brushType1->setSize(sf::Vector2f(m_buttonMenu1.getSize().x * 0.1f, m_buttonMenu1.getSize().x * 0.1f));
	brushType1->setPosition(sf::Vector2f(m_buttonMenu1.getPosition().x - m_buttonMenu1.getSize().x / 4.0f, m_buttonMenu1.getPosition().y - m_buttonMenu1.getSize().y * 0.45f));
	brushType1->setAdditionalParameters(ve::LOCK_WHEN_CLICKED);

	ve::RectangleButton* brushType2 = new ve::RectangleButton();
	*brushType2 = *brushType1;
	brushType2->setTextures(m_pResources->mapCreator_Buttons.getTexturePtr("rectangleBrush"));
	brushType2->setPosition(sf::Vector2f(m_buttonMenu1.getPosition().x + m_buttonMenu1.getSize().x / 4.0f, m_buttonMenu1.getPosition().y - m_buttonMenu1.getSize().y * 0.45f));

	m_buttonMenu1.addComponent(brushType1);
	m_buttonMenu1.addComponent(brushType2);
	//Sliders
	ve::Slider* sizeSlider = new ve::Slider();
	sizeSlider->setSliderColor(sf::Color::White);
	sizeSlider->setSliderPointerColor(sf::Color::Yellow);
	sizeSlider->setSize(sf::Vector2f(m_buttonMenu1.getSize().x * 0.7f, m_buttonMenu1.getSize().y*0.03f));
	sizeSlider->setPosition(sf::Vector2f(m_buttonMenu1.getPosition().x, m_buttonMenu1.getPosition().y - m_buttonMenu1.getSize().y * 0.35f));
	sizeSlider->setValue(0.5f);

	ve::Slider* hardenessSlider = new ve::Slider();
	*hardenessSlider = *sizeSlider; //copy
	sizeSlider->setPosition(sf::Vector2f(m_buttonMenu1.getPosition().x, m_buttonMenu1.getPosition().y - m_buttonMenu1.getSize().y * 0.25f));
	sizeSlider->setValue(1.0f);

	m_buttonMenu1.addComponent(sizeSlider);
	m_buttonMenu1.addComponent(hardenessSlider);

	///=TERRAIN BUTTONS
	/////////
	ve::ButtonsPanel* buttonPanelTerrain = new ve::ButtonsPanel();
	////////
	//seawater
	ve::RectangleButton* terrain_seawater = new ve::RectangleButton();
	terrain_seawater->setTextures(m_pResources->mapCreator_Buttons.getTexturePtr("seawater_noClicked"),
								  m_pResources->mapCreator_Buttons.getTexturePtr("seawater_onIt"),
								  m_pResources->mapCreator_Buttons.getTexturePtr("seawater_clicked"));
	terrain_seawater->setSize(sf::Vector2f(m_buttonMenu1.getSize().x * 0.15f, m_buttonMenu1.getSize().x * 0.15f));
	terrain_seawater->setPosition(sf::Vector2f(m_buttonMenu1.getPosition().x - m_buttonMenu1.getSize().x/4.0f, m_buttonMenu1.getPosition().y - m_buttonMenu1.getSize().x * 0.3f));
	terrain_seawater->setAdditionalParameters(ve::LOCK_WHEN_CLICKED);

	buttonPanelTerrain->addButton("seawater", terrain_seawater);
	//water
	ve::RectangleButton* terrain_water = new ve::RectangleButton();
	*terrain_water = *terrain_seawater; //copy
	terrain_water->setTextures(m_pResources->mapCreator_Buttons.getTexturePtr("water_noClicked"),
							      m_pResources->mapCreator_Buttons.getTexturePtr("water_onIt"),
							      m_pResources->mapCreator_Buttons.getTexturePtr("water_clicked"));

	terrain_seawater->setPosition(sf::Vector2f(m_buttonMenu1.getPosition().x , m_buttonMenu1.getPosition().y - m_buttonMenu1.getSize().x * 0.3f));

	buttonPanelTerrain->addButton("water", terrain_water);
	//grass
	ve::RectangleButton* terrain_grass = new ve::RectangleButton();
	*terrain_grass = *terrain_seawater; //copy
	terrain_grass->setTextures(m_pResources->mapCreator_Buttons.getTexturePtr("grass_noClicked"),
							   m_pResources->mapCreator_Buttons.getTexturePtr("grass_onIt"),
							   m_pResources->mapCreator_Buttons.getTexturePtr("grass_clicked"));

	terrain_grass->setPosition(sf::Vector2f(m_buttonMenu1.getPosition().x + m_buttonMenu1.getSize().x / 4.0f, m_buttonMenu1.getPosition().y - m_buttonMenu1.getSize().x * 0.3f));
	
	buttonPanelTerrain->addButton("grass", terrain_grass);
	//sand
	ve::RectangleButton* terrain_sand = new ve::RectangleButton();
	*terrain_sand = *terrain_seawater; //copy
	terrain_sand->setTextures(m_pResources->mapCreator_Buttons.getTexturePtr("sand_noClicked"),
							  m_pResources->mapCreator_Buttons.getTexturePtr("sand_onIt"),
							  m_pResources->mapCreator_Buttons.getTexturePtr("sand_clicked"));

	terrain_sand->setPosition(sf::Vector2f(m_buttonMenu1.getPosition().x - m_buttonMenu1.getSize().x / 8.0f, m_buttonMenu1.getPosition().y - m_buttonMenu1.getSize().x * 0.05f));

	buttonPanelTerrain->addButton("sand", terrain_sand);

	//rock1
	ve::RectangleButton* terrain_rock1 = new ve::RectangleButton();
	*terrain_rock1 = *terrain_seawater; //copy
	terrain_rock1->setTextures(m_pResources->mapCreator_Buttons.getTexturePtr("rock1_noClicked"),
							   m_pResources->mapCreator_Buttons.getTexturePtr("rock1_onIt"),
							   m_pResources->mapCreator_Buttons.getTexturePtr("rock1_clicked"));

	terrain_rock1->setPosition(sf::Vector2f(m_buttonMenu1.getPosition().x + m_buttonMenu1.getSize().x / 8.0f, m_buttonMenu1.getPosition().y - m_buttonMenu1.getSize().x * 0.05f));

	buttonPanelTerrain->addButton("rock1", terrain_rock1);
	//rock2
	ve::RectangleButton* terrain_rock2 = new ve::RectangleButton();
	*terrain_rock2 = *terrain_seawater; //copy
	terrain_rock2->setTextures(m_pResources->mapCreator_Buttons.getTexturePtr("rock2_noClicked"),
							   m_pResources->mapCreator_Buttons.getTexturePtr("rock2_onIt"),
							   m_pResources->mapCreator_Buttons.getTexturePtr("rock2_clicked"));

	terrain_rock2->setPosition(sf::Vector2f(m_buttonMenu1.getPosition().x - m_buttonMenu1.getSize().x / 4.0f, m_buttonMenu1.getPosition().y + m_buttonMenu1.getSize().x * 0.2f));

	buttonPanelTerrain->addButton("rock2", terrain_rock2);
	//snow
	ve::RectangleButton* terrain_snow = new ve::RectangleButton();
	*terrain_snow = *terrain_seawater; //copy
	terrain_snow->setTextures(m_pResources->mapCreator_Buttons.getTexturePtr("snow_noClicked"),
							  m_pResources->mapCreator_Buttons.getTexturePtr("snow_onIt"),
							  m_pResources->mapCreator_Buttons.getTexturePtr("snow_clicked"));

	terrain_snow->setPosition(sf::Vector2f(m_buttonMenu1.getPosition().x, m_buttonMenu1.getPosition().y + m_buttonMenu1.getSize().x * 0.2f));

	buttonPanelTerrain->addButton("snow", terrain_snow);
	//tree
	ve::RectangleButton* terrain_tree = new ve::RectangleButton();
	*terrain_tree = *terrain_seawater; //copy
	terrain_tree->setTextures(m_pResources->mapCreator_Buttons.getTexturePtr("tree_noClicked"),
							  m_pResources->mapCreator_Buttons.getTexturePtr("tree_onIt"),
		                      m_pResources->mapCreator_Buttons.getTexturePtr("tree_clicked"));

	terrain_tree->setPosition(sf::Vector2f(m_buttonMenu1.getPosition().x + m_buttonMenu1.getSize().x / 4.0f, m_buttonMenu1.getPosition().y + m_buttonMenu1.getSize().x * 0.2f));

	buttonPanelTerrain->addButton("tree", terrain_tree);
	//ADD COMPONENT
	m_buttonMenu1.addComponent(buttonPanelTerrain);
}

void MapCreator::setResourcesPtr(Resources* resources)
{
	m_pResources = resources;
}

void MapCreator::setEditAreaViewport(sf::Rect<float> Viewport)
{
	m_viewport = Viewport;
}

void MapCreator::setEditAreaZoom(float Zoom)
{
	m_zoom = Zoom;
}

void MapCreator::setEditAreaCameraPosition(sf::Vector2f CameraPosition)
{
	m_cameraPosition = CameraPosition;
}

sf::Rect<float> MapCreator::getEditAreaViewport() const
{
	return m_viewport;
}

float MapCreator::getEditAreaZoom() const
{
	return m_zoom;
}

sf::Vector2f MapCreator::getEditAreaCameraPosition() const
{
	return m_cameraPosition;
}

void MapCreator::setMousePosition(sf::Vector2i position)
{
	m_mousePos = position;
}

sf::Vector2i MapCreator::getMousePosition() const
{
	return m_mousePos;
}

sf::Vector2f MapCreator::getMousePosRelativeToMap()
{
	return m_mousePosRelativeToMap;
}

void MapCreator::refreshBrushPosRelativeToMap(sf::RenderWindow& window)
{
	if (!m_viewport.contains(sf::Vector2f(sf::Mouse::getPosition().x / window.getSize().x, sf::Mouse::getPosition().y / window.getSize().y)))
	{
		//in
		m_mouseOnMap = true;
		
		sf::Vector2f viewportCenter = sf::Vector2f((m_viewport.left + m_viewport.width / 2.0f) * window.getSize().x, (m_viewport.top + m_viewport.height / 2.0f) * window.getSize().y);
		m_mousePosRelativeToMap.x = (sf::Mouse::getPosition().x - viewportCenter.x) / m_zoom + m_cameraPosition.x;
		m_mousePosRelativeToMap.y = (sf::Mouse::getPosition().y - viewportCenter.y) / m_zoom + m_cameraPosition.y;
	
	}
	else
	{
		//out
		m_mouseOnMap = false;
	}

}

void MapCreator::refresh(unsigned deltaTime)
{
	m_brush.setBrushShape(BrushShape::CIRCLE_BRUSH);
	
	int leftChunkId = m_terrain->getChunkId(getMousePosRelativeToMap() - sf::Vector2f(m_brush.getSize(), m_brush.getSize()));
	int rightChunkId = m_terrain->getChunkId(getMousePosRelativeToMap() - sf::Vector2f(-m_brush.getSize(), m_brush.getSize()));
	int botChunkId = m_terrain->getChunkId(getMousePosRelativeToMap() + sf::Vector2f(m_brush.getSize(), m_brush.getSize()));

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))return;

	for (int k = 0; k <= (botChunkId - rightChunkId) / (MAP_X_SIZE/CHUNK_X_SIZE); k++)
	{

		for (int i = leftChunkId; i <= rightChunkId; i++)
		{
			std::cout << i << std::endl;
			
			for (int x = 0; x < CHUNK_X_SIZE; x++)
			{
				for (int y = 0; y < CHUNK_Y_SIZE; y++)
				{
					if (m_brush.getBrushShape() == BrushShape::CIRCLE_BRUSH)
					{
						//m_terrain->setBlock(i * (MAP_X_SIZE / CHUNK_X_SIZE) + k , x, y, Block(Block::BlockId::ID_SAND, 1, sf::Color::Yellow));

						sf::Vector2f blockGlobalPos = m_terrain->getGlobalBlockPosition(i + k * (MAP_X_SIZE / CHUNK_X_SIZE), x, y);


						float radius2 = (m_mousePosRelativeToMap.x - blockGlobalPos.x) * (m_mousePosRelativeToMap.x - blockGlobalPos.x) +
							(m_mousePosRelativeToMap.y - blockGlobalPos.y) * (m_mousePosRelativeToMap.y - blockGlobalPos.y);

						if (radius2 < m_brush.getSize() * m_brush.getSize())
						{
							m_terrain->setBlock(i + k * (MAP_X_SIZE / CHUNK_X_SIZE), x, y, Block(Block::BlockId::ID_SAND, 1, sf::Color::Yellow));
						}
						//if(sf::Mouse::getPosition().x < blockGlobalPos)

					}
				}
			}

			m_terrain->refreshChunkTexture(i + k * (MAP_X_SIZE / CHUNK_X_SIZE));
		}
	}

}

void MapCreator::refreshUI(sf::Vector2f clickerPosition)
{
	m_buttonMenu1.checkStatus(clickerPosition);
}

void MapCreator::setBrushSize(float size)
{
	m_brush.setSize(size);
}

Brush::Brush()
{
}

Brush::~Brush()
{
}

void Brush::setBrushShape(BrushShape shape)
{
	this->m_brushShape = shape;
}

BrushShape Brush::getBrushShape() const
{
	return this->m_brushShape;
}

void Brush::setSize(float size)
{
	this->m_size = size;
}

float Brush::getSize() const
{
	return this->m_size;
}

void Brush::setPosition(sf::Vector2f position)
{
	this->m_position = position;
}

sf::Vector2f Brush::getPosition() const
{
	return this->m_position;
}



void MapCreator::drawBackground(sf::RenderWindow& window)
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	shape.setTexture(m_pResources->mapCreator_Backgrounds.getTexturePtr("table"));
	shape.setFillColor(sf::Color(30,30,30));
	
	window.draw(shape);
}

void MapCreator::drawEditArea(sf::RenderWindow& RenderWindow)
{
	m_terrain->renderChunks(RenderWindow, m_cameraPosition, m_viewport, m_zoom);
	
}

void MapCreator::drawUI(sf::RenderWindow& window)
{
	m_buttonMenu1.draw(window);
}

void MapCreator::generateOcean()
{
	sf::Vector2f genChunkPos0 = sf::Vector2f((CHUNK_X_SIZE + 1) / 2.0f, (CHUNK_Y_SIZE + 1) / 2.0f);//position of first chunk
																	//f.e (16,16)
	for (int x = 0; x < MAP_X_SIZE / CHUNK_X_SIZE; x++)
	{
		for (int y = 0; y < MAP_Y_SIZE / CHUNK_Y_SIZE; y++)
		{
			Chunk* chunk = new Chunk();

			m_terrain->addChunk(chunk);

			chunk->setCoords(sf::Vector2f(genChunkPos0.x + CHUNK_X_SIZE * y, genChunkPos0.y + CHUNK_Y_SIZE * x));

			chunk->fill(Block::BlockId::ID_SEAWATER);
		}
	}
}

void MapCreator::postTerrainRender()
{
}
