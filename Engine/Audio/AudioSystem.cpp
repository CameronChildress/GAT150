#include "pch.h"
#include "AudioSystem.h"
namespace nc
{    
	bool nc::AudioSystem::Startup()   
	{        
		FMOD_RESULT result = FMOD::System_Create(&m_system);        
		ASSERT_MSG(result == FMOD_OK, "Error creating FMOD system.");     

		void* extradriverdata = nullptr;        

		result = m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);        
		ASSERT_MSG(result == FMOD_OK, "Error initializing FMOD system.");   

		return true;    
	}    

	void nc::AudioSystem::Shutdown()    
	{        
		FMOD_RESULT result = m_system->close();        
		ASSERT_MSG(result == FMOD_OK, "Error closing FMOD system.");     

		result = m_system->release();   
		ASSERT_MSG(result == FMOD_OK, "Error releasing FMOD system.");    
	}    

	void nc::AudioSystem::Update()
	{  
		FMOD_RESULT result = m_system->update();
		ASSERT_MSG(result == FMOD_OK, "Error updating FMOD system.");
	}
}