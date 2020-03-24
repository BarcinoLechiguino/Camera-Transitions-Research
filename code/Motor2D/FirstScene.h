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


	void LoadGuiElements();							// Method that will load all the Gui Elements present in this scene.

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
	std::string		name;
	int				index;
	
	SDL_Texture*	debug_tex;
	UI_Image*		banner;
	UI_Text*		text;

	Module*			listener;
};

#endif // __FIRSTSCENE_H__