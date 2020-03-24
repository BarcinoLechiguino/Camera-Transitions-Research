#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 
#include <sstream> 

#include "p2Defs.h"
#include "p2Log.h"

#include "Application.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Map.h"
#include "Fonts.h"
#include "Gui.h"
#include "SceneManager.h"

// Constructor
Application::Application(int argc, char* args[]) : argc(argc), args(args)
, win(nullptr)
, input(nullptr)
, render(nullptr)
, tex(nullptr)
, audio(nullptr)
, map(nullptr)
, font(nullptr)
, gui(nullptr)
, scene_manager(nullptr)
{
	PERF_START(ptimer);

	win				= new Window();
	input			= new Input();
	render			= new Render();
	tex				= new Textures();
	audio			= new Audio();
	map				= new Map();
	font			= new Fonts();
	gui				= new Gui();
	scene_manager	= new SceneManager();

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(input);
	AddModule(win);
	AddModule(tex);
	AddModule(audio);
	AddModule(map);
	AddModule(font);
	AddModule(gui);

	// scene_manager last
	AddModule(scene_manager);

	// render last to swap buffer
	AddModule(render);

	PERF_PEEK(ptimer);
}

// Destructor
Application::~Application()
{
	// release modules
	std::list<Module*>::reverse_iterator item = modules.rbegin();

	while(item != modules.rend())
	{
		RELEASE(*item);
		++item;
	}

	modules.clear();
}

void Application::AddModule(Module* module)
{
	module->Init();
	modules.push_back(module);
}

// Called before render is available
bool Application::Awake()
{
	PERF_START(ptimer);

	pugi::xml_document	config_file;
	pugi::xml_node		config;
	pugi::xml_node		app_config;

	bool ret = false;
		
	config = LoadConfig(config_file);

	if(config.empty() == false)
	{
		// self-config
		ret				= true;
		app_config		= config.child("app");
		title			= app_config.child("title").child_value();
		organization	= app_config.child("organization").child_value();

		int cap			= app_config.attribute("framerate_cap").as_int(-1);

		if(cap > 0)
		{
			capped_ms = 1000 / cap;
		}
	}

	if(ret == true)
	{
		std::list<Module*>::iterator item = modules.begin();

		while(item != modules.end() && ret == true)
		{
			ret = (*item)->Awake(config.child((*item)->name.c_str()));
			++item;
		}
	}

	PERF_PEEK(ptimer);

	return ret;
}

// Called before the first frame
bool Application::Start()
{
	PERF_START(ptimer);
	bool ret = true;
	std::list<Module*>::iterator item = modules.begin();

	while(item != modules.end() && ret == true)
	{
		ret = (*item)->Start();
		++item;
	}
	startup_time.Start();

	PERF_PEEK(ptimer);

	return ret;
}

// Called each loop iteration
bool Application::Update()
{
	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate();

	if(ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// ---------------------------------------------
pugi::xml_node Application::LoadConfig(pugi::xml_document& config_file) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = config_file.load_file("config.xml");

	if(result == NULL)
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
	else
		ret = config_file.child("config");

	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	frame_count++;
	last_sec_frame_count++;

	dt = frame_time.ReadSec();
	frame_time.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	// Framerate calculations --

	if(last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;
	}

	float avg_fps = float(frame_count) / startup_time.ReadSec();
	float seconds_since_startup = startup_time.ReadSec();
	uint32 last_frame_ms = frame_time.Read();
	uint32 frames_on_last_update = prev_last_sec_frame_count;

	static char title[256];
	sprintf_s(title, 256, "Av.FPS: %.2f Last Frame Ms: %u Last sec frames: %i Last dt: %.3f Time since startup: %.3f Frame Count: %lu ",
			  avg_fps, last_frame_ms, frames_on_last_update, dt, seconds_since_startup, frame_count);
	App->win->SetTitle(title);

	if(capped_ms > 0 && last_frame_ms < capped_ms)
	{
		PerfTimer t;
		SDL_Delay(capped_ms - last_frame_ms);
	}
}

// Call modules before each loop iteration
bool Application::PreUpdate()
{
	bool ret = true;
	std::list<Module*>::iterator item = modules.begin();
	Module* pModule = NULL;

	for(; item != modules.end() && ret == true; ++item)
	{
		pModule = (*item);

		if(pModule->active == false) {
			continue;
		}

		ret = (*item)->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool Application::DoUpdate()
{
	bool ret = true;
	std::list<Module*>::iterator item = modules.begin();
	Module* pModule = NULL;

	for(; item != modules.end() && ret == true; ++item)
	{
		pModule = (*item);

		if(pModule->active == false) {
			continue;
		}

		ret = (*item)->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool Application::PostUpdate()
{
	bool ret = true;
	std::list<Module*>::iterator item = modules.begin();
	Module* pModule = NULL;

	for(; item != modules.end() && ret == true; ++item)
	{
		pModule = (*item);

		if(pModule->active == false) {
			continue;
		}

		ret = (*item)->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool Application::CleanUp()
{
	PERF_START(ptimer);
	bool ret = true;
	std::list<Module*>::reverse_iterator item = modules.rbegin();

	while(item != modules.rend() && ret == true)
	{
		ret = (*item)->CleanUp();
		++item;
	}

	PERF_PEEK(ptimer);
	return ret;
}

// ---------------------------------------
int Application::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* Application::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* Application::GetTitle() const
{
	return title.c_str();
}

// ---------------------------------------
float Application::GetDT() const
{
	return dt;
}

// ---------------------------------------
const char* Application::GetOrganization() const
{
	return organization.c_str();
}

void Application::ExitApplication(bool& ret)
{
	if (ret)
	{
		ret = !ret;
	}
}