#pragma once
#include "myStructs.h"

namespace myUtils
{
#pragma region Transformation
	void ApplyTranslate(const Point2f& translation);
	void ApplyTranslate(float x, float y);
	void ApplyRotate(float angle);
	void ApplyScale(float scaleX, float scaleY);
#pragma region EndTransformation

#pragma region Generate
	int GenRand(int max);
	int GenRand(int min, int max);
	float GenRand(float max);
	float GenRand(float min, float max);

	Color4f RGBToColor4f(int r, int g, int b, int a = 255);
	Color4f HexToColor4f(int hexCode);
#pragma endregion Generate

#pragma region Collision
	bool IsCircleInRect(const Rectf& boundingBox, const Circlef& shape);
#pragma endregion Collision

#pragma region JSON
#pragma endregion JSON
}