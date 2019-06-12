#include "Familly.h"

Family::Family()
{
}

Family::~Family()
{
}

int Family::getId() const
{
	return m_id;
}

void Family::setId(int Id)
{
	m_id = Id;
}

int Family::getMembersNumber() const
{
	int number = 0;

	/*
	if (m_man != nullptr)
		number++;
	if (m_woman != nullptr)
		number++;
	*/

	number += m_girls.size();
	number += m_boys.size();

	return number;
}

Man* Family::createMan()
{
	if (m_man == nullptr)
	{
		Man* man = new Man();
		m_man = man;
		return man;
	}
	else return nullptr;
}

Woman* Family::createWoman()
{
	if (m_woman == nullptr)
	{
		Woman* woman = new Woman();
		m_woman = woman;
		return woman;
	}
	else return nullptr;
}
