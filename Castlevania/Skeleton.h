#pragma once
#include "Enemy.h"
#include <vector>

class Skeleton : public Enemy
{
public:
	Skeleton();
	virtual ~Skeleton();

	void Die();
private:
	std::vector<Rectf> m_PartSrcVec;
};

