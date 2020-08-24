#include "pch.h"
#include "Engine.h"

namespace nc
{
    bool Engine::Startup()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        m_systems.push_back(new Renderer);
        m_systems.push_back(new InputSystem);
        m_systems.push_back(new ResourceManager);

        for (auto system : m_systems)
        {
            system->Startup();
        }

        GetSystem<Renderer>()->Create("GAT150", 800, 600);

        return true;
    }

    void Engine::Shutdown()
    {
        for (auto system : m_systems)
        {
            system->Shutdown();
            delete system;
        }
        m_systems.clear();

        SDL_Quit();
    }

    void Engine::Update()
    {
        m_timer.Tick();
        for (auto system : m_systems)
        {
            system->Update();
        }
    }
}
