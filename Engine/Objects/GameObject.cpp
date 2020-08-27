#include "pch.h"
#include "GameObject.h"
#include "Components/Component.h"
#include "Components/RenderComponent.h"
#include "ObjectFactory.h"

namespace nc
{
    GameObject::GameObject(const GameObject& other)
    {
        m_name = other.m_name;
        m_tag = other.m_tag;
        m_lifetime = other.m_lifetime;

        m_flags = other.m_flags;

        m_transform = other.m_transform;
        m_engine = other.m_engine;

        for (Component* component : other.m_components)
        {
            Component* clone = dynamic_cast<Component*>(component->Clone());
            clone->m_owner = this;
            AddComponent(clone);
        }
    }

    bool GameObject::Create(void* data)
    {
        m_engine = static_cast<Engine*>(data);

        return false;
    }

    void GameObject::Destroy()
    {
        RemoveAllComponents();
    }

    void GameObject::Read(const rapidjson::Value& value)
    {
        nc::json::Get(value, "name", m_name);
        nc::json::Get(value, "tag", m_tag);
        nc::json::Get(value, "lifetime", m_lifetime);

        bool transient = m_flags[eFlags::TRANSIENT];
        json::Get(value, "transient", transient);
        m_flags[eFlags::TRANSIENT] = transient;

        nc::json::Get(value, "position", m_transform.position);
        nc::json::Get(value, "scale", m_transform.scale);
        nc::json::Get(value, "angle", m_transform.angle);

        if (value.HasMember("Components"))
        {
            const rapidjson::Value& componentsValue = value["Components"]; 
            if (componentsValue.IsArray()) 
            { 
                ReadComponents(componentsValue); 
            }
        }
    }

    void GameObject::ReadComponents(const rapidjson::Value& value)
    {
        for (rapidjson::SizeType i = 0; i < value.Size(); i++) 
        {
            const rapidjson::Value& componentValue = value[i]; 
            
            if (componentValue.IsObject()) 
            {
                std::string typeName;
                json::Get(componentValue, "type", typeName);

                Component* component = nc::ObjectFactory::Instance().Create<nc::Component>(typeName); 
                if (component)
                {
                    component->Create(this);
                    component->Read(componentValue);

                    AddComponent(component);
                    
                }
            }
        }
    }

    void GameObject::Update()
    {
        for (auto component : m_components)
        {
            component->Update();
        }

        if (m_flags[eFlags::TRANSIENT])
        {
            m_lifetime -= m_engine->GetTimer().DeltaTime();
            m_flags[eFlags::DESTROY] = (m_lifetime <= 0);
        }
    }

    void GameObject::Draw()
    {
        RenderComponent* component = GetComponent<RenderComponent>();
        if (component)
        {
            component->Draw();
        }
    }

    void GameObject::BeginContact(GameObject* other)
    {
        m_contacts.push_back(other);
    }

    void GameObject::EndContact(GameObject* other)
    {
        m_contacts.remove(other);
    }

    std::vector<GameObject*> GameObject::GetContactsWithTag(const std::string& tag)
    {
        std::vector<GameObject*> contacts; 

        for (auto contact : m_contacts)
        {
            if (contact->m_tag == tag)
            {
                contacts.push_back(contact);
            }
        }

        return contacts;
    }

    void GameObject::AddComponent(Component* component)
    {
        component->m_owner = this;
        m_components.push_back(component);
    }

    void GameObject::RemoveComponent(Component* component)
    {
        auto iter = std::find(m_components.begin(), m_components.end(), component);
        if (iter != m_components.end())
        {
            (*iter)->Destroy();
            delete (*iter);
        }
    }

    void GameObject::RemoveAllComponents()
    {
        for (auto component : m_components)
        {
            component->Destroy();
            delete component;
        }
        m_components.clear();
    }
}
