#pragma once
#include "GameObject.h"

class RigidBody;
class Sprite;

class Enemy: public GameObject
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void Update(float elapsedSec) override;
	virtual void Draw() const override;

protected:
	void ApplyPhysics();

	int m_Hp;
	RigidBody* m_pRigidBody;
	Sprite* m_pSprite;
};

