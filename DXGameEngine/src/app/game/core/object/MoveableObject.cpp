#include "MoveableObject.h"

//==============================================================================
#pragma region // Physic object
//==============================================================================

GameCore::PhysicObject::PhysicObject()
{
    m_elastic = 0.0f;
    m_friction = 0.0f;
}

GameCore::PhysicObject::PhysicObject(const PhysicObject& clone) : ObjectBase(clone)
{
    m_elastic = clone.m_elastic;
    m_friction = clone.m_friction;
    m_mass = clone.m_mass;
}

GameCore::PhysicObject::~PhysicObject()
{

}

void GameCore::PhysicObject::SetElastic(float elastic) {
    m_elastic = elastic;
}

void GameCore::PhysicObject::SetFriction(float friction) {
    m_friction = friction;
}

void GameCore::PhysicObject::SetMass(float mass) {
    m_mass = mass;
}

float GameCore::PhysicObject::GetElastic() {
    return m_elastic;
}

float GameCore::PhysicObject::GetFriction() {
    return m_friction;
}

float GameCore::PhysicObject::GetMass() {
    return m_mass;
}

//==============================================================================
#pragma endregion // Physic object
//==============================================================================


//==============================================================================
#pragma region // Move able character
//==============================================================================

GameCore::MoveableObject::MoveableObject()
{
    m_haveSpeedLimit = false;
}

GameCore::MoveableObject::MoveableObject(const MoveableObject& clone) : PhysicObject(clone)
{
    m_velocity = clone.m_velocity;
    m_acceleration = clone.m_acceleration;

    m_maxSpeed = clone.m_maxSpeed;
    m_minSpeed = clone.m_minSpeed;
    m_haveSpeedLimit = clone.m_haveSpeedLimit;
}

GameCore::MoveableObject::~MoveableObject()
{
}

void GameCore::MoveableObject::SetVelocity(const hkVector2F& veloc)
{
    m_velocity = veloc;
}

void GameCore::MoveableObject::SetAcceleration(const hkVector2F& acc)
{
    m_acceleration = acc;
}

void GameCore::MoveableObject::SetSpeedLimit(hkVector2F min, hkVector2F max)
{
    m_maxSpeed = max;
    m_minSpeed = min;

    if (m_maxSpeed.x < 0) m_maxSpeed.x -= m_maxSpeed.x;
    if (m_maxSpeed.y < 0) m_maxSpeed.y -= m_maxSpeed.y;

    if (m_minSpeed.x < 0) m_minSpeed.x -= m_minSpeed.x;
    if (m_minSpeed.y < 0) m_minSpeed.y -= m_minSpeed.y;

    EnableSpeedLimit(true);
}

hkVector2F GameCore::MoveableObject::GetVelocity()
{
    return m_velocity;
}

hkVector2F GameCore::MoveableObject::GetAcceleration()
{
    return m_acceleration;
}

void GameCore::MoveableObject::ApplyForce(const hkVector2F& force)
{
    m_acceleration += (force / m_mass);
}

void GameCore::MoveableObject::EnableSpeedLimit(bool speedLimit)
{
    m_haveSpeedLimit = speedLimit;
}

bool GameCore::MoveableObject::HaveSpeedLimit()
{
    return m_haveSpeedLimit;
}

//---------------------------------------------------------------------------
// INHERIT METHOD
void GameCore::MoveableObject::Update(float timeStep)
{
    // Change position according to 
    m_position += (m_velocity + m_acceleration * timeStep * 0.5f) * timeStep;

    // Change velocity
    m_velocity += m_acceleration * timeStep;

    if (m_velocity < m_minSpeed)
    {
        m_velocity.Normalize();
        m_velocity *= m_minSpeed.Magnitude();
    }
    else if (m_velocity > m_maxSpeed)
    {
        m_velocity.Normalize();
        m_velocity *= m_minSpeed.Magnitude();
    }

    ObjectBase::Update(timeStep);
}
//---------------------------------------------------------------------------

//==============================================================================
#pragma endregion // Move able character
//==============================================================================
