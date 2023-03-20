#pragma once
#include "utils.h"

class RigidBody
{
public:
	RigidBody();
	RigidBody(const Point2f& pivot, float width, float height, const Vector2f& velocity, float mass, bool isDynamic);
	virtual ~RigidBody() = default;
	
	void Update(float elapsedSec, const Rectf& floor);
	void Draw() const;
	Rectf GetHurtBox() const;
	Point2f GetPivot() const;
	Vector2f GetVelocity() const;
	bool IsGrounded() const;
	void SetPosition(const Point2f& pivot);
	void SetVelocity(const Vector2f& velocity);
	
	static const Vector2f GRAVITY;
	static const bool SHOW_HURT_BOX;

protected:
	virtual bool Collision(const Rectf& hitBox);
	virtual bool Collision(std::vector<Point2f>& vertices);
	void CheckGrounded();
	void UpdatePosition(float elapsedSec, const Rectf& floor);
	
	float m_Width;
	float m_Height;
	Point2f m_Pivot;
	Vector2f m_Velocity;
	float m_Mass;
	bool m_IsDynamic;
	bool m_IsGrounded;
	utils::HitInfo m_HitInfo;
};

