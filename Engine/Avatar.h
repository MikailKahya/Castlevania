#pragma once
#include "myStructs.h"
#include "Sprite.h"
#include <vector>

class Avatar :  public Sprite
{
public:
	Avatar(Texture* pTexture, std::vector<Anim>& animVec, Anim& anim);
	Avatar(Texture* pTexture, std::vector<Anim>& animVec, int currentAnim = 0);

	void Update(float elapsedSec);
	void SetAnimation(int index);
	bool IsLastFrame();

private:
	virtual Rectf CalcSrcRect() const override;
	int GetRow() const;
	int GetCol() const;

	std::vector<Anim> m_AnimVec;
	Anim m_CurrentAnim;
	float m_AccumTime;
};

