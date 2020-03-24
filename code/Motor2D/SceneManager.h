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
	void	LoadInitialScene(SCENES scene_name);
	
	void	SwitchScene(SCENES scene_name);

	void	CaseSwitchScene(SCENES scene_name);
	
	Scene*	CreateScene(SCENES scene_name);

public:
	Scene*					current_scene;		// The scene that is being currently loaded.
	Scene*					next_scene;

private:
	std::vector<Scene*>		scenes;				// All the scenes of the game.
};

#endif // !__SCENE_MANAGER_H__