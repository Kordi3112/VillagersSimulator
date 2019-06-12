#include "Terrain.h"



Terrain::Terrain()
{
}


Terrain::~Terrain()
{
	this->releaseChunks();
}

void Terrain::generateMap(int seed)
{
	/// //////////////////////////////////
	// cordinates info:
	// (0,0) is left top vertex of map
	// x increased to right
	// y increased to down
	/// ///////////////////////
	srand(seed);

	createSea(seed);
	
	createLand(seed);
}

void Terrain::generateBlueBackground()
{
	sf::Vector2f genChunkPos0 = sf::Vector2f((CHUNK_X_SIZE ) / 2.0f, (CHUNK_Y_SIZE ) / 2.0f);//position of first chunk
																	//f.e (16,16)
	for (int x = 0; x < MAP_X_SIZE / CHUNK_X_SIZE; x++)
	{
		for (int y = 0; y < MAP_Y_SIZE / CHUNK_Y_SIZE; y++)
		{
			Chunk* chunk = new Chunk();

			m_map.push_back(chunk);

			chunk->setCoords(sf::Vector2f(genChunkPos0.x + CHUNK_X_SIZE * y, genChunkPos0.y + CHUNK_Y_SIZE * x));

			chunk->fill(Block::BlockId::ID_SEAWATER);
		}
	}

	refreshAllChunksTexture();
}

void Terrain::clear()
{
	for (int i = 0; i < m_map.size(); i++)
	{
		delete m_map[i];
	}

	m_map.clear();
}

void Terrain::refreshChunkTexture(int chunkId)
{
	if (chunkId < 0 or chunkId >= m_map.size())return;
	//else
	m_map[chunkId]->createTexture();
}

void Terrain::refreshAllChunksTexture()
{
	for (int x = 0; x < this->m_map.size(); x++)
	{
		m_map[x]->createTexture();
	}
}

void Terrain::releaseChunks()
{
	for (int i = this->m_map.size() - 1 ; i > 0; i--)
	{
		delete m_map[i];					//and whole chunk
	}

	m_map.clear();
}

void Terrain::renderChunks(sf::RenderWindow& window, sf::Vector2f cameraPosition, sf::Rect<float> viewPort, float zoom)
{
	sf::RenderTexture frameBuffer; //its bufor before drawing on the screen
	frameBuffer.create(viewPort.width * window.getSize().x, viewPort.height * window.getSize().y);
	frameBuffer.clear();

	const float chunkPxSize = zoom;//
	const sf::Vector2f frameCenter = sf::Vector2f(frameBuffer.getSize().x / 2.0f, frameBuffer.getSize().y / 2.0f);

	for (int id = 0; id < this->m_map.size(); id++)//checking whole chunks
	{
		//TODO: make this funcktion working
		//if(!MathOperations::areTwoRectanglesConnected(this->m_map[id]->getGlobalBlockPosition(0,0), this->m_map[id]->getGlobalBlockPosition(CHUNK_X_SIZE-1, CHUNK_Y_SIZE - 1),
		//										cameraPosition, viewPort, window.getSize(), zoom))continue;
		//	
		sf::Sprite sprite;
		sprite.setTexture(*this->m_map[id]->getTexturePtr());

		sprite.setPosition((this->m_map[id]->getCoords() - cameraPosition) * chunkPxSize + frameCenter);
		
		sprite.setOrigin(sf::Vector2f((CHUNK_X_SIZE + 1) / 2, (CHUNK_Y_SIZE + 1) / 2));
		sprite.setScale(zoom, zoom);

		frameBuffer.draw(sprite);
	}
	//
	

	frameBuffer.display();
	sf::Sprite frameBufferSprite(frameBuffer.getTexture());
	frameBufferSprite.setPosition(viewPort.left*window.getSize().x, viewPort.top * window.getSize().y);

	window.draw(frameBufferSprite);
}

