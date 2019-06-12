#include "Villager.h"



Villager::Villager()
{
}


Villager::~Villager()
{
}

void Villager::setPosition(Coord position)
{
	m_position = position;
}

Coord Villager::getPosition()
{
	return m_position;
}

void Villager::setId(int id)
{
	m_id = id;
}

int Villager::getId() const
{
	return m_id;
}

void Villager::setStatistics(float iq, float strenght, float charisma, float religion)
{
	setStatistic(ID_IQ, iq);
	setStatistic(ID_STRENGHT, strenght);
	setStatistic(ID_CHARISMA, charisma);
	setStatistic(ID_RELIGION, religion);
}

void Villager::setStatistic(VillagerStat statistic, float number)
{
	if (statistic == ID_HUNGER) {
		m_hunger = number;
	}
	else if (statistic == ID_EXHAUSTION) {
		m_exhaustion = number;
	}
	else if (statistic == ID_THIRST) {
		m_thirst = number;
	}
	else if (statistic == ID_HEALTH) {
		m_health = number;
	}
	else if (statistic == ID_THIRST) {
		m_thirst = number;
	}
	else if (statistic == ID_STRENGHT) {
		m_strenght = number;
	}
	else if (statistic == ID_IQ) {
		m_iq = number;
	}
	else if (statistic == ID_CHARISMA) {
		m_charisma = number;
	}
	else if (statistic == ID_RELIGION) {
		m_religion = number;
	}

}

float Villager::getStatistic(VillagerStat statistic)
{
	if (statistic == ID_HUNGER) {
		return m_hunger;
	}
	else if (statistic == ID_EXHAUSTION) {
		return m_exhaustion;
	}
	else if (statistic == ID_THIRST) {
		return m_thirst;
	}
	else if (statistic == ID_HEALTH) {
		return m_health;
	}
	else if (statistic == ID_THIRST) {
		return m_thirst;
	}
	else if (statistic == ID_STRENGHT) {
		return m_strenght;
	}
	else if (statistic == ID_IQ) {
		return m_iq;
	}
	else if (statistic == ID_CHARISMA) {
		return m_charisma;
	}
	else if (statistic == ID_RELIGION) {
		return m_religion;
	}
}

bool Villager::checkStatus()
{
	if ((m_hunger <= 0) || (m_thirst <= 0) || (m_exhaustion >= 100) || (m_health <= 0)) return false;
	else return true;
}

void Villager::changeStatistic(VillagerStat statistic, float number)
{
	if (statistic == ID_HUNGER) {
		m_hunger += number;
	}
	else if (statistic == ID_EXHAUSTION) {
		m_exhaustion += number;
	}
	else if (statistic == ID_THIRST) {
		m_thirst += number;
	}
	else if (statistic == ID_HEALTH) {
		m_health += number;
	}
	else if (statistic == ID_THIRST) {
		m_thirst += number;
	}
	else if (statistic == ID_STRENGHT) {
		m_strenght += number;
	}
	else if (statistic == ID_IQ) {
		m_iq += number;
	}
	else if (statistic == ID_CHARISMA) {
		m_charisma += number;
	}
	else if (statistic == ID_RELIGION) {
		m_religion += number;
	}

}

void Villager::checkPriority()
{
	if (m_actualPriority == VillagerPriorities::Priorities::ID_NOTHING)
	{
		//find new priority
		m_actualPriority = m_villagerPriorities.drawLotsActivity();
	}
}

Girl::Girl()
{
}

Girl::~Girl()
{
}

Boy::Boy()
{
}

Boy::~Boy()
{
}

Man::Man()
{
}

Man::~Man()
{
}

Woman::Woman()
{
}

Woman::~Woman()
{
}
