#include "pch.h"
#include "Player.h"
#include <Texture.h>
#include <Avatar.h>
#include <utils.h>
#include <iostream>

Player::Player()
	: m_Hp{ 120 }
	, m_Stamina{ 50 }
	, m_Mana{ 15 }
	, m_State{ State::idle }
	, m_JumpTime{ 0.0f }
	, m_MaxJump{ 0.3f }
{
	Setup();
}

Player::~Player()
{
	delete m_pSprite;
}

#pragma region MainFunctions
void Player::Setup()
{
	SetupSprite();
	SetupRigidBody();
}

void Player::Update(float elapsedSec)
{
	const State startState{ m_State };
	const Vector2f startVelocity{ m_pRigidBody->GetVelocity() };
	HandleInput(elapsedSec);
	UpdateAnimation(elapsedSec, startState, startVelocity);

	const Rectf floor{ -10.0f, -10.0f, 2000.0f, 10.0f };
	UpdatePhysics(elapsedSec, floor);
}

void Player::Draw() const
{
	DrawPlayer();
	DrawBoundingBox();
}
Rectf Player::GetHurtBox() const
{
	return m_pRigidBody->GetHurtBox();
}
#pragma endregion MainFunctions


#pragma region Create
void Player::SetupSprite()
{
	Texture* pTexture = new Texture{ "Shanoa.png" };
	std::vector<Anim> animVec{ CreateAnimations() };
	m_pSprite = new Avatar{ pTexture, animVec };
}

void Player::SetupRigidBody()
{
	const Point2f pivot{ 100.0f, 0.0f };
	const float width{ 35.0f }, height{ 70.0f };
	const float mass{ 30.0f };
	m_pRigidBody = new RigidBody(pivot, width, height, Vector2f{}, mass, false);
}

std::vector<Anim> Player::CreateAnimations() const
{
	std::vector<Anim> animVec{};

	const int fps{ 12 };
	const float frameSize{ 70.0f };
	Point2f topLeft{ 0.0f, 0.0f };

	// insert in order of enum and spritesheet (18 total anims)
	std::vector<int> nrFrames{ 8, 18, 8, 10, 6, 10, 4, 12, 8, 7, 24, 7, 8, 8, 8, 8, 8, 8 };
	std::vector<int> nrCols{   8,  9, 8, 10, 6, 10, 4,  6, 8, 7,  8, 7, 8, 8, 8, 8, 8, 8 };
	std::vector<int> nrRows{   1,  2, 1,  1, 1,  1, 1,  2, 1, 1,  3, 1, 1, 1, 1, 1, 1, 1 };
	std::vector<bool> isLooping{
		true, true, false, false,
		false, false, false, false,
		true, false, false, false,
		false, false, false, false,
		false, false };

	for (size_t index{}; index < nrFrames.size(); ++index)
	{
		Anim animation{ topLeft, frameSize,frameSize, fps,
						nrFrames[index], nrCols[index], nrRows[index],
						isLooping[index] };
		animVec.push_back(animation);
		topLeft.y += frameSize * nrRows[index];
	}

	return animVec;
}
#pragma endregion Create

#pragma region Update
void Player::UpdateAnimation(float elapsedSec, const State& startState, const Vector2f& startVelocity)
{
	TransitionAnimation(startVelocity);
	if (startState != m_State)
	{
		dynamic_cast<Avatar*>(m_pSprite)->SetAnimation(int(m_State));
	}
	m_pSprite->Update(elapsedSec);
}

void Player::UpdatePhysics(float elapsedSec, const Rectf& floor)
{
	m_pRigidBody->Update(elapsedSec, floor);
	if (m_pRigidBody->IsGrounded())
	{
		m_JumpTime = 0.0f;
	}
}

void Player::HandleInput(float elapsedSec)
{
	const Uint8* pKeyStates{ SDL_GetKeyboardState(nullptr) };

	InputState(elapsedSec, pKeyStates);
	InputPhysics(pKeyStates);
}

