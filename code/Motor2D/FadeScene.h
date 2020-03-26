#ifndef  _MODULE_SCENECHANGE_
#define _MODULE_SCENECHANGE_

#include "Module.h"
#include "SDL\include\SDL_rect.h"

enum ListOfMapNames;

class Fade_Scene : public Module
{
public:

	Fade_Scene();

	virtual ~Fade_Scene();

	//Called before render is avalible
	bool Awake(pugi::xml_node&);

	//Called before the first frame
	bool Start();

	//Called each loop iteration
	bool Update(float dt);

	//returns true if it's changing map
	bool IsChanging() const;

	//New, must change.
	bool FadeToBlack(const char* mapname, float time = 2.0f);
	bool FadeToBlack2(Module* module_off, Module* module_on, float time = 1.0f);

private:

public:

	bool fading = false;

private:
	enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black
	} current_step = fade_step::none;

	int nextMap;
	float start_time = 0;
	float total_time = 0;
	SDL_Rect screen;
	const char* mapName;
	Module* to_enable = nullptr;
	Module* to_disable = nullptr;

};
#endif // ! _MODULE_SCENECHANGE_
