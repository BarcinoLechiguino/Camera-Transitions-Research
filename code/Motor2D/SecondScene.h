#ifndef __SECOND_SCENE_H__
#define __SECOND_SCENE_H__

#include "Scene.h"

class SecondScene : public Scene
{
public:
	SecondScene();
	SecondScene(SCENES scene);
	~SecondScene();									// Destructor

	bool Awake(pugi::xml_node& config);				// Called before render is available
	bool Start();									// Called before the first frame
	bool PreUpdate();								// Called before all Updates
	bool Update(float dt);							// Called each loop iteration
	bool PostUpdate();								// Called before all Updates
	bool CleanUp();									// Called before quitting

public:
	void ExecuteTransition();						// Method that will trigger a new transition depending on the input received.

	void LoadGuiElements();							// Method that will load all the Gui Elements present in this scene.

private:


};

#endif // !__SECOND_SCENE_H__
