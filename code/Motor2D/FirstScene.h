#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;

class UI;
class UI_Image;
class UI_Text;
class UI_Button;
class UI_InputBox;
class UI_Scrollbar;

class FirstScene : public Module
{
public:

	FirstScene();

	// Destructor
	virtual ~FirstScene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

public:
	bool escape;
	
	UI_Image*		window;
	UI_Text*		interactibleText;
	UI_Text*		buttonLabel;
	UI_Button*		button;
	UI_Button*		escButton;
	UI_Button*		draggableButton;
	UI_Button*		draggableButton2;

	UI_InputBox*	inputBox;

	UI_Image*		scrollWindow;
	UI_Text*		scrollText;
	UI_InputBox*	scrollInputBox;
	UI_Scrollbar*	scrollbar;
	UI_Image*		thumbo;

private:
	SDL_Texture* debug_tex;
	UI_Image* banner;
	UI_Text* text;

	Module* listener;
};

#endif // __SCENE_H__