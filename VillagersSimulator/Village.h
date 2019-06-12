#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "Familly.h"
#include "Building.h"
#include "Villager.h"


class Village
{
public:
	//
	Village();
	~Village();
	//
	void spawnVillager(Villager::VillagerType type); //spawning Man or Woman  
	//
	void convertBoyToMan();
	void convertGirlToWoman();

	//
	void addFamily(Family family);
	Family* createFamily(); //returns id;
	//
	void setSpawnerPosition(sf::Vector2i position);
	sf::Vector2i getSpawnerPosition() const;
	//
	void setSpawnerRadius(float radius);
	float getSpawnerRadius() const;

	///BUILDINGS
	Building* createBuilding();

	///DRAW
	//void draw(sf::RenderWindow& window, sf::FloatRect viewPort, sf::Vector2f cameraPos, float zoom);
	///REFRESH
	void refresh();
	//Villagers

	//Buili
private:
	//
	Random m_random;
	//
	std::vector<Family*> m_families;
	int m_latestFamilyId = -1;
	std::vector<Building*> m_buildings;
	//
	sf::Vector2i m_spawnerPosition; //
	float m_spawnerRadius;
};
