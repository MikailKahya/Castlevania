#include "base.h"
#include "myUtils.h"

#pragma region Transformation
	void myUtils::ApplyTranslate(const Point2f& translation)
	{
		ApplyTranslate(translation.x, translation.y);
	}
	void myUtils::ApplyTranslate(float x, float y)
	{
		glTranslatef(x, y, 0);
	}

	void myUtils::ApplyRotate(float angle)
	{
		glRotatef(angle, 0, 0, 1);
	}

	void myUtils::ApplyScale(float scaleX, float scaleY)
	{
		glScalef(scaleX, scaleY, 0);
	}
#pragma endregion Transformation

#pragma region Generate
	int myUtils::GenRand(int max)
	{
		return GenRand(0, max);
	}
	int myUtils::GenRand(int min, int max)
	{
		return rand() % (max - min + 1) + min;
	}

	float myUtils::GenRand(float max)
	{
		return GenRand(0.f, max);
	}
	float myUtils::GenRand(float min, float max)
	{
		const float scalar{ powf(10, 2) };
		return rand() % int(max * scalar - min * scalar + 1 * scalar) / scalar + min;
	}

	Color4f myUtils::RGBToColor4f(int r, int g, int b, int a)
	{
		const float maxRGB{ 255 };
		return Color4f{ r / maxRGB, g / maxRGB, b / maxRGB, a / maxRGB };
	}
	Color4f myUtils::HexToColor4f(int hexCode)
	{
		const float r{ float(hexCode >> 4 & 0xFF) / 0xFF };
		const float g{ float(hexCode >> 8 & 0xFF) / 0xFF };
		const float b{ float(hexCode >> 12 & 0xFF) / 0xFF };
		return Color4f{ r, g, b, 1.0f };
	}
#pragma endregion Generate

#pragma region Collision
	bool myUtils::IsCircleInRect(const Rectf& boundingBox, const Circlef& shape)
	{
		const float
			shapeBottom{ shape.center.y - shape.radius },
			shapeTop{ shape.center.y + shape.radius },
			shapeLeft{ shape.center.x - shape.radius },
			shapeRight{ shape.center.x + shape.radius };


		const float
			boundingBottom{ boundingBox.bottom },
			boundingTop{ boundingBox.bottom + boundingBox.height },
			boundingLeft{ boundingBox.left },
			boundingRight{ boundingBox.left + boundingBox.width };

		if (boundingBottom > shapeBottom)
			return false;

		if (boundingTop < shapeTop)
			return false;

		if (boundingLeft > shapeLeft)
			return false;

		if (boundingRight < shapeRight)
			return false;

		return true;
	}
#pragma endregion Collision