float Terrain::distanceToBlock(sf::Vector2f point, unsigned int chunkId, int x, int y)
{

	if (chunkId >= this->m_map.size())return 0;

	return sqrt(this->distanceToBlock2(point, chunkId, x, y));
}

float Terrain::distanceToBlock2(sf::Vector2f point, unsigned int chunkId, int x, int y)
{
	if (chunkId >= this->m_map.size())return 0;

	const float xBlockPos = this->m_map[chunkId]->getGlobalBlockPosition(x, y).x;
	const float yBlockPos = this->m_map[chunkId]->getGlobalBlockPosition(x, y).y;

	return (xBlockPos - point.x) * (xBlockPos - point.x) + (yBlockPos - point.y) * (yBlockPos - point.y);
}

sf::Vector2f Terrain::getMapSizeInPx() const
{
	return sf::Vector2f(MAP_X_SIZE * CHUNK_X_SIZE, MAP_Y_SIZE * CHUNK_Y_SIZE);

}

unsigned Terrain::getChunksNumber() const
{
	return m_map.size();
}

sf::Vector2f Terrain::getGlobalBlockPosition(int id, int x, int y) const
{
	if (id < 0 or id >= m_map.size())
		return sf::Vector2f();

	else return m_map[id]->getGlobalBlockPosition(x, y);

	
}

Block Terrain::getBlock(int n, int x, int y) const
{
	if (n < 0 or n >= m_map.size())
		return Block();

	return m_map[n]->getBlock(x, y);
}

bool Terrain::setBlock(int n, int x, int y, Block material)
{
	if (n < 0 or n >= m_map.size())return false;

	return m_map[n]->setBlock(x, y, material);
}

bool Terrain::setBlock(sf::Vector2f blockPosition, int x, int y, Block material)
{
	if (blockPosition.x > getMapSizeInPx().x or blockPosition.y > getMapSizeInPx().y)
		return false;//block outside the map

	int n = 0;//witch index
	int m = 0;//height index


	n = round(blockPosition.x) / CHUNK_X_SIZE;
	m = round(blockPosition.y) / CHUNK_Y_SIZE;



}

bool Terrain::setBlock(int n, int x, int y, Block::BlockId id, int type, sf::Color blockColor)
{
	if (n < 0 or n >= m_map.size())return false;

	return m_map[n]->setBlock(x, y, id, type, blockColor);
}

void Terrain::addChunk(Chunk* chunk)
{
	m_map.push_back(chunk);
}


int Terrain::getTreesNumber() const
{
	return m_treeCoord.size();
}

Coord Terrain::getTreeCoord(int id) const
{
	if (id < 0 || id >= m_treeCoord.size())
		return Coord();

	else return m_treeCoord[id];
}

void Terrain::refreshTreeCoords()
{
	m_treeCoord.clear();

	for (int i = 0; i < getChunksNumber(); i++)
	{
		for(int x = 0; x < CHUNK_X_SIZE; x++)
		{
			for(int y = 0; y < CHUNK_Y_SIZE; y++)
			{
				if (getBlock(i, x, y).blockId == Block::BlockId::ID_GRASSTREE)
				{
					int random = x * y * i % 4;

					if (random == 0)
						m_treeCoord.push_back(Coord(getGlobalBlockPosition(i, x, y), 0, 0));
					else if (random == 1)
						m_treeCoord.push_back(Coord(getGlobalBlockPosition(i, x, y), 0, 1));
					else if (random == 2)
						m_treeCoord.push_back(Coord(getGlobalBlockPosition(i, x, y), 1, 0));
					else if (random == 3)
						m_treeCoord.push_back(Coord(getGlobalBlockPosition(i, x, y), 1, 1));
				}
			}
		}

	}
}

