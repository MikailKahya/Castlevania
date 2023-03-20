#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite(Texture* pTexture, const Rectf& srcRect, bool isFlipped)
	: m_pSpriteSheet{ pTexture }
	, m_SrcRect{ srcRect }
	, m_Flip{ isFlipped }
{
}

Sprite::~Sprite()
{
	delete m_pSpriteSheet;
}

void Sprite::Draw(const Point2f& pivot) const
{
	Draw(Rectf{ pivot.x - m_SrcRect.width / 2, pivot.y, m_SrcRect.width, m_SrcRect.height });
}

void Sprite::Draw(const Rectf& dstRect) const
{
	float scaleX{ dstRect.width / m_SrcRect.width };
	const float scaleY{ dstRect.height / m_SrcRect.height };

	if (m_Flip) scaleX *= -1;

	glPushMatrix();
	glTranslatef(dstRect.left, dstRect.bottom, 0.0f);
	glScalef(scaleX, scaleY, 0.0f);
	if (m_Flip)
	{
		glTranslatef(-m_SrcRect.width, 0.0f, 0.0f);
	}

	m_pSpriteSheet->Draw(Point2f{}, m_SrcRect);
	glPopMatrix();
}

void Sprite::SetFlip(bool isFlipped)
{
	m_Flip = isFlipped;
}