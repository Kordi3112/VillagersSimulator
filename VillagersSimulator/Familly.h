#pragma once
#include "Villager.h"
#include <vector>

class Family
{
public:
	Family();
	~Family();
	//
	int getId() const;
	void setId(int Id);
	int getMembersNumber() const;
	//
	bool addFamilyMember(Man* man);
	bool addFamilyMember(Woman* woman);

	Man* createMan();
	Woman* createWoman();
	//
	void makeNewChild(Villager::VillagerType type);
private:
	int m_familyHouseId;
	//
	Man* m_man = nullptr;
	Woman* m_woman = nullptr;
	//CHILDREN
	std::vector<Girl*> m_girls;
	std::vector<Boy*> m_boys;
	//
	int m_id;
};

