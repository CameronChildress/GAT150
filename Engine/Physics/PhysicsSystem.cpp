#include "pch.h"
#include "PhysicsSystem.h"
#include "Physics/ContactListener.h"

namespace nc
{
    bool PhysicsSystem::Startup()
    {
        b2Vec2 gravity(0.0f, 10);

        m_world = new b2World{ gravity };

        m_contactListener = new ContactListener;
        m_world->SetContactListener(m_contactListener);

        return true;
    }

    void PhysicsSystem::Shutdown()
    {
        delete m_world;
        m_world = nullptr;
    }

    void PhysicsSystem::Update()
    {
        float timeStep = (1.0f / 60.0f);
        m_world->Step(timeStep, 8, 3);
    }

    b2Body* PhysicsSystem::CreateBody(const Vector2& position, float angle, const RigidBodyData& data, GameObject* gameObject)
    {
        b2BodyDef bodyDef;
        
        Vector2 world = PhysicsSystem::ScreenToWorld(position);

        bodyDef.type = (data.isDynamic) ? b2_dynamicBody : b2_staticBody;

        bodyDef.position.Set(world.x, world.y);
        bodyDef.angle = nc::DegreesToRadians(angle);
        bodyDef.fixedRotation = data.lockAngle;
        b2Body* body = m_world->CreateBody(&bodyDef);

        b2PolygonShape shape;
        Vector2 worldSize = PhysicsSystem::ScreenToWorld(data.size);
        shape.SetAsBox(worldSize.x, worldSize.y);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = data.density;
        fixtureDef.friction = data.friction;
        fixtureDef.restitution = data.restitution;
        fixtureDef.isSensor = data.isSensor;
        fixtureDef.userData = gameObject;

        body->CreateFixture(&fixtureDef);

        return body;
    }

    void PhysicsSystem::DestroyBody(b2Body* body)
    {
        m_world->DestroyBody(body);
    }
}
