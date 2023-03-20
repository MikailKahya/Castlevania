#pragma once
#include "Room.h"
class Enemy;

class Corridor : public Room
{
public:
	
	Corridor(const std::string& svgPath, Type tileType);
	Corridor(const std::string& svgPath, const Rectf& bounds, Type tileType);
	virtual ~Corridor() {};

private:
	std::vector<Enemy*> m_pEnemyVec;
	std::vector<Point2f> m_pChestVec;
};

