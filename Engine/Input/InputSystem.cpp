#include "pch.h"
#include "InputSystem.h"

namespace nc
{
    bool InputSystem::Startup()
    {
        // get current keystate and retrieve numKeys
        const Uint8* keystate = SDL_GetKeyboardState(&m_numKeys);
        
        // allocate memory for current and previous keystate
        m_keystate = new Uint8[m_numKeys];
        m_prevKeystate = new Uint8[m_numKeys];

        // copy current keystate (source) to m_keystate (destination)
        memcpy(m_keystate, m_prevKeystate, m_numKeys);

        // copy current keystate to m_prevKeystate
        memcpy(m_prevKeystate, m_keystate, m_numKeys);
        
        return true;
    }

    void InputSystem::Shutdown()
    {
        delete[] m_keystate;
        delete[] m_prevKeystate;
    }

    void InputSystem::Update()
    {
        // copy m_keystate (source) to m_prevKeystate (destination)
        memcpy(m_prevKeystate, m_keystate, m_numKeys);

       // get current keystate
        const Uint8* keystate = SDL_GetKeyboardState(nullptr);
        
        // copy current keystate to m_keystate
        memcpy(m_keystate, keystate, m_numKeys);
    }

    InputSystem::eButtonState InputSystem::GetButtonState(int id)
    {
        eButtonState state = eButtonState::IDLE; 
        
        bool buttonDown = GetButtonDown(id); 
        bool prevButtonDown = GetPreviousButtonDown(id); 
        
        if (buttonDown) 
        { 
            state = (prevButtonDown) ? HELD : PRESSED ; 
        }
        else 
        { 
            state = (prevButtonDown) ? RELEASED : IDLE ; 
        }
        
        return state;
    }

    bool InputSystem::GetButtonDown(int id)
    {
        return m_keystate[id];
    }

    bool InputSystem::GetPreviousButtonDown(int id)
    {
        return m_prevKeystate[id];
    }
}