void Player::InputState(float elapsedSec, const Uint8* pKeyStates)
{
	if (m_pRigidBody->IsGrounded())
	{
		if (pKeyStates[SDL_SCANCODE_A])
		{
			m_State = State::run;
		}
		else if (pKeyStates[SDL_SCANCODE_D])
		{
			m_State = State::run;
		}

		if (pKeyStates[SDL_SCANCODE_S])
		{
			m_State = State::crouch;
		}
	}

	if (pKeyStates[SDL_SCANCODE_W] && m_JumpTime < m_MaxJump)
	{
		m_State = State::jump;
	}
	if (m_State == State::jump)
	{
		m_JumpTime += elapsedSec;
	}

	
}

void Player::InputPhysics(const Uint8* pKeyStates)
{
	Vector2f velocity{ m_pRigidBody->GetVelocity() };
	const float moveSpeed{ 200.0f };
	const float jumpSpeed{ 300.0f };

	if (pKeyStates[SDL_SCANCODE_A])
	{
		velocity.x = -moveSpeed;
		m_pSprite->SetFlip(true);
	}
	else if (pKeyStates[SDL_SCANCODE_D])
	{
		velocity.x = moveSpeed;
		m_pSprite->SetFlip(false);
	}
	else
	{
		velocity.x = 0.0f;
	}

	if (pKeyStates[SDL_SCANCODE_W] && m_JumpTime < m_MaxJump)
	{
		velocity.y = jumpSpeed;
	}

	if (m_State == State::crouch || m_State == State::turn)
	{
		velocity.x = 0;
	}

	m_pRigidBody->SetVelocity(velocity);
}

void Player::TransitionAnimation(const Vector2f& startVelocity)
{
	const Vector2f velocity{ m_pRigidBody->GetVelocity() };
	const Uint8* pKeyStates{ SDL_GetKeyboardState(nullptr) };

	if (velocity.y < 0)
	{
		m_State = State::fall;
	}

	const bool moveNotPressed{ !pKeyStates[SDL_SCANCODE_A] && !pKeyStates[SDL_SCANCODE_D] };
	if (m_State == State::run && startVelocity.x == velocity.x * -1) // turn if sudden movement change
	{
		m_State = State::turn;
	}
	else 
	if (m_State == State::run && moveNotPressed) // stop if not moving any direction
	{
		m_State = State::stopRun;
	}

	

	// transition animation for end of loop anims
	if (dynamic_cast<Avatar*>(m_pSprite)->IsLastFrame())
	{
		switch (m_State)
		{
		case Player::State::startRun:
			m_State = State::run;
			break;
		case Player::State::stopRun:
			m_State = State::idle;
			break;
		case Player::State::turn:
			m_State = State::run;
			break;
		}
	}

	const bool isIdle{ velocity.x == 0 && velocity.y == 0 && m_State != State::crouch && m_State != State::turn && m_State != State::stopRun };
	if (isIdle)
	{
		m_State = State::idle;
	}
}
#pragma endregion Update

#pragma region Draw
void Player::DrawPlayer() const
{
	const Rectf hurtBox{ m_pRigidBody->GetHurtBox() };
	const float scale{ 1.5f };
	const float w{ hurtBox.width * scale * 2 };
	const float h{ hurtBox.height * scale };
	const float x{ hurtBox.left - hurtBox.width  };
	const float y{ hurtBox.bottom };
	const Rectf dstRect{ x, y, w, h };
	m_pSprite->Draw(dstRect);
}

void Player::DrawBoundingBox() const
{
	const Color4f color{ 0.0f, 1.0f, 0.0f, 1.0f };
	utils::SetColor(color);
	m_pRigidBody->Draw();
}
#pragma endregion Draw

#pragma region Setters

#pragma endregion Setters

#pragma region Getters
bool Player::IsDead()
{
	return (m_Hp == 0) ? true : false;
}
#pragma endregion Getters

#pragma region Helpers
bool Player::CheckHit(Rectf hitBox) const
{
	return false;
}
#pragma endregion Helpers

