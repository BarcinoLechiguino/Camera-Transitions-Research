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
	void	ScenePushbacks();										// The pushbacks must be made in the order in which the scenes will appear.
	void	LoadInitialScene();										// Will load the first scene in the scenes vector.
	void	SwitchScene(SCENES scene_name);							// Unloads the current scene and then loads the next one.
	void	LoadScene(SCENES scene_name);							// Loads the a new scene. Can be called even while there is another one already running.

	Scene*	CreateScene(SCENES scene_name);

	void	ReverseSwitchScene(SCENES scene_name);					// Loads the next scene and then unloads the current one.
	void	CaseSwitchScene(SCENES scene_name);
	void	VectorSwitchScene(SCENES scene_name);

public:
	Scene*					current_scene;		// The scene that is being currently loaded.
	Scene*					next_scene;

private:
	std::vector<Scene*>		scenes;				// All the scenes of the game.
};

#endif // !__SCENE_MANAGER_H__