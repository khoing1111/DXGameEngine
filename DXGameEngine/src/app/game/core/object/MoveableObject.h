#pragma once


/////////////
// INCLUDE
#include <hkUtilLib\core\Vector.h>

#include "ObjectCore.h"
#include "figure/ObjectFigure.h"
#include "boundingBox/BoundingBox.h"
#include "controll/FrameController.h"


namespace GameCore
{
    /////////////////////////
    // CLASS: PhysicObject
    class PhysicObject : public GameCore::ObjectBase
    {
    public:
        PhysicObject();
        PhysicObject(const PhysicObject& clone);
        ~PhysicObject();

        void SetElastic(float elastic);
        void SetFriction(float friction);
        void SetMass(float mass);

        float GetElastic();
        float GetFriction();
        float GetMass();

    protected:
        float m_elastic;
        float m_friction;
        float m_mass;
    };

    ///////////////////////////
    // CLASS: MoveableObject
    class MoveableObject : public GameCore::PhysicObject
    {
    public:
        MoveableObject();
        MoveableObject(const MoveableObject& clone);
        ~MoveableObject();

        virtual void Update(float) override;

        void SetVelocity(const hkVector2F&);
        void SetAcceleration(const hkVector2F&);

        void SetSpeedLimit(hkVector2F = hkVector2F(0, 0), hkVector2F = hkVector2F(0, 0));
        void EnableSpeedLimit(bool speedLimit);
        bool HaveSpeedLimit();

        hkVector2F GetVelocity();
        hkVector2F GetAcceleration();

        void ApplyForce(const hkVector2F& force);

    private:
        hkVector2F m_velocity;
        hkVector2F m_acceleration;

        hkVector2F m_maxSpeed;
        hkVector2F m_minSpeed;
        bool m_haveSpeedLimit;
    };
}