bool Terrain::loadFromFile(std::string path)
{
	clear();

	generateBlueBackground();

	std::string fileStream;
	//
	if (FileManaging::LoadFileToString("../data/maptest.map", fileStream) != FileManaging::GOOD)
	{
		return false;
	}
	//

	std::string letter;
	std::string row;
	std::string block;
	int blockId = 0; //in row
	int rowId = 0;

	for (int i = 0; i < fileStream.length(); i++)
	{
		letter = fileStream.substr(i, 1);


		if (letter == "\n")
		{
			if (rowId == 0)
			{
				//MAP_X_SIZE

			}
			else if (rowId == 1)
			{
				//MAP_Y_SIZE

			}
			else if (rowId == 2)
			{
				//CHUNK_X_SIZE

			}
			else if (rowId == 3)
			{
				//CHUNK_Y_SIZE

			}

			rowId++;

			if (rowId < 4)
				row.clear();

			block.clear();
			blockId = 0;
		}
		else if (letter == ",")
		{
			Block blockToFill;

			if (block.substr(0, 1) == "0") //first number is 0
			{
				blockToFill.blockId = (Block::BlockId)atoi(block.substr(1, 1).c_str());
			}
			else
			{
				blockToFill.blockId = (Block::BlockId)atoi(block.substr(0, 2).c_str());
			}

			blockToFill.type = atoi(block.substr(2, 1).c_str());

			setBlock(rowId - 4, blockId / CHUNK_X_SIZE, blockId % CHUNK_X_SIZE, blockToFill);

			blockId++;
			block.clear();
		}
		else
		{
			if (rowId < 4)
				row += letter;
			block += letter;
		}
	}

	refreshAllChunksTexture();

	return true;
}

bool Terrain::saveToFile(std::string path)
{
	std::string toSave;
	//INFORMATIONS ABOUT SIZE
	toSave += std::to_string(MAP_X_SIZE) + "\n";
	toSave += std::to_string(MAP_Y_SIZE) + "\n";
	//
	toSave += std::to_string(CHUNK_X_SIZE) + "\n";
	toSave += std::to_string(CHUNK_Y_SIZE) + "\n";
	//MAP
	for (int i = 0; i < m_map.size(); i++)
	{
		for (int x = 0; x < CHUNK_X_SIZE; x++)
		{
			for (int y = 0; y < CHUNK_Y_SIZE; y++)
			{
				Block block = getBlock(i, x, y);
				if (block.blockId < 10)
					toSave += "0";

				toSave += std::to_string((int)block.blockId);

				toSave += std::to_string(block.type);
				toSave += ",";
			}
		}

		toSave += "\n";
	}

	if (FileManaging::SaveStringToFile("../data/maptest.map", toSave) != FileManaging::STATUS::GOOD)
	{
		return false;
	}

	return true;
}

void Terrain::copyFrom(Terrain* terrain)
{
	clear();
	
	generateBlueBackground();

	for (int i = 0; i < terrain->getChunksNumber(); i++)
	{

		
		for (int x = 0; x < CHUNK_X_SIZE; x++)
		{
			for (int y = 0; y < CHUNK_Y_SIZE; y++)
			{
				setBlock(i, x, y, terrain->getBlock(i,x,y));
			}
		}
		
		
	}

	refreshAllChunksTexture();
}

int Terrain::getChunkId(sf::Vector2f blockPosition)
{
	if (blockPosition.x > getMapSizeInPx().x or blockPosition.y > getMapSizeInPx().y)
		return -1;//block outside the map

	int n = 0;//witch index
	int m = 0;//height index


	n = round(blockPosition.x) / CHUNK_X_SIZE;
	m = round(blockPosition.y) / CHUNK_Y_SIZE;

	return m * MAP_X_SIZE / CHUNK_X_SIZE + n;
}

