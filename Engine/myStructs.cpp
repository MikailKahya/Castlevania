#include "myStructs.h"
#include "myUtils.h"
#include "Texture.h"

Transform::Transform(const Point2f& translation, float angle, float scaleX, float scaleY) :
	translate{ translation },
	angle{ angle },
	scaleX{ scaleX },
	scaleY{ scaleY }
{
}

Transform::Transform(float translateX, float translateY, float angle, float scaleX, float scaleY) :
	Transform( Point2f{translateX, translateY}, angle, scaleX, scaleY )
{
}

void Transform::ApplyMatrix(Type transformType) const
{
	switch (transformType)
	{
	case Transform::Type::RTS:
		myUtils::ApplyRotate(angle);
		myUtils::ApplyTranslate(translate);
		myUtils::ApplyScale(scaleX, scaleY);
		break;
	case Transform::Type::RT:
		myUtils::ApplyRotate(angle);
		myUtils::ApplyTranslate(translate);
		break;
	case Transform::Type::TRS:
		myUtils::ApplyTranslate(translate);
		myUtils::ApplyRotate(angle);
		myUtils::ApplyScale(scaleX, scaleY);
		break;
	case Transform::Type::TR:
		myUtils::ApplyTranslate(translate);
		myUtils::ApplyRotate(angle);
		break;
	}
}

Anim::Anim(const Point2f& startPos, float frameWidth, float frameHeight, int fps, int nrFrames, int cols, int rows, bool loop)
	: startPos{ startPos }
	, frameWidth{ frameWidth }
	, frameHeight{ frameHeight }
	, frameTime{ 1.0f / fps }
	, currentFrame{ 0 }
	, nrFrames{ nrFrames }
	, cols{ cols }
	, rows{ rows }
	, loop{ loop }
{
}

Anim::Anim(const Point2f& startPos, float frameWidth, float frameHeight, int fps, int nrFrames, bool loop)
	: Anim(startPos, frameWidth, frameHeight, fps, nrFrames, nrFrames, 1, loop)
{
}

Anim::Anim(Texture* pTexture, const Point2f& startPos, int fps, int nrFrames, int cols, int rows, bool loop)
	: Anim( startPos, 0.0f, 0.0f, fps, nrFrames, cols, rows, loop)
{
	frameWidth = pTexture->GetWidth() / cols;
	frameHeight = pTexture->GetHeight() / rows;
}
