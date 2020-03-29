#ifndef __UI_WINDOW_H__
#define __UI_WINDOW_H__

#include "UI.h"

class UI_Window : public UI
{
public:
	UI_Window(UI_Element element, int x, int y, SDL_Rect hitbox, bool isVisible = true, bool isInteractible = false, bool isDraggable = false, UI* parent = nullptr);

	bool Draw();

	void CheckInput();				//If any UI element can be interactible, then this function needs to be declared at UI as virtual void.

	void UpdateChilds();			//Updates all the window's childs.

private:
	SDL_Texture*	tex;
};

#endif // !__UI_WINDOW_H__