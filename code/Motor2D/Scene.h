#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include "PugiXml\src\pugixml.hpp"

#include "Application.h"								// Watch out with unnecessary includes.

enum class SCENES
{
	FIRST_SCENE,
	SECOND_SCENE,
	NONE
};

class Scene
{
public:

	Scene(SCENES scene_name);
	virtual ~Scene();

	virtual bool Awake(pugi::xml_node& config);			// Called before render is available
	
	virtual bool Start();								// Called before the first frame

	virtual bool PreUpdate();							// Called before all Updates

	virtual bool Update(float dt);						// Called each loop iteration

	virtual bool PostUpdate();							// Called before all Updates

	virtual bool CleanUp();								// Called before quitting

public:
	void CameraDebugMovement(float dt);

public:
	SCENES		scene_name;								// SCENE will be both the name and the index of the scene.

};

#endif // !__SCENE_H__