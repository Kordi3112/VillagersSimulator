#include "Village.h"



Village::Village()
{
}


Village::~Village()
{
	for (int i = 0; i < m_families.size(); i++)
	{
		delete m_families[i];
	}
}

void Village::spawnVillager(Villager::VillagerType type)
{
	if (type == Villager::VillagerType::ID_MAN)
	{
		//creating new family with one member
		Family* family = createFamily();
		Man* man = family->createMan();
		//
		float radius = m_random.NextF(m_spawnerRadius * 0.1f, m_spawnerRadius);
		float angle = m_random.NextF(0, 2 * M_PI);
		//
		man->setPosition(Coord(sf::Vector2i(m_spawnerPosition.x + cos(angle) * radius, m_spawnerPosition.y + cos(angle) * radius)));
		//man->

	}
	else if (type == Villager::VillagerType::ID_WOMAN)
	{
		//creating new family with one member
		Family* family = createFamily();
	}
}

Family* Village::createFamily()
{
	Family* family = new Family();

	family->setId(++m_latestFamilyId);

	m_families.push_back(family);

	return family;

}

void Village::setSpawnerPosition(sf::Vector2i position)
{
	m_spawnerPosition = position;
}

sf::Vector2i Village::getSpawnerPosition() const
{
	return m_spawnerPosition;
}

void Village::setSpawnerRadius(float radius)
{
	m_spawnerRadius = radius;
}

float Village::getSpawnerRadius() const
{
	return m_spawnerRadius;
}
