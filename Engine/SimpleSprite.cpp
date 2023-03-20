#include "SimpleSprite.h"
#include "Texture.h"

SimpleSprite::SimpleSprite(Texture* pTexture, int cols, int rows, int col, int row)
	: Sprite{ pTexture, Rectf{} }
	, m_NrCols{ cols }
	, m_NrRows{ rows }
	, m_Col{ col }
	, m_Row{ row }
{
	m_SrcRect = CalcSrcRect();
}

void SimpleSprite::SetCol(int col)
{
	m_Col = col;
	m_SrcRect = CalcSrcRect();
}

void SimpleSprite::SetRow(int row)
{
	m_Row = row;
	m_SrcRect = CalcSrcRect();
}

Rectf SimpleSprite::CalcSrcRect() const
{
	const float width{ m_pSpriteSheet->GetWidth() / m_NrCols };
	const float height{ m_pSpriteSheet->GetHeight() / m_NrRows };
	const float x{ width * m_Col };
	const float y{ height * m_Row };

	return Rectf{ x, y, width, height };
}