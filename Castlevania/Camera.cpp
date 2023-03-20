#include "pch.h"
#include "Camera.h"
#include <algorithm>
#include <utils.h>
#include <iostream>

Camera::Camera(float width, float height)
	: m_Width{ width }
	, m_Height{ height }
	, m_LevelBoundaries{ Rectf{0.0f, 0.0f, width, height} }
	, m_Zoom{ Vector2f{1.0f, 1.0f} }
{
}

void Camera::SetLevelBoundaries(const Rectf& boundary)
{
	m_LevelBoundaries = boundary;
}

void Camera::View(const Point2f& target) const
{
	Point2f tracker{ target };
	Clamp(tracker);
	glTranslatef(-tracker.x, -tracker.y, 0.0f);
	glScalef(m_Zoom.x, m_Zoom.y, 0.0f);
}

void Camera::View(const Rectf& target) const
{
	const Point2f tracker{ Track(target) };
	View(tracker);
}

void Camera::Draw(const Rectf& target) const
{
	const Point2f tracker{ Track(target) };
	const Rectf camera{ tracker.x - m_Width / 2, tracker.y - m_Height / 2, m_Width, m_Height };
	utils::SetColor(Color4f{ 0.0f, 1.0f, 0.0f, 1.0f });
	utils::DrawRect(camera);
}

void Camera::SetZoom(const Vector2f& zoom)
{
	m_Zoom = zoom;
	m_Width /= m_Zoom.x;
	m_Height /= m_Zoom.y;
}


Point2f Camera::Track(const Rectf& target) const
{
	const float x{ target.left - m_Width / 2 }, y{ target.bottom - m_Height / 2 };
	const float w{ target.width }, h{ target.height };
	

	return Point2f{ (x - w / 2) * m_Zoom.x, (y - h / 2) * m_Zoom.y };
}

void Camera::Clamp(Point2f& bottomLeftPos) const
{
	// use standard min and max
	const float minX{ m_LevelBoundaries.left };
	const float maxX{ minX + m_LevelBoundaries.width };
	const float minY{ m_LevelBoundaries.bottom };
	const float maxY{ minY + m_LevelBoundaries.height };


	// check clamping top and right
	bottomLeftPos.x = std::min(maxX, bottomLeftPos.x);
	bottomLeftPos.y = std::min(maxY, bottomLeftPos.y);

	// check clamping bottom and left
	bottomLeftPos.x = std::max(minX, bottomLeftPos.x);
	bottomLeftPos.y = std::max(minY, bottomLeftPos.y);

	std::cout << minX;
	std::cout << bottomLeftPos << std::endl;
}
