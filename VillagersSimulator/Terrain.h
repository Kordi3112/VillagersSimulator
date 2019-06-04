#pragma once
#include <SFML/Graphics.hpp>
#include <vector> //cointainer
#include <stdlib.h>
#include <iostream>
#include <math.h>
//
#include "MathOperations.h"
#include "PerlinNoise.h"

enum Biomes
{
	BIOME_STEPPES,
	BIOME_OCEAN,
	BIOME_DESERT,
	BIOME_FOREST

};


const sf::Color NOTHING_COLOR = sf::Color::Transparent;
const sf::Color WATER_COLOR = sf::Color::Cyan;
const sf::Color SEAWATER_COLOR = sf::Color::Blue;
const sf::Color GRASS_COLOR = sf::Color::Green;
const sf::Color SAND_COLOR = sf::Color::Yellow;
const sf::Color TREE_COLOR = sf::Color::Red;  //its for a while
const sf::Color ROCK1_COLOR = sf::Color::Black;  


class Block
{
public:
	//
	enum BlockId
	{
		ID_NOTHING = 0,// 
		ID_WATER,  //sweet water in lakes, rivers etc.
		ID_SEAWATER,
		ID_GRASS,
		ID_SAND,
		ID_TREE,
		ID_ROCK1,
		ID_ROCK2
	};
	//
	BlockId blockId;
	int type=0;
	sf::Color color;
	//
	Block();
	Block(BlockId id);
	Block(BlockId id, int type);
	Block(BlockId id, int type, sf::Color color);
	~Block();

	//
	static sf::Color getBlockColor(BlockId blockId);
};



//
const int CHUNK_X_SIZE = 51; //must be odd number
const int CHUNK_Y_SIZE = 51; //must be odd number

//it is area of terrain CHUNK_X_SIZE x CHUNK_Y_SIZE [m]   <- block on the center of chunck shows coords whole chunk 
class Chunk 
{
public:
	
	Chunk();
	~Chunk();
	//
	void fill(Block material);
	Block getBlock(int x, int y) const;
	bool setBlock(int x, int y, Block material);
	bool setBlock(int x, int y, Block::BlockId id, int type, sf::Color blockColor);
	//
	void setCoords(sf::Vector2f coords);
	sf::Vector2f getCoords() const;
	sf::Vector2f getGlobalBlockPosition(int x, int y) const;
	//
	bool isUnitary() const;
	//
	sf::Texture* getTexturePtr() const;
	void createTexture();   //its many process demand function!
private:
	Block m_block[CHUNK_X_SIZE][CHUNK_Y_SIZE];
	bool m_isUnitary = false; //if all block is chunk are the same, it will help for fast render
	Block m_unitaryChunksBlockId;
	sf::Vector2f m_coords;
	sf::Texture* m_texture;
};

const int MAP_X_SIZE = CHUNK_X_SIZE * 20; //2480
const int MAP_Y_SIZE = CHUNK_Y_SIZE * 20;

class Terrain
{
public:

	Terrain();
	~Terrain();

	void generateMap(int seed);
	void refreshChunkTexture(int chuckId); //calls Chunk::createTexture()
	void refreshAllChunksTexture(); //the same like above
	void releaseChunks(); //! very important to use that, release chunks memory space
	//
	void renderChunks(sf::RenderWindow& window, sf::Vector2f cameraPosition, sf::Rect<float> viewPort, float zoom);
	//
	float distanceToBlock(sf::Vector2f point, unsigned int chunkId, int x, int y);
	float distanceToBlock2(sf::Vector2f point, unsigned int chunkId, int x, int y); //it returns distance*distance
	//
	sf::Vector2f getMapSizeInPx() const;
	//
	Block getBlock(int n,int x, int y) const;
	bool setBlock(int n, int x, int y, Block material);
	bool setBlock(sf::Vector2f blockPosition, int x, int y, Block material);
	bool setBlock(int n, int x, int y, Block::BlockId id, int type, sf::Color blockColor);
	void addChunk(Chunk* chunk);
	//
	//-1 means fail
	int getChunkId(sf::Vector2f blockPosition);
private:
	std::vector<Chunk*> m_map;
	//
	//MAP GENERATION PROCESS
	void createSea(int seed);
	void createLand(int seed);
};

