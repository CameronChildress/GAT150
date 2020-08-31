#include "pch.h"
#include "TileMap.h"
#include "Objects/Scene.h"
#include "Objects/GameObject.h"
#include "Objects/ObjectFactory.h"

namespace nc
{
    void TileMap::Read(const rapidjson::Value& value)
    {
        json::Get(value, "numX", m_numX);
        json::Get(value, "numY", m_numY);
        json::Get(value, "size", m_size);
        json::Get(value, "start", m_start);
        json::Get(value, "tileNames", m_tileNames);
        json::Get(value, "tiles", m_tiles);
    }

    bool TileMap::Create(Scene* scene)
    {
        for (size_t i = 0; i < m_tiles.size(); i++)
        {
            int index = m_tiles[i];

            if (index != 0)
            {
                GameObject* gameobject = ObjectFactory::Instance().Create<GameObject>(m_tileNames[index]);

                float x = i % m_numX;
                float y = i / m_numX;
                gameobject->m_transform.position = m_start + nc::Vector2{ x, y } * m_size;
                scene->AddGameObject(gameobject);
            }
        }

        return true;
    }
}