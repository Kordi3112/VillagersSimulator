#include "MapCreator.h"



MapCreator::MapCreator()
{
}


MapCreator::~MapCreator()
{
	//delete terrain
	delete m_terrain;
}

void MapCreator::drawScene(sf::RenderWindow& RenderWindow)
{
	drawEditArea(RenderWindow);
	//drawUI
}

void MapCreator::init()
{
	//create terrain
	m_terrain = new Terrain();
	//default piece of terrain
	generateOcean();

	//create map bitmaps
	m_terrain->refreshAllChunksTexture();
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



void MapCreator::drawEditArea(sf::RenderWindow& RenderWindow)
{
	m_terrain->renderChunks(RenderWindow, m_cameraPosition, m_viewport, m_zoom);
	
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

			chunk->setCoords(sf::Vector2f(genChunkPos0.x + CHUNK_X_SIZE * x, genChunkPos0.y + CHUNK_Y_SIZE * y));

			chunk->fill(Block::BlockId::ID_SEAWATER);
		}
	}
}
