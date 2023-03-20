#pragma once
#include "utils.h"
class Texture;

class Sprite
{
public:
	Sprite(Texture* pTexture, const Rectf& srcRect, bool isFlipped = false);
	virtual ~Sprite();

	virtual void Update(float elapsedSec) = 0;
	virtual void Draw() const = 0;
	virtual void Draw(const Point2f& pivot) const;
	virtual void Draw(const Rectf& dstRect) const;
	
	void SetFlip(bool isFlipped);

protected:
	virtual Rectf CalcSrcRect() const = 0;

	Texture* m_pSpriteSheet;
	Rectf m_SrcRect;
	bool m_Flip;
};

