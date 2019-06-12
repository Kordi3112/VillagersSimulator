#include "MapCreator.h"



MapCreator::MapCreator()
{
}


MapCreator::~MapCreator()
{
	//delete terrain
	delete m_terrain;

	delete m_copyTerrain;
	//ButtonMenu
	m_buttonMenu1.releaseAllComponents();
	m_dialogWindowControler.releaseAllElements();
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
	m_terrain->generateBlueBackground();
	//create map bitmaps
	m_terrain->refreshAllChunksTexture();

	///INIT UI
	//TextBoxes
	ve::TextBox* textBox = new ve::TextBox();
	textBox->setBackgroundColor(sf::Color::Black);
	textBox->setTextColor(sf::Color::White);
	textBox->setTextFont(&m_pResources->font_Roboto_Thin);
	textBox->setSize(sf::Vector2f(window.getSize().x*0.86f, window.getSize().y / 30.0f));
	textBox->setPosition(sf::Vector2f(window.getSize().x * 0.07f + textBox->getSize().x / 2.0f, window.getSize().y * 0.95f));
	textBox->setTextPlace(ve::TextBox::TEXT_LEFT, ve::TextBox::TEXT_TOP);
	textBox->setTextSize(24);

	m_dialogWindowControler.addElement("textBox", textBox);
	//INit Button
	m_buttonMenu1.initButton();
	m_buttonMenu1.setButtonSize(sf::Vector2f(window.getSize().y * 0.6f * 0.15f, window.getSize().y * 0.6f));
	m_buttonMenu1.setButtonPosition(sf::Vector2f(window.getSize().x - window.getSize().y * 0.6f * 0.1f, window.getSize().y / 2.0f));
	m_buttonMenu1.setButtonTextures(m_pResources->mapCreator_Buttons.getTexturePtr("rightPanelInit"), m_pResources->mapCreator_Buttons.getTexturePtr("rightPanelInit"), m_pResources->mapCreator_Buttons.getTexturePtr("rightPanelInit"));
	//Background
	m_buttonMenu1.setSize(sf::Vector2f(0.2f * window.getSize().x, m_buttonMenu1.getButtonSize().y * 1.5f));
	m_buttonMenu1.setBackgroundTexture(m_pResources->mapCreator_Backgrounds.getTexturePtr("rightPanel"));
	m_buttonMenu1.setPosition(sf::Vector2f(m_buttonMenu1.getButtonPosition().x - 3.5f*m_buttonMenu1.getButtonSize().x, m_buttonMenu1.getButtonPosition().y));
	//Menu button
	ve::RectangleButton* menuButton = new ve::RectangleButton();

	menuButton->setTextures(m_pResources->mapCreator_Buttons.getTexturePtr("menu_noClicked"),
		m_pResources->mapCreator_Buttons.getTexturePtr("menu_onIt"),
		m_pResources->mapCreator_Buttons.getTexturePtr("menu_clicked"));
	menuButton->setSize(sf::Vector2f(m_buttonMenu1.getSize().x * 0.2f, m_buttonMenu1.getSize().x * 0.2f));
	menuButton->setPosition(sf::Vector2f(window.getSize().x - window.getSize().y * 0.6f * 0.1f, window.getSize().y * 0.05f));

	m_dialogWindowControler.addElement("menuButton", menuButton);
	//Choose Brush Buttons
	ve::ButtonsPanel* brushButtonPanel = new ve::ButtonsPanel();
	

	ve::RectangleButton* brushType1 = new ve::RectangleButton();
	brushType1->setTextures(m_pResources->mapCreator_Buttons.getTexturePtr("circleBrush_noClicked"), m_pResources->mapCreator_Buttons.getTexturePtr("circleBrush_onIt"), m_pResources->mapCreator_Buttons.getTexturePtr("circleBrush_clicked"));
	brushType1->setSize(sf::Vector2f(m_buttonMenu1.getSize().x * 0.1f, m_buttonMenu1.getSize().x * 0.1f));
	brushType1->setPosition(sf::Vector2f(m_buttonMenu1.getPosition().x - m_buttonMenu1.getSize().x / 4.0f, m_buttonMenu1.getPosition().y - m_buttonMenu1.getSize().y * 0.45f));
	brushType1->setAdditionalParameters(ve::LOCK_WHEN_CLICKED);

	brushButtonPanel->addButton("circleBrush", brushType1);

	ve::RectangleButton* brushType2 = new ve::RectangleButton();
	*brushType2 = *brushType1;
	brushType2->setTextures(m_pResources->mapCreator_Buttons.getTexturePtr("rectangleBrush_noClicked"), m_pResources->mapCreator_Buttons.getTexturePtr("rectangleBrush_onIt"), m_pResources->mapCreator_Buttons.getTexturePtr("rectangleBrush_clicked"));
	brushType2->setPosition(sf::Vector2f(m_buttonMenu1.getPosition().x + m_buttonMenu1.getSize().x / 4.0f, m_buttonMenu1.getPosition().y - m_buttonMenu1.getSize().y * 0.45f));

	brushButtonPanel->addButton("rectangleBrush", brushType2);

	m_buttonMenu1.addComponent("brushButtonPanel", brushButtonPanel);
	//Sliders
	ve::Slider* sizeSlider = new ve::Slider();
	sizeSlider->setSliderColor(sf::Color::White);
	sizeSlider->setSliderPointerColor(sf::Color::Yellow);
	sizeSlider->setSize(sf::Vector2f(m_buttonMenu1.getSize().x * 0.7f, m_buttonMenu1.getSize().y*0.03f));
	sizeSlider->setPosition(sf::Vector2f(m_buttonMenu1.getPosition().x, m_buttonMenu1.getPosition().y - m_buttonMenu1.getSize().y * 0.35f));
	sizeSlider->setValue(0.5f);

	ve::Slider* hardnessSlider = new ve::Slider();
	*hardnessSlider = *sizeSlider; //copy
	hardnessSlider->setPosition(sf::Vector2f(m_buttonMenu1.getPosition().x, m_buttonMenu1.getPosition().y - m_buttonMenu1.getSize().y * 0.25f));
	hardnessSlider->setValue(1.0f);

	m_buttonMenu1.addComponent("sizeSlider", sizeSlider);
	m_buttonMenu1.addComponent("hardnessSlider", hardnessSlider);

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
	m_buttonMenu1.addComponent("terrainButtonPanel", buttonPanelTerrain);
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

void MapCreator::moveEditAreaCamera(sf::Vector2f vector)
{
	m_cameraPosition += vector;
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

void MapCreator::refresh(unsigned deltaTime, sf::RenderWindow& window)
{
	
	///OPTIMALIZATION STUFF
	int leftChunkId = m_terrain->getChunkId(getMousePosRelativeToMap() - sf::Vector2f(m_brush.getSize(), m_brush.getSize()));
	int rightChunkId = m_terrain->getChunkId(getMousePosRelativeToMap() - sf::Vector2f(-m_brush.getSize(), m_brush.getSize()));
	int botChunkId = m_terrain->getChunkId(getMousePosRelativeToMap() + sf::Vector2f(m_brush.getSize(), m_brush.getSize()));
	//
	if (sf::Mouse::getPosition().x < getEditAreaViewport().left * window.getSize().x || sf::Mouse::getPosition().x >(getEditAreaViewport().left + getEditAreaViewport().width) * window.getSize().x ||
		sf::Mouse::getPosition().y < getEditAreaViewport().top * window.getSize().y || sf::Mouse::getPosition().y >(getEditAreaViewport().top + getEditAreaViewport().height) * window.getSize().y)
	{
		return;
	}

	if (m_buttonMenu1.isActive())return;

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))return;
	///UPDATE BRUSH
	//PICKED BLOCK
	int clickedbuttonId = m_buttonMenu1.getComponentButtonPanel("terrainButtonPanel")->getClickedButtonId();
	if (clickedbuttonId == -1)
	{
		m_brush.setPickedBlock(Block(Block::BlockId::ID_NOTHING));
	}
	else
	{
		std::string clickedName = m_buttonMenu1.getComponentButtonPanel("terrainButtonPanel")->getName(clickedbuttonId);
		if (clickedName == "seawater")
			m_brush.setPickedBlock(Block(Block::BlockId::ID_SEAWATER));
		else if (clickedName == "water")
			m_brush.setPickedBlock(Block(Block::BlockId::ID_WATER));
		else if (clickedName == "grass")
			m_brush.setPickedBlock(Block(Block::BlockId::ID_GRASS));
		else if (clickedName == "sand")
			m_brush.setPickedBlock(Block(Block::BlockId::ID_SAND));
		else if (clickedName == "rock1")
			m_brush.setPickedBlock(Block(Block::BlockId::ID_ROCK1));
		else if (clickedName == "rock2")
			m_brush.setPickedBlock(Block(Block::BlockId::ID_ROCK2));
		else if (clickedName == "snow")
			m_brush.setPickedBlock(Block(Block::BlockId::ID_SNOW));
		else if (clickedName == "tree")
			m_brush.setPickedBlock(Block(Block::BlockId::ID_GRASSTREE));
		//....
		
	}
	//SIZE
	float maxBrushSize = 80.0f;
	m_brush.setSize(m_buttonMenu1.getComponentSlider("sizeSlider")->getValue() * maxBrushSize);
	//HARDNESS
	m_brush.setHardness(m_buttonMenu1.getComponentSlider("hardnessSlider")->getValue());
	//SHAPE
	clickedbuttonId = m_buttonMenu1.getComponentButtonPanel("brushButtonPanel")->getClickedButtonId();
	if (clickedbuttonId == -1)
	{
		m_brush.setBrushShape(BrushShape::CIRCLE_BRUSH);
	}
	else
	{
		std::string clickedName = m_buttonMenu1.getComponentButtonPanel("brushButtonPanel")->getName(clickedbuttonId);
		if (clickedName == "circleBrush")
			m_brush.setBrushShape(BrushShape::CIRCLE_BRUSH);
		else if (clickedName == "rectangleBrush")
			m_brush.setBrushShape(BrushShape::SQUARE_BRUSH);
		//....

	}
	///RAND HANDLE
	Random random;
	
	///
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

						sf::Vector2f blockGlobalPos = m_terrain->getGlobalBlockPosition(i + k * (MAP_X_SIZE / CHUNK_X_SIZE), x, y);


						float radius2 = (m_mousePosRelativeToMap.x - blockGlobalPos.x) * (m_mousePosRelativeToMap.x - blockGlobalPos.x) +
							(m_mousePosRelativeToMap.y - blockGlobalPos.y) * (m_mousePosRelativeToMap.y - blockGlobalPos.y);

						if (radius2 < m_brush.getSize() * m_brush.getSize())
						{
							if(m_brush.getHardness() > 0.95f)
								m_terrain->setBlock(i + k * (MAP_X_SIZE / CHUNK_X_SIZE), x, y, m_brush.getPickedBlocked());
							else
							{
								if(random.Next(0,95) < m_brush.getHardness() * 100)
									m_terrain->setBlock(i + k * (MAP_X_SIZE / CHUNK_X_SIZE), x, y, m_brush.getPickedBlocked());
							}
						}
			

					}
					else if (m_brush.getBrushShape() == BrushShape::SQUARE_BRUSH)
					{
						sf::Vector2f blockGlobalPos = m_terrain->getGlobalBlockPosition(i + k * (MAP_X_SIZE / CHUNK_X_SIZE), x, y);

						if (blockGlobalPos.x > m_mousePosRelativeToMap.x - m_brush.getSize() && blockGlobalPos.x < m_mousePosRelativeToMap.x + m_brush.getSize() &&
							blockGlobalPos.y > m_mousePosRelativeToMap.y - m_brush.getSize() && blockGlobalPos.y < m_mousePosRelativeToMap.y + m_brush.getSize())
						{
							if (m_brush.getHardness() > 0.95f)
								m_terrain->setBlock(i + k * (MAP_X_SIZE / CHUNK_X_SIZE), x, y, m_brush.getPickedBlocked());
							else
							{
								if (random.Next(0, 95) < m_brush.getHardness() * 100)
									m_terrain->setBlock(i + k * (MAP_X_SIZE / CHUNK_X_SIZE), x, y, m_brush.getPickedBlocked());
							}
						}
					}
				}
			}

			m_terrain->refreshChunkTexture(i + k * (MAP_X_SIZE / CHUNK_X_SIZE));
		}
	}

}

