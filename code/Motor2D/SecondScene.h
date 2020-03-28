#ifndef __SECOND_SCENE_H__
#define __SECOND_SCENE_H__

#include "Scene.h"

class SecondScene : public Scene
{
public:
	SecondScene();									// Constructor
	~SecondScene();									// Destructor

	bool Awake(pugi::xml_node& config);				// Called before render is available
	bool Start();									// Called before the first frame
	bool PreUpdate();								// Called before all Updates
	bool Update(float dt);							// Called each loop iteration
	bool PostUpdate();								// Called before all Updates
	bool CleanUp();									// Called before quitting

public:
	void InitScene();
	
	void DrawScene();
	SDL_Texture* SceneToTexture();

	void ExecuteTransition();						// Method that will trigger a new transition depending on the input received.

public:

};

#endif // !__SECOND_SCENE_H__
