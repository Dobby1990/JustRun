#ifndef _SETTINGS_H_
#define _SETTINGS_H_

class Settings {
public:
	static Settings* getSettings();	// return instance of settings

	void disableSound();	// set music state to false
	void enableSound();		// set music state to true

	bool init();	// init method called by constructor
	bool clear();	// clear method called by deconstructor
	bool isPlaying(); // return sound state

private:
	Settings();		// hidden constructor
	~Settings();	// hidden deconstructor

	bool m_sound;	// sound state
};
#endif
