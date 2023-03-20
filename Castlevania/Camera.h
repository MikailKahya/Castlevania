#pragma once
#include <Vector2f.h>

class Camera final
{
public:
	Camera(float width, float height);
	~Camera() {};

	void SetLevelBoundaries(const Rectf& boundary);
	void View(const Point2f& target) const;
	void View(const Rectf& target) const;
	void Draw(const Rectf& target) const;
	void SetZoom(const Vector2f& zoom);

private:
	Point2f Track(const Rectf& target) const;
	void Clamp(Point2f& bottomLeftPos) const;

	float m_Width;
	float m_Height;
	Rectf m_LevelBoundaries;
	Vector2f m_Zoom;
};