void Terrain::createSea(int seed)
{
	sf::Vector2f genChunkPos0 = sf::Vector2f((CHUNK_X_SIZE + 1) / 2.0f, (CHUNK_Y_SIZE + 1) / 2.0f);//position of first chunk
																//f.e (16,16)
	for (int x = 0; x < MAP_X_SIZE / CHUNK_X_SIZE; x++)
	{
		for (int y = 0; y < MAP_Y_SIZE / CHUNK_Y_SIZE; y++)
		{
			Chunk* chunk = new Chunk();

			this->m_map.push_back(chunk);

			chunk->setCoords(sf::Vector2f(genChunkPos0.x + CHUNK_X_SIZE * x, genChunkPos0.y + CHUNK_Y_SIZE * y));

			

			for (int xChunk = 0; xChunk < CHUNK_X_SIZE; xChunk++)
			{
				for (int yChunk = 0; yChunk < CHUNK_Y_SIZE; yChunk++)
				{
					int random = rand()%3;
					if (random == 0)chunk->setBlock(xChunk, yChunk, Block::ID_SEAWATER, 0, sf::Color(0, 110, 128));
					else if (random == 1)chunk->setBlock(xChunk, yChunk, Block::ID_SEAWATER, 1, sf::Color(0, 100, 128));
					else if (random == 2)chunk->setBlock(xChunk, yChunk, Block::ID_SEAWATER, 2, sf::Color(0, 90, 128));

				}
		
			}
		}
	}
}

void Terrain::createLand(int seed)
{
	//
	sf::Vector2f* landPoints = new sf::Vector2f[5];
	int* pointsRadius = new int[5];

	for (int i = 0; i < 5; i++)
	{
		landPoints[i] = sf::Vector2f((float)rand() / (float)RAND_MAX * (float)MAP_X_SIZE, (float)rand() / (float)RAND_MAX * (float)MAP_Y_SIZE);
		pointsRadius[i] = (float)rand() / (float)RAND_MAX * 400.0f;// 400 is max radius

	}

	PerlinNoise perlinNoise(576);
	PerlinNoise perlinNoise2(250);
	//
	
	for (int id = 0; id < this->m_map.size(); id++)
	{
		for (int x = 0; x < CHUNK_X_SIZE;x++)
		{
			for (int y = 0; y < CHUNK_Y_SIZE; y++)
			{
				float val = perlinNoise.noise(1*this->m_map[id]->getGlobalBlockPosition(x, y).x/(float)MAP_X_SIZE,1* this->m_map[id]->getGlobalBlockPosition(x, y).y/(float)MAP_X_SIZE, 25);
				//val += 0.5f*perlinNoise2.noise(5 * this->m_map[id]->getGlobalBlockPosition(x, y).x / (float)MAP_X_SIZE, 5 * this->m_map[id]->getGlobalBlockPosition(x, y).y / (float)MAP_X_SIZE, 25);
				//val += 0.2f * perlinNoise2.noise(10 * this->m_map[id]->getGlobalBlockPosition(x, y).x / (float)MAP_X_SIZE, 10 * this->m_map[id]->getGlobalBlockPosition(x, y).y / (float)MAP_X_SIZE, 25);
				//val += perlinNoise.noise(5 * this->m_map[id]->getGlobalBlockPosition(x+1, y+1).x / (float)MAP_X_SIZE, 5 * this->m_map[id]->getGlobalBlockPosition(x+1, y+1).y / (float)MAP_X_SIZE, 25);
				//val *= 0.588f; //1/1.7f
				/*
				if (val <= -0.1f+(float)random*0.0004f)this->m_map[id]->setBlock(x, y, Block::ID_SAND, 1, sf::Color::Red);
				else this->m_map[id]->setBlock(x, y, Block::ID_SAND, 1, sf::Color((val+1)*0.5f *255, (val + 1) * 255*0.5f, (val + 1) * 0.5f* 255));
				*/
				int random = rand() % 10;

				if (val <= -0.3f)//Deep Ocean
				{
					int random = rand() % 3;
					if (random == 0)this->m_map[id]->setBlock(x, y, Block::ID_SEAWATER, 0, sf::Color(20, 100, 240));
					else if (random == 1)this->m_map[id]->setBlock(x, y, Block::ID_SEAWATER, 1, sf::Color(20, 125, 230));
					else if (random == 2)this->m_map[id]->setBlock(x, y, Block::ID_SEAWATER, 2, sf::Color(20, 115, 220));
				}
				else if (val <= -0.1f + (float)random * 0.0002f)//tile ocean
				{
					int random = rand() % 3;
					if (random == 0)this->m_map[id]->setBlock(x, y, Block::ID_SEAWATER, 3, sf::Color(20, 100, 255));
					else if (random == 1)this->m_map[id]->setBlock(x, y, Block::ID_SEAWATER, 4, sf::Color(20, 125, 255));
					else if (random == 2)this->m_map[id]->setBlock(x, y, Block::ID_SEAWATER, 5, sf::Color(20, 115, 250));
				}
				else if (val <= 0.3f + (float)random * 0.0002f)//lowlands
				{
					int random = rand() % 3;
					if (random == 0)this->m_map[id]->setBlock(x, y, Block::ID_GRASS, 0, sf::Color(0, 190, 0));
					else if (random == 1)this->m_map[id]->setBlock(x, y, Block::ID_GRASS, 1, sf::Color(0, 180, 0));
					else if (random == 2)this->m_map[id]->setBlock(x, y, Block::ID_GRASS, 2, sf::Color(0, 170, 0));

				}
				else if (val <= 0.5f + (float)random * 0.0002f)//highlands
				{
					int random = rand() % 3;
					if (random == 0)this->m_map[id]->setBlock(x, y, Block::ID_GRASS, 3, sf::Color(0, 165, 0));
					else if (random == 1)this->m_map[id]->setBlock(x, y, Block::ID_GRASS, 4, sf::Color(0, 160, 0));
					else if (random == 2)this->m_map[id]->setBlock(x, y, Block::ID_GRASS, 5, sf::Color(0, 155, 0));
				}
				else //mountains
				{

				}
				/*

				if (val > 0.0) {
					int random = rand() % 3;
					if (random == 0)this->m_map[id]->setBlock(x, y, Block::ID_GRASS, 0, sf::Color(0, 200, 0));
					else if (random == 1)this->m_map[id]->setBlock(x, y, Block::ID_GRASS, 1, sf::Color(0, 190, 0));
					else if (random == 2)this->m_map[id]->setBlock(x, y, Block::ID_GRASS, 2, sf::Color(0, 180, 0));

				}
				else if (val <= 0.0 and val > -0.1)
				{
					int random = rand() % 2;
					if (random == 0)this->m_map[id]->setBlock(x, y, Block::ID_SAND, 0, sf::Color(240, 220, 50));
					else if (random == 1)this->m_map[id]->setBlock(x, y, Block::ID_SAND, 1, sf::Color(220, 200, 20));

				}
				*/
				
			}
		}
	}


			
		
	

	//RELEASE
	delete[] landPoints;
	delete[] pointsRadius;
}


