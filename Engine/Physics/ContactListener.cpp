#include "pch.h"
#include "ContactListener.h"
#include "Objects/GameObject.h"

namespace nc
{
	void ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData() && fixtureB->GetUserData())
		{
			GameObject* gameObjectA = static_cast<GameObject*>(fixtureA->GetUserData());
			GameObject* gameObjectB = static_cast<GameObject*>(fixtureB->GetUserData());

			gameObjectA->BeginContact(gameObjectB);
			gameObjectB->BeginContact(gameObjectA);
		}
	}

	void ContactListener::EndContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData() && fixtureB->GetUserData())
		{
			GameObject* gameObjectA = static_cast<GameObject*>(fixtureA->GetUserData());
			GameObject* gameObjectB = static_cast<GameObject*>(fixtureB->GetUserData());

			gameObjectA->EndContact(gameObjectB);
			gameObjectB->EndContact(gameObjectA);
		}
	}
}
