#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <list>
#include "Module.h"
#include "PerfTimer.h"
#include "Timer.h"
#include "PugiXml\src\pugixml.hpp"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Map;
class Fonts;
class Gui;
class SceneManager;

class Application
{
public:

	Application(int argc, char* args[]);					// Constructor
	
	virtual ~Application();									// Destructor

	bool Awake();											// Called before render is available
	
	bool Start();											// Called before render is available
	
	bool Update();											// Called each loop iteration
	
	bool CleanUp();											// Called before quitting


	void AddModule(Module* module);							// Add a new module to handle

	int GetArgc() const;									// Exposing some properties for reading
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;
	float GetDT() const;

	void ExitApplication(bool& ret);

private:

	pugi::xml_node LoadConfig(pugi::xml_document&) const;	// Load config file

	void PrepareUpdate();									// Call modules before each loop iteration

	void FinishUpdate();									// Call modules before each loop iteration

	bool PreUpdate();										// Call modules before each loop iteration

	bool DoUpdate();										// Call modules on each loop iteration

	bool PostUpdate();										// Call modules after each loop iteration

public:

	// Modules
	Window*				win;
	Input*				input;
	Render*				render;
	Textures*			tex;
	Audio*				audio;
	Map*				map;
	Fonts*				font;
	Gui*				gui;
	SceneManager*		scene_manager;

private:

	std::list<Module*>	modules;
	int					argc;
	char**				args;

	std::string			title;
	std::string			organization;

	PerfTimer			ptimer;
	uint64				frame_count = 0;
	Timer				startup_time;
	Timer				frame_time;
	Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	float				dt = 0.0f;
	int					capped_ms = -1;
};

extern Application* App; // No student is asking me about that ... odd :-S

#endif