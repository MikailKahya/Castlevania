#include "Avatar.h"
#include "Texture.h"

Avatar::Avatar(Texture* pTexture, std::vector<Anim>& animVec, Anim& anim)
	: Sprite(pTexture, Rectf{})
	, m_AnimVec{ animVec }
	, m_CurrentAnim{ anim }
	, m_AccumTime{ 0.0f }
{
	m_SrcRect = CalcSrcRect();
}

Avatar::Avatar(Texture* pTexture, std::vector<Anim>& animVec, int currentAnim)
	: Avatar( pTexture, animVec, animVec[currentAnim] )
{
}
	
void Avatar::Update(float elapsedSec)
{
	if (!m_CurrentAnim.loop && IsLastFrame()) return;

	m_AccumTime += elapsedSec;
	if (m_AccumTime < m_CurrentAnim.frameTime) return;
	++m_CurrentAnim.currentFrame;

	m_CurrentAnim.currentFrame %= m_CurrentAnim.nrFrames;
	m_AccumTime -= m_CurrentAnim.frameTime;
	m_SrcRect = CalcSrcRect();
}

Rectf Avatar::CalcSrcRect() const
{
	const float row{ float(GetRow()) };
	const float col{ float(GetCol()) };
	const float x{ m_CurrentAnim.startPos.x };
	const float y{ m_CurrentAnim.startPos.y };
	const float width{ m_CurrentAnim.frameWidth };
	const float height{ m_CurrentAnim.frameHeight };

	return Rectf{ x + col * width, y + row * height, width, height };
}

int Avatar::GetRow() const
{
	return m_CurrentAnim.currentFrame / m_CurrentAnim.cols + 1;
}

int Avatar::GetCol() const
{
	return m_CurrentAnim.currentFrame % m_CurrentAnim.cols;
}

void Avatar::SetAnimation(int index)
{
	m_CurrentAnim = m_AnimVec[index];
	m_AccumTime = 0;
	m_SrcRect = CalcSrcRect();
}

bool Avatar::IsLastFrame()
{
	return (m_CurrentAnim.currentFrame == m_CurrentAnim.nrFrames - 1) ? true : false;
}
