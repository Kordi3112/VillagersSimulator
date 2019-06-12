#pragma once
#include "Coord.h"
#include "VillagerPriorities.h"

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

///=////////////////////////////////////////////////
//  Villager
///=////////////////////////////////////////////////





class Villager
{
public:

	///
	enum VillagerType
	{
		ID_BOY,
		ID_GIRL,
		ID_MAN,
		ID_WOMAN,
	};

	///
	//
	Villager();
	virtual ~Villager() = 0;
	///
	//virtual VillagerType getType() = 0;
	///
	void setPosition(Coord position);
	Coord getPosition();
	//
	void setId(int id);
	int getId() const;
	//
	void setStatistics(float iq, float strenght, float charisma, float religion);
	//
	void setStatistic(VillagerStat statistic, float number);
	float getStatistic(VillagerStat statistic);
	//
	bool checkStatus();//check if villager is still alive
	void changeStatistic(VillagerStat statistic, float number);
	///CHECK
	void checkPriority();
	///PRIORITIES DOING 

	///FUNCIONALITY
	void kill();
	//
	
protected:
	//VillagerPriorities
	VillagerPriorities m_villagerPriorities;
	VillagerPriorities::Priorities m_actualPriority = VillagerPriorities::Priorities::ID_NOTHING;
	//
	int m_id;
	//
	Coord m_position; //position on map 
	//Stats
	float m_hunger = 100;
	float m_exhaustion = 0;
	float m_thirst = 100; //water
	float m_health = 100;
	float m_iq;
	float m_strenght;
	float m_charisma;
	float m_religion;
};

///=////////////////////////////////////////////////
//  GIRL
///=////////////////////////////////////////////////

class Girl : public Villager
{
public:
	Girl();
	~Girl();
	///VIRTUALS

	///
private:

};

///=////////////////////////////////////////////////
//  BOY
///=////////////////////////////////////////////////

class Boy : public Villager
{
public:
	Boy();
	~Boy();
private:

};


///=////////////////////////////////////////////////
//  MEN
///=////////////////////////////////////////////////

class Man : public Villager
{
public:
	Man();
	~Man();
private:

};



///=////////////////////////////////////////////////
//  WOMAN
///=////////////////////////////////////////////////

class Woman : public Villager
{
public:
	Woman();
	~Woman();
private:

};