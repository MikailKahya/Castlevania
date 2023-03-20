#pragma once
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update(float elapsedSec) {};
	virtual void Draw() const {};
	
	static int NR_GAMEOBJECTS;
};

