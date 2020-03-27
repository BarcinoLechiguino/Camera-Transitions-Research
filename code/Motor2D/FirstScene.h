#ifndef __FIRSTSCENE_H__
#define __FIRSTSCENE_H__

#include "Module.h"
#include "Scene.h"

struct SDL_Texture;
class GuiImage;
class GuiText;

class UI;
class UI_Image;
class UI_Text;
class UI_Button;
class UI_InputBox;
class UI_Scrollbar;

class FirstScene : public Scene
{
public:

	FirstScene();
	FirstScene(SCENES scene);						// Constructor
	~FirstScene();									// Destructor

	bool Awake(pugi::xml_node& config);				// Called before render is available
	bool Start();									// Called before the first frame
	bool PreUpdate();								// Called before all Updates
	bool Update(float dt);							// Called each loop iteration
	bool PostUpdate();								// Called before all Updates
	bool CleanUp();									// Called before quitting

public:
	void ExecuteTransition();						// Method that will trigger a new transition depending on the input received.

public:

};

#endif // __FIRSTSCENE_H__