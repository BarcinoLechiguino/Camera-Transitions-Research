#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include "SDL/include/SDL.h"
#include "PugiXml\src\pugixml.hpp"

#include "Application.h"

// TODO 0: Familiarize yourself with the structure, different methods and core elements of
// the Camera Transition System. It will be key to be able to keep up with the rest of TODOs.

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

	virtual bool Awake(pugi::xml_node& config);					// Called before render is available
	virtual bool Start();										// Called before the first frame
	virtual bool PreUpdate();									// Called before all Updates
	virtual bool Update(float dt);								// Called each loop iteration
	virtual bool PostUpdate();									// Called before all Updates
	virtual bool CleanUp();										// Called before quitting

public:
	virtual void InitScene();									// Method that will be used to initialize the variables all the scenes.
	virtual void DrawScene();									// Method that will draw the map and all other elements of the scene.
	
	virtual void ExecuteTransition();							// Method that will trigger a new transition depending on the input received.
	virtual void CameraDebugMovement(float dt);					// Method that will move the camera around depending on the input.

public:
	SCENES		scene_name;										// SCENE will be both the name and the index of the scene.

	int			map_width;										// Width of the map loaded on the scene.
	int			map_height;										// Height of the map loaded on the scene.
};

#endif // !__SCENE_H__