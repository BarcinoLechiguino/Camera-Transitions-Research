#ifndef __FIRSTSCENE_H__
#define __FIRSTSCENE_H__

#include "Module.h"
#include "Scene.h"

class FirstScene : public Scene
{
public:

	FirstScene();									// Constructor
	~FirstScene();									// Destructor

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

#endif // __FIRSTSCENE_H__