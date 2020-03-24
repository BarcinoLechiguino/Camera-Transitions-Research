// ----------------------------------------------------
// Module.h
// Interface for all engine modules
// ----------------------------------------------------

#ifndef __MODULE_H__
#define __MODULE_H__

#include <list>
#include <vector>
#include "PugiXml\src\pugixml.hpp"

#include "p2Defs.h"
#include "p2Log.h"


class Application;
class UI;
enum class UI_Event;

class Module
{
public:

	Module() : active(false)
	{}

	virtual ~Module()
	{}

	void Init()
	{
		active = true;
	}

	virtual bool Awake(pugi::xml_node&)							// Called before render is available
	{
		return true;
	}

	virtual bool Start()										// Called before the first frame
	{
		return true;
	}

	virtual bool PreUpdate()									// Called each loop iteration
	{
		return true;
	}

	virtual bool Update(float dt)								// Called each loop iteration
	{
		return true;
	}

	virtual bool PostUpdate()									// Called each loop iteration
	{
		return true;
	}

	virtual bool CleanUp()										// Called before quitting
	{
		return true;
	}

	virtual void OnEventCall(UI* element, UI_Event ui_event)
	{
		return;
	}

public:

	std::string	name;
	bool		active;

};

#endif // !__MODULE_H__