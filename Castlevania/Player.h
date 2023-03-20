#pragma once
#include <myStructs.h>
#include <Vector2f.h>
#include <vector>
#include <RigidBody.h>
#include "GameObject.h"

class Sprite;

class Player : public GameObject
{
public:
	Player();
	virtual ~Player() override;

	void Update(float elapsedSec) override;
	void Draw() const override;
	Rectf GetHurtBox() const;

private:
	enum class State
	{
		idle,
		run,
		turn,
		startRun,
		stopRun,
		jump,
		fall,
		crouch,
		powerup,
		dodge,
		death,
		slide,
		attackLeft,
		attackRight,
		attackCrouchLeft,
		attackCrouchRight,
		attackAirLeft,
		attackAirRight
	};

	void Setup();
	void SetupSprite();
	void SetupRigidBody();
	std::vector<Anim> CreateAnimations() const;

	void UpdateAnimation(float elapsedSec, const State& startState, const Vector2f& startVelocity);
	void UpdatePhysics(float elapsedSec, const Rectf& floor);

	void DrawPlayer() const;
	void DrawBoundingBox() const;

	bool CheckHit(Rectf hitBox) const;
	bool IsDead();
	void IsIdle();
	void HandleInput(float elapsedSec);
	void InputState(float elapsedSec, const Uint8* pKeyStates);
	void InputPhysics(const Uint8* pKeyStates);
	void TransitionAnimation(const Vector2f& startVelocity);
	

	int m_Hp;
	int m_Stamina;
	int m_Mana;
	State m_State;
	float m_JumpTime;
	const float m_MaxJump;

	Sprite* m_pSprite;
	RigidBody* m_pRigidBody;
};

