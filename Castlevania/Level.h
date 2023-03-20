#pragma once
#include <vector>
class Room;

class Level final
{
public:
	Level();
	~Level();
private:
	std::vector<Room*> m_pRoomVec;
};