///  //////////////////////////////
//  CHUNK
///  ///////////////////////////////


Chunk::Chunk()
{
}

Chunk::~Chunk()
{
	delete this->m_texture;
}

void Chunk::fill(Block material)
{
	for (int x = 0; x < CHUNK_X_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_Y_SIZE; y++)
		{
			this->m_block[x][y] = material;
		}
	}

	m_changed = true;
}

Block Chunk::getBlock(int x, int y) const
{
	if ((x < 0 or x >= CHUNK_X_SIZE) or (y < 0 or y >= CHUNK_Y_SIZE))
		return Block();
	
	return m_block[x][y];
}

bool Chunk::setBlock(int x, int y, Block material)
{
	if ((x < 0 or x >= CHUNK_X_SIZE) or (y < 0 or y >= CHUNK_Y_SIZE))return false;

	m_block[x][y] = material;

	m_changed = true;

	return true;
}

bool Chunk::setBlock(int x, int y, Block::BlockId id, int type, sf::Color blockColor)
{
	if ((x < 0 or x >= CHUNK_X_SIZE) or (y < 0 or y >= CHUNK_Y_SIZE))return false;

	this->m_block[x][y] = Block(id, type, blockColor);

	m_changed = true;

	return true;
}

void Chunk::setCoords(sf::Vector2f coords)
{
	this->m_coords = coords;
}

