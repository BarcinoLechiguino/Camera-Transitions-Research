#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include "PugiXml\src\pugixml.hpp"

enum class SCENE
{
	FIRST_SCENE,
	SECOND_SCENE,
	NONE
};

class Scene
{
public:
	Scene(SCENE scene);
	virtual ~Scene();

	virtual bool Awake(pugi::xml_node& config);			// Called before render is available
	
	virtual bool Start();								// Called before the first frame

	virtual bool PreUpdate();							// Called before all Updates

	virtual bool Update(float dt);						// Called each loop iteration

	virtual bool PostUpdate();							// Called before all Updates

	virtual bool CleanUp();								// Called before quitting


	//virtual void LoadGuiElements();					// Method that will load all the Gui Elements present in this scene.

private:


public:
	std::string name;
	SCENE		scene;									// SCENE will be both the name and the index of the scene.

};

#endif // !__SCENE_H__