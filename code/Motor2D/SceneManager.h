#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "Module.h"
#include "Scene.h"

class SceneManager : public Module
{
public:
	SceneManager();
	~SceneManager();

	bool Awake(pugi::xml_node& config);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();


public:
	void	LoadInitialScene(SCENE name);
	
	void	SwitchScene(SCENE name);
	
	Scene*	CreateScene(SCENE name);

public:
	Scene*					current_scene;		// The scene that is being currently loaded.

private:
	std::vector<Scene*>		scenes;				// All the scenes of the game.
};

#endif // !__SCENE_MANAGER_H__