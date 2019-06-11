#pragma once
#include "Coord.h"


enum VillagerStat {
	ID_HUNGER,
	ID_EXHAUSTION,
	ID_THIRST,
	ID_HEALTH,
	ID_STRENGHT,
	ID_IQ,
	ID_CHARISMA,
	ID_RELIGION,
};

class Villager
{
public:

	Villager();
	virtual ~Villager() = 0;
	void setPosition(Coord position);
	Coord getPosition();
	void setStatistics(float iq, float strenght, float charisma, float religion, bool male);
	//
	void setStatistic(VillagerStat statistic, float number);
	float getStatistic(VillagerStat statistic);
	//
	bool checkStatus();//check if villager is still alive
	void changeStatistic(VillagerStat statistic, float number);
	//

protected:
	Coord m_position; //position on map 
	bool  m_isMale;//true-Male false-Female
	float m_hunger = 100;
	float m_exhaustion = 0;
	float m_thirst = 100; //water
	float m_health = 100;
	float m_iq;
	float m_strenght;
	float m_charisma;
	float m_religion;
};

