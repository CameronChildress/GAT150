#pragma once

#include "Object.h"
#include <list>

namespace nc 
{
	class Engine; 
	class GameObject; 

	class Scene : public Object 
	{
	public:
		virtual bool Create(void* data = nullptr) override; 
		virtual void Destroy() override; 

		void Read(const rapidjson::Value& value) override; 
		void ReadGameObjects(const rapidjson::Value& value);
		void ReadPrototypes(const rapidjson::Value& value);

		void Update();
		void Draw();

		GameObject* Find(const std::string& name);
		std::vector<GameObject*> FindGameObjectsWithTag(const std::string& tag);

		void AddGameObject(GameObject* gameObject);
		void RemoveGameObject(GameObject* gameObject);
		void RemoveAllGameObjects();

	protected:
		Engine* m_engine{ nullptr }; 
		std::list<GameObject*> m_gameObjects;
	};
}