sf::Vector2f Chunk::getCoords() const
{
	return this->m_coords;
}

sf::Vector2f Chunk::getGlobalBlockPosition(int x, int y) const
{  
	//f.e.
	//x, y are from 0 to 50
	//middle is 25

	const sf::Vector2f middle = sf::Vector2f((CHUNK_X_SIZE-1)/2, (CHUNK_Y_SIZE - 1)/2);
	
	return sf::Vector2f(this->getCoords().x + x - middle.x, this->getCoords().y + y - middle.y);
}



sf::Texture* Chunk::getTexturePtr() const
{
	return m_texture;
}

void Chunk::setTexturePtr(sf::Texture* texture)
{
	//if(m_texture != nullptr)
	//	delete m_texture;

	m_texture = texture;
}

void Chunk::createTexture()
{
	createTextureOnDemand(false);
}

void Chunk::createTextureOnDemand(bool onDemand)
{
	if(!onDemand)
		if (!m_changed)return; //its not neccesary to update if chunks has no changes

	if(m_texture != nullptr)
	delete m_texture; //destroy previous texture

	m_texture = new sf::Texture(); //create new Texture
	m_texture->create(CHUNK_X_SIZE, CHUNK_Y_SIZE); //...

	sf::Image image;


	image.create(CHUNK_X_SIZE, CHUNK_Y_SIZE, Block::getBlockColor(Block::ID_NOTHING));

	for (int x = 0; x < CHUNK_X_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_Y_SIZE; y++)
		{
			image.setPixel(x, y, Block::getBlockColor(getBlock(x,y)));
		}
	}
	

	m_texture->loadFromImage(image);

	m_changed = false;
}

Block::Block()
{
	blockId = ID_NOTHING;
}

Block::Block(BlockId id)
{
	blockId = id;
	Block::type = 0;
}

Block::Block(BlockId id, int type)
{
	blockId = id;
	Block::type = type;

}

Block::Block(BlockId id, int type, sf::Color color)
{
	blockId = id;
	Block::type = type;
	color = color;
}

Block::~Block()
{
}


sf::Color Block::getBlockColor(Block block)
{
	if (block.color != sf::Color())
		return block.color;


	if (block.blockId == ID_NOTHING)
		return NOTHING_COLOR;
	else if (block.blockId == ID_WATER)
	{
		if (block.type == 0)
			return WATER_COLOR;
		else if(block.type == 1)
			return WATER_COLOR_1;
		else if (block.type == 2)
			return WATER_COLOR_2;
		else if (block.type == 3)
			return WATER_COLOR_3;
	}
	else if (block.blockId == ID_SEAWATER)
	{
		if(block.type == 0)
			return SEAWATER_COLOR;
		else if (block.type == 1)
			return SEAWATER_COLOR_1;	
		else if (block.type == 2)
			return SEAWATER_COLOR_2;
		else if (block.type == 3)
			return SEAWATER_COLOR_3;
	}
	else if (block.blockId == ID_GRASS)
	{
		if (block.type == 0)
			return GRASS_COLOR;
		else if (block.type == 1)
			return GRASS_COLOR_1;
		else if (block.type == 2)
			return GRASS_COLOR_2;
		else if (block.type == 3)
			return GRASS_COLOR_3;

	}
	else if (block.blockId == ID_SAND)return SAND_COLOR;
	else if (block.blockId == ID_TREE)return TREE_COLOR;
	else if (block.blockId == ID_GRASSTREE)return GRASSTREE_COLOR;
	else if (block.blockId == ID_SNOWTREE)return SNOWTREE_COLOR;
	else if (block.blockId == ID_SNOW)return SNOW_COLOR;
	else if (block.blockId == ID_ROCK1)return ROCK1_COLOR;
	else if (block.blockId == ID_ROCK2)return ROCK2_COLOR;
	
	
	return sf::Color();
}
