#include "RigidBody.h"

const Vector2f RigidBody::GRAVITY = Vector2f{0.0f, -981.0f };
const bool RigidBody::SHOW_HURT_BOX = true;

RigidBody::RigidBody()
	: RigidBody(Point2f{ 0.0f, 0.0f }, 0.0f, 0.0f, Vector2f{ 0.0f, 0.0f }, 0.0f, false)
{
}

RigidBody::RigidBody(const Point2f& pivot, float width, float height, const Vector2f& velocity, float mass, bool isDynamic)
	: m_Pivot{ pivot }
	, m_Width{ width }
	, m_Height{ height }
	, m_Velocity{ velocity }
	, m_Mass{ mass }
	, m_IsDynamic{ isDynamic }
	, m_HitInfo{ utils::HitInfo{} }
	, m_IsGrounded{ false }
{
}

void RigidBody::Update(float elapsedSec, const Rectf& floor)
{
	m_Velocity += GRAVITY * elapsedSec;
	UpdatePosition(elapsedSec, floor);
	CheckGrounded();
}

void RigidBody::Draw() const
{
	if (!RigidBody::SHOW_HURT_BOX) return;
	utils::DrawRect(GetHurtBox());
}

Rectf RigidBody::GetHurtBox() const
{
	const float x{ m_Pivot.x - m_Width / 2 };
	const float y{ m_Pivot.y };

	return Rectf{ x, y, m_Width, m_Height };
}

Point2f RigidBody::GetPivot() const
{
	return m_Pivot;
}

Vector2f RigidBody::GetVelocity() const
{
	return m_Velocity;
}

bool RigidBody::Collision(const Rectf& hitBox)
{
	// get vertices of a rect
	std::vector<Point2f> vertices{};
	const float h{ hitBox.height };
	const float w{ hitBox.width };
	const float x{ hitBox.left };
	const float y{ hitBox.bottom };

	vertices.push_back(Point2f{ x, y });
	vertices.push_back(Point2f{ x + w, y });
	vertices.push_back(Point2f{ x + w, y + h });
	vertices.push_back(Point2f{ x, y + h });

	return Collision(vertices);
}

bool RigidBody::Collision(std::vector<Point2f>& vertices)
{
	// raycast for groundcheck
	const Point2f rayP1{ m_Pivot.x, m_Pivot.y + m_Height };
	const Point2f rayP2{ m_Pivot.x, m_Pivot.y };
	
	const bool isHit{ utils::Raycast(vertices, rayP1, rayP2, m_HitInfo) };
	if(!isHit) m_HitInfo = utils::HitInfo{};
	
	return isHit;
}

void RigidBody::CheckGrounded()
{
	const float episolon{ 0.005f };
	
	const float xDistance{ m_Pivot.x - m_HitInfo.intersectPoint.x };
	const float yDistance{ m_Pivot.y - m_HitInfo.intersectPoint.y };
	
	m_IsGrounded = false;

	if (xDistance > episolon) return;
	if (yDistance > episolon) return;
	
	m_Velocity.y = 0;
	m_IsGrounded = true;
}

void RigidBody::UpdatePosition(float elapsedSec, const Rectf& floor)
{
	m_Pivot += m_Velocity * elapsedSec;
	if (Collision(floor))
	{
		m_Pivot = m_HitInfo.intersectPoint;
	}
}

bool RigidBody::IsGrounded() const
{
	return m_IsGrounded;
}

void RigidBody::SetPosition(const Point2f& pivot)
{
	m_Pivot = pivot;
}

void RigidBody::SetVelocity(const Vector2f& velocity)
{
	m_Velocity = velocity;
}
