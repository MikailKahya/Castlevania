#pragma once
#include "Sprite.h"

class SimpleSprite : public Sprite
{
public:
	SimpleSprite(Texture* pTexture, int rows, int cols, int row = 0, int col = 0);
	
	void SetCol(int col);
	void SetRow(int row);

	virtual void Update(float elapsedSec) override {};

private:
	virtual Rectf CalcSrcRect() const override;

	int m_NrCols;
	int m_NrRows;
	int m_Col;
	int m_Row;
};