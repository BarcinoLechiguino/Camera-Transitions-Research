#ifndef __j1SCENE2_H__
#define __j1SCENE2_H__

#include "j1Module.h"
#include "p2Point.h"

struct SDL_Texture;

class j1Scene2 : public j1Module
{
public:

	j1Scene2();
	virtual ~j1Scene2();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void ChangeScene();

public:

	bool zoom_done = false;

};

#endif // __j1SCENE2_H__