void MapCreator::refreshUI(sf::Vector2f clickerPosition)
{
	m_dialogWindowControler.checkStatus(clickerPosition);
	m_buttonMenu1.checkStatus(clickerPosition);
	//textBoxes
	std::string textBoxString;
	textBoxString += "Camera position: " + std::to_string((int)m_cameraPosition.x) + ", " + std::to_string((int)m_cameraPosition.y);
	textBoxString += "                Zoom: " + std::to_string(m_zoom) + "                ";
	textBoxString += "Map mouse Coords: " + std::to_string((int)m_mousePosRelativeToMap.x) + ", " + std::to_string((int)m_mousePosRelativeToMap.y);
	m_dialogWindowControler.getTextBoxPtr("textBox")->setString(textBoxString);
	//

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

void Brush::setPickedBlock(Block block)
{
	m_blockPicked = block;
}

Block Brush::getPickedBlocked() const
{
	return m_blockPicked;
}

void Brush::setHardness(float level)
{
	m_hardness = level;
}

float Brush::getHardness() const
{
	return m_hardness;
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
	m_dialogWindowControler.draw(window);
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

void MapCreator::saveMap()
{
	m_terrain->saveToFile("../data/maptest.map");
}

void MapCreator::loadMap()
{
	m_terrain->loadFromFile("../data/maptest.map");

}

void MapCreator::swapTerrainPointers()
{
	Terrain* buforPtr = m_terrain;
	m_terrain = m_copyTerrain;
	m_copyTerrain = buforPtr;
}

void MapCreator::copyTerrain()
{
	if (m_copyTerrain == nullptr)
	{
		m_copyTerrain = new Terrain();
		m_copyTerrain->copyFrom(m_terrain);
	}
	else
	{
		m_copyTerrain->copyFrom(m_terrain);
	}
}

void MapCreator::postTerrainRender()
{
	//making copy for post render
	copyTerrain();
	//
	Random random; //random handle
	//
	for (int i = 0; i < m_copyTerrain->getChunksNumber(); i++)
	{
		for (int x = 0; x < MAP_X_SIZE; x++)
		{
			for (int y = 0; y < MAP_Y_SIZE; y++)
			{
				
				if (m_copyTerrain->getBlock(i, x, y).blockId == Block::BlockId::ID_SEAWATER)
				{
					int randNumber = (x* x * y * i + 1323) % 3 +1;

					if (randNumber == 1)
						m_copyTerrain->setBlock(i, x, y, Block(Block::BlockId::ID_SEAWATER, 1));
					else if (randNumber == 2)
						m_copyTerrain->setBlock(i, x, y, Block(Block::BlockId::ID_SEAWATER, 2));
					else if (randNumber == 3)
						m_copyTerrain->setBlock(i, x, y, Block(Block::BlockId::ID_SEAWATER, 3));
					
				}
				else if (m_copyTerrain->getBlock(i, x, y).blockId == Block::BlockId::ID_WATER)
				{
					int randNumber = (x * x * y * i + 1323) % 3 + 1;

					if (randNumber == 1)
						m_copyTerrain->setBlock(i, x, y, Block(Block::BlockId::ID_WATER, 1));
					else if (randNumber == 2)
						m_copyTerrain->setBlock(i, x, y, Block(Block::BlockId::ID_WATER, 2));
					else if (randNumber == 3)
						m_copyTerrain->setBlock(i, x, y, Block(Block::BlockId::ID_WATER, 3));

				}
				else if (m_copyTerrain->getBlock(i, x, y).blockId == Block::BlockId::ID_GRASS)
				{
					int randNumber = (x * x * y * i + 1323) % 3 + 1;

					if (randNumber == 1)
						m_copyTerrain->setBlock(i, x, y, Block(Block::BlockId::ID_GRASS, 1));
					else if (randNumber == 2)
						m_copyTerrain->setBlock(i, x, y, Block(Block::BlockId::ID_GRASS, 2));
					else if (randNumber == 3)
						m_copyTerrain->setBlock(i, x, y, Block(Block::BlockId::ID_GRASS, 3));

				}
			}
		}
	}
	//
	m_copyTerrain->refreshAllChunksTexture();
}
