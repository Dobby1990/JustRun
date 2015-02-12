#include "Settings.h"

Settings* Settings = NULL;	// settings instance

Settings::Settings(){
	Settings::init();	// call init to initialise all variables
}

Settings::~Settings(){
	CollisionManager::clear();	// call clear to safefully delete pointers
}

// return instance of collision manager
Settings* Settings::getSettings(){
	if (Settings == NULL)					// if instance is null create a new one
		Settings = new Settings();

	return Settings;
}

// turn m_sound to false
void Settings::disableSound(){
	Settings::m_sound = false;
}

// turn m_sound to true
void Settings::enableSound(){
	Settings::m_sound = true;
}
// return state of m_sound
bool Settings::isPlaying(){
	return Settings::m_sound;
}

// set m_sound to true
bool Settings::init(){
	Settings::m_sound = true;

	return true;
}

// delete player pointer and content of objects array
bool Settings::clear(){
	// empty clear method
	return true;
}
