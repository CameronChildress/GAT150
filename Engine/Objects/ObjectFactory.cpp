#include "pch.h"
#include "ObjectFactory.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/SpriteAnimationComponent.h"

namespace nc
{
	void ObjectFactoryImpl::Initialize()
	{
		nc::ObjectFactory::Instance().Register("GameObject", new nc::Creator<GameObject, Object>);
		nc::ObjectFactory::Instance().Register("PhysicsComponent", new nc::Creator<PhysicsComponent, Object>);
		nc::ObjectFactory::Instance().Register("SpriteComponent", new nc::Creator<SpriteComponent, Object>);
		nc::ObjectFactory::Instance().Register("SpriteAnimationComponent", new nc::Creator<SpriteAnimationComponent, Object>);
	}
}
