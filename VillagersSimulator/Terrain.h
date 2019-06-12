#pragma once
#include <SFML/Graphics.hpp>
#include <vector> //cointainer
#include <stdlib.h>
#include <iostream>
#include <math.h>
//
#include "FileManaging.h"
#include "Random.h"
#include "Coord.h"
#include "MathOperations.h"
#include "PerlinNoise.h"

enum Biomes
{
	BIOME_STEPPES,
	BIOME_OCEAN,
	BIOME_DESERT,
	BIOME_FOREST

};

///COLORS DEFINITION
const sf::Color NOTHING_COLOR = sf::Color::Transparent;
//
const sf::Color WATER_COLOR = sf::Color::Cyan;
const sf::Color WATER_COLOR_1 = sf::Color(0,128,255);
const sf::Color WATER_COLOR_2 = sf::Color(20,130,255);
const sf::Color WATER_COLOR_3 = sf::Color(20,120,235);
//
const sf::Color SEAWATER_COLOR = sf::Color::Blue;
const sf::Color SEAWATER_COLOR_1 = sf::Color(20,100,160);
const sf::Color SEAWATER_COLOR_2 = sf::Color(30,120,170);
const sf::Color SEAWATER_COLOR_3 = sf::Color(30,115,160);
//
const sf::Color GRASS_COLOR = sf::Color::Green;
const sf::Color GRASS_COLOR_1 = sf::Color(65, 160, 30);
const sf::Color GRASS_COLOR_2 = sf::Color(60, 150, 30);
const sf::Color GRASS_COLOR_3 = sf::Color(85, 150, 35);


//
const sf::Color SAND_COLOR = sf::Color::Yellow;
const sf::Color TREE_COLOR = sf::Color::Red;  //its for a while
const sf::Color GRASSTREE_COLOR = sf::Color::Red;  //its for a while
const sf::Color SNOWTREE_COLOR = sf::Color::Red;  //its for a while
const sf::Color SNOW_COLOR = sf::Color::White;
const sf::Color ROCK1_COLOR = sf::Color(82,82,82);  
const sf::Color ROCK2_COLOR = sf::Color(127,127,127);  


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
		ID_SNOW,
		ID_SWAMP,
		ID_TREE,
		ID_GRASSTREE,
		ID_SNOWTREE,
		ID_ROCK1,
		ID_ROCK2
	};
	//
	BlockId blockId;
	int type;
	sf::Color color = sf::Color();
	//
	Block();
	Block(BlockId id);
	Block(BlockId id, int type);
	Block(BlockId id, int type, sf::Color color);
	~Block();

	//
	static sf::Color getBlockColor(Block block);

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
	//
	sf::Texture* getTexturePtr() const;
	void setTexturePtr(sf::Texture* texture);

	void createTexture();   //its many process demand function!
	void createTextureOnDemand(bool onDemand); //onDemand = true; create new texture even if is up to date
private:
	Block m_block[CHUNK_X_SIZE][CHUNK_Y_SIZE];
	bool m_isUnitary = false; //if all block is chunk are the same, it will help for fast render

	bool m_changed = true;
	
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
	//
	void generateBlueBackground();//sets all block to seawater
	//
	void clear();
	//
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
	unsigned getChunksNumber() const;
	sf::Vector2f getGlobalBlockPosition(int id, int x, int y) const;
	//
	Block getBlock(int n,int x, int y) const;
	bool setBlock(int n, int x, int y, Block material);
	bool setBlock(sf::Vector2f blockPosition, int x, int y, Block material);
	bool setBlock(int n, int x, int y, Block::BlockId id, int type, sf::Color blockColor);
	void addChunk(Chunk* chunk);
	///TREES
	int getTreesNumber() const;
	Coord getTreeCoord(int id) const;
	void refreshTreeCoords();
	///SAVE & LOAD
	bool loadFromFile(std::string path);
	bool saveToFile(std::string path);
	//
	void copyFrom(Terrain* terrain);
	///
	//
	//-1 means fail
	int getChunkId(sf::Vector2f blockPosition);
private:
	std::vector<Chunk*> m_map;
	std::vector<Coord> m_treeCoord;
	//
	//MAP GENERATION PROCESS
	void createSea(int seed);
	void createLand(int seed);
};

