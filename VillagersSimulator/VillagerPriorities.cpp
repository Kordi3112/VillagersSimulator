#include "VillagerPriorities.h"

VillagerPriorities::VillagerPriorities()
{
	//creating points
	for (int x = 0; x < PRIORITIES_NUMBER; x++)
	{
		m_priorityPoints.push_back(sf::Vector2f(x, 0));
	}

	//
	m_priorityChances.setDefault();
	//
	
}

VillagerPriorities::~VillagerPriorities()
{
}

VillagerPriorities::Priorities VillagerPriorities::drawLotsActivity()
{
	//counting fate value
	float fate_eating = getPriorityValue(ID_EATING) * m_priorityChances.eating;
	float fate_drinking = getPriorityValue(ID_DRINKING) * m_priorityChances.drinking;
	float fate_relaxing = getPriorityValue(ID_RELAXING) * m_priorityChances.relaxing;
	float fate_heating = getPriorityValue(ID_HEATING) * m_priorityChances.heating;
	float fate_working = getPriorityValue(ID_WORKING) * m_priorityChances.working;
	float fate_loving = getPriorityValue(ID_LOVING) * m_priorityChances.loving;
	float fate_makingFamily = getPriorityValue(ID_MAKINGFAMILY) * m_priorityChances.makingFamily;
	float fate_learning = getPriorityValue(ID_LEARNING) * m_priorityChances.learning;
	float fate_revolting = getPriorityValue(ID_REVOLTING) * m_priorityChances.revolting;
	float fate_discovering = getPriorityValue(ID_DISCOVERING) * m_priorityChances.discovering;
	float fate_raging = getPriorityValue(ID_RAGING) * m_priorityChances.raging;
	//
	float sum = fate_eating + fate_drinking + fate_relaxing + fate_heating + fate_working + fate_loving + fate_makingFamily + fate_learning + fate_revolting + fate_discovering + fate_raging;

	float random = m_random.NextF(0, sum);
	std::cout << "SUM: " << sum << "random: " << random << "Stuff: "<< getPriorityValue(ID_EATING) << std::endl;

	float reached = fate_eating;

	if (random < reached)
		return Priorities::ID_EATING;
	else reached += fate_drinking;

	if(random < reached)
		return Priorities::ID_DRINKING;
	else reached += fate_relaxing;

	if (random < reached)
		return Priorities::ID_RELAXING;
	else reached += fate_heating;

	if (random < reached)
		return Priorities::ID_HEATING;
	else reached += fate_working;

	if (random < reached)
		return Priorities::ID_WORKING;
	else reached += fate_loving;

	if (random < reached)
		return Priorities::ID_LOVING;
	else reached += fate_makingFamily;

	if (random < reached)
		return Priorities::ID_MAKINGFAMILY;
	else reached += fate_learning;

	if (random < reached)
		return Priorities::ID_LEARNING;
	else reached += fate_revolting;

	if (random < reached)
		return Priorities::ID_REVOLTING;
	else reached += fate_discovering;

	if (random < reached)
		return Priorities::ID_DISCOVERING;
	else reached += fate_raging;

	if (random < reached)
		return Priorities::ID_RAGING;
	else return Priorities::ID_NOTHING;
}

int VillagerPriorities::getPriorityId(Priorities prioryty) const
{
	return (int)prioryty;
}

float VillagerPriorities::getPriorityValue(Priorities prioryty) const
{
	return getPriorityValueById(getPriorityId(prioryty));
}

float VillagerPriorities::getPriorityValueById(int id) const
{
	if (id < 0 || id >= m_priorityPoints.size())
		return 0.f;

	else return m_priorityPoints[id].y;
}

void VillagerPriorities::addPoints(Priorities priority, float value)
{
	if (priority == Priorities::ID_NOTHING)
		return;

	for (int i = 0; i < m_priorityPoints.size(); i++)
	{
		if (i == getPriorityId(priority))
		{
			m_priorityPoints[i].y += value;
		}
		else
		{
			m_priorityPoints[i].y -= value / (m_priorityPoints.size() - 1);
		}
	}

	//check
	correctIfOutOfRange();
}

void VillagerPriorities::addPoints(int priority, float value)
{
	if (priority < 0 || priority >= m_priorityPoints.size())
		return;

	addPoints((Priorities)priority, value);
}

void VillagerPriorities::setPriorityChances(PrioritiesChanses priorityChanses)
{
	m_priorityChances = priorityChanses;
}

void VillagerPriorities::equalDistribution()
{
	for (int i = 0; i < m_priorityPoints.size(); i++)
	{
		m_priorityPoints[i].y = POINTS_SUM / m_priorityPoints.size();
	}
}

void VillagerPriorities::addValue(Priorities priority, float value)
{
	if (priority == Priorities::ID_NOTHING)
		return;

	m_priorityPoints[getPriorityId(priority)].y + value;
}

void VillagerPriorities::correctIfOutOfRange()
{
	//check if all variables are in range
	for (int i = 0; i < m_priorityPoints.size(); i++)
	{
		if (m_priorityPoints[i].y < 0.0f)
		{
			//too low
			addPoints(i, -m_priorityPoints[i].y);
			correctIfOutOfRange();
		}
		else if (m_priorityPoints[i].y > 100.0f)
		{
			//too lot
			addPoints(i, m_priorityPoints[i].y - 100.0f);
			correctIfOutOfRange();
		}
	}

	//everything is ok
}

void PrioritiesChanses::setDefault()
{
	eating = 1.f;
	drinking = 1.f;
	relaxing = 1.f;
	working = 0.8f;
	heating = 1.0f;
	loving = 0.5f;
	makingFamily = 0.5f;
	learning = 0.5f;
	revolting = 0.3f;
	discovering = 0.2f;
	raging = 0.1f;
}
