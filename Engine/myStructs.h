#pragma once
#include "structs.h"

class Texture;

struct Transform
{
	enum class Type
	{
		RTS,
		RT,
		TRS,
		TR
	};

	Transform(const Point2f& translation, float angle = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f);
	Transform(float translateX, float translateY, float angle = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f);

	Point2f translate;
	float angle;
	float scaleX;
	float scaleY;

	void ApplyMatrix(Type transformType) const;
};

struct Anim
{
	Anim(const Point2f& startPos, float frameWidth, float frameHeight, int fps, int nrFrames, int cols, int rows, bool loop = true);
	Anim(const Point2f& startPos, float frameWidth, float frameHeight, int fps, int nrFrames, bool loop = true);
	Anim(Texture* pTexture, const Point2f& startPos, int fps, int nrFrames, int cols, int rows, bool loop = true);

	Point2f startPos;
	float frameWidth;
	float frameHeight;
	float frameTime;
	int currentFrame;
	int nrFrames;
	int cols;
	int rows;
	bool loop;
};
