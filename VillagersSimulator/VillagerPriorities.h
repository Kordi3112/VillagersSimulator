#pragma once
#include <vector>
#include "Random.h"
#include <SFML/Graphics.hpp>
#include <iostream>

//chance to make an activity, for 100 points
struct PrioritiesChanses
{
	float eating;
	float drinking;
	float relaxing;
	float working;
	float heating;
	float loving;
	float makingFamily;
	float learning;
	float revolting;
	float discovering;
	float raging;

	void setDefault();
};


//shows whats is the most important to villager
class VillagerPriorities
{
public:
	///
	enum Priorities
	{
		ID_NOTHING = -1, //returns when error
		ID_EATING = 0,
		ID_DRINKING = 1,
		ID_RELAXING, //to refiil energy
		ID_WORKING, //helping the village
		ID_HEATING,  //
		ID_LOVING, //looking for love
		ID_MAKINGFAMILY,//making children
		ID_LEARNING, //increase an intelect
		ID_REVOLTING, //increase chance to split village, some people moving and making their own village
		ID_DISCOVERING, //searching terrains around village
		ID_RAGING, //tendence to make strange thinks
	};

	const int PRIORITIES_NUMBER = 11;
	const float POINTS_SUM = 100.0f;
	///
	VillagerPriorities();
	~VillagerPriorities();

	///
	Priorities drawLotsActivity();
	///GET
	int getPriorityId(Priorities prioryty) const;
	float getPriorityValue(Priorities prioryty) const;
	float getPriorityValueById(int id) const;

	///SET
	void addPoints(Priorities priority, float value);
	void addPoints(int priority, float value);
	void setPriorityChances(PrioritiesChanses priorityChanses);
	///MAKING DISTRIBUTION
	void equalDistribution();

	///
private:
	//
	void addValue(Priorities priority, float value);
	//
	void correctIfOutOfRange();
	//
	std::vector<sf::Vector2f> m_priorityPoints;
	//
	PrioritiesChanses m_priorityChances;
	//
	Random m_random = Random();
	/*
	float m_level_eating;
	float m_level_drinking;
	float m_level_relaxing;
	float m_level_working;
	float m_level_loving;
	float m_level_makingfamilly;
	float m_level_teaching;
	float m_level_revolting;
	float m_level_discovery;
	float m_level_madness;
	*/
	//
};

