#include "p2Defs.h"
#include "p2Log.h"
#include "Application.h"
#include "Render.h"
#include "Textures.h"
#include "Fonts.h"
#include "Input.h"
#include "Gui.h"
#include "SceneManager.h"

Gui::Gui() : Module()
{
	name = "gui";
}

// Destructor
Gui::~Gui()
{}

// Called before render is available
bool Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.c_str());

	ui_debug = false;
	escape = true;

	iteratedElement = elements.end();

	return true;
}

// Update all guis
bool Gui::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
	{
		PassFocus();
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		if (focusedElement != nullptr && focusedElement->isInteractible)
		{
			focusedElement->ui_event = UI_Event::UNCLICKED;
			OnEventCall(focusedElement, focusedElement->ui_event);
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
	{
		//ShowElement(App->scene->draggableButton2);
		/*SetElementsVisibility(App->scene_manager->current_scene, !App->scene_manager->current_scene->window);
		SetElementsVisibility(App->scene->scrollWindow, !App->scene->scrollWindow->isVisible);*/
	}
	
	return true;
}

// Called after all Updates
bool Gui::PostUpdate()
{	
	std::list<UI*>::iterator elem = elements.begin();

	for (; elem != elements.end(); ++elem)
	{
		if ((*elem)->isVisible)
		{
			(*elem)->Draw();
		}
	}

	Debug_UI();

	return escape;
}

// Called before quitting
bool Gui::CleanUp()
{
	LOG("Freeing GUI");

	//Iterate the elements list and frees all allocated memory.
	std::list<UI*>::iterator elem = elements.begin();

	for (; elem != elements.end(); ++elem)
	{
		(*elem)->CleanUp();
		RELEASE((*elem));
	}

	elements.clear();

	return true;
}

// const getter for atlas
/*const*/ SDL_Texture* Gui::GetAtlas() const
{
	return atlas;
}

//----------------------------------- UI ELEMENT CREATION METHODS -----------------------------------
UI* Gui::CreateImage(UI_Element element, int x, int y, SDL_Rect hitbox, bool isVisible, bool isInteractible, bool isDraggable, UI* parent)
{
	UI* elem = nullptr;

	elem = new UI_Image(element, x, y, hitbox, isVisible, isInteractible, isDraggable, parent);

	if (elem != nullptr)
	{
		elements.push_back(elem);
	}

	return elem;
}

UI* Gui::CreateText(UI_Element element, int x, int y, SDL_Rect hitbox, _TTF_Font* font, SDL_Color fontColour, bool isVisible, bool isInteractible, bool isDraggable,
					UI* parent, std::string* string, std::string* hoverString, std::string* leftClickString, std::string* rightClickString)
{
	UI* elem = nullptr;

	elem = new UI_Text(element, x, y, hitbox, font, fontColour, isVisible, isInteractible, isDraggable, parent, string, hoverString, leftClickString, rightClickString);

	if (elem != nullptr)
	{
		elements.push_back(elem);
	}

	return elem;
}

UI* Gui::CreateButton(UI_Element element, int x, int y, bool isVisible, bool isInteractible, bool isDraggable, UI* parent, SDL_Rect* idle, SDL_Rect* hover, SDL_Rect* clicked)
{
	UI* elem = nullptr;

	elem = new UI_Button(element, x, y, isVisible, isInteractible, isDraggable, parent, idle, hover, clicked);

	if (elem != nullptr)
	{
		elements.push_back(elem);
	}

	return elem;
}

UI* Gui::CreateUI_Window(UI_Element element, int x, int y, SDL_Rect hitbox, bool isVisible, bool isInteractible, bool isDraggable, UI* parent)
{
	UI* elem = nullptr;

	elem = new UI_Window(element, x, y, hitbox, isVisible, isInteractible, isDraggable, parent);

	if (elem != nullptr)
	{
		elements.push_back(elem);
	}

	return elem;
}

UI* Gui::CreateInputBox(UI_Element element, int x, int y, SDL_Rect hitbox, _TTF_Font* font, SDL_Color fontColour, SDL_Rect cursor, SDL_Color cursorColour, iPoint textOffset, 
					float blinkFrequency, bool isVisible, bool isInteractible, bool isDraggable, UI* parent, std::string* defaultString)
{
	UI* elem = nullptr;

	elem = new UI_InputBox(element, x, y, hitbox, font, fontColour, cursor, cursorColour, textOffset, blinkFrequency, isVisible, isInteractible, isDraggable, parent, defaultString);

	if (elem != nullptr)
	{
		elements.push_back(elem);
	}

	return elem;
}

UI* Gui::CreateScrollbar(UI_Element element, int x, int y, SDL_Rect hitbox, SDL_Rect thumbSize, iPoint thumbOffset, SDL_Rect dragArea, float dragFactor, bool dragXAxis, bool dragYAxis,
					bool invertedScrolling, bool isVisible, bool isInteractible, bool isDraggable, UI* parent, SDL_Rect* scrollMask, iPoint maskOffset)
{
	UI* elem = nullptr;

	elem = new UI_Scrollbar(element, x, y, hitbox, thumbSize, thumbOffset, dragArea, dragFactor, dragXAxis, dragYAxis, invertedScrolling,
					isVisible, isInteractible, isDraggable, parent, scrollMask, maskOffset);

	if (elem != nullptr)
	{
		elements.push_back(elem);
	}

	return elem;
}

//--------------------------------- INPUT PROCESSING METHODS ---------------------------------
void Gui::OnEventCall(UI* element, UI_Event ui_event)
{
	//if (element == App->scene->button && ui_event == UI_Event::UNCLICKED)					//If the pointer received is the UI_Button* button pointer of Scene.h and event = clicked. 
	//{
	//	App->gui->ui_debug = !App->gui->ui_debug;											//Enables / Disables UI Debug Mode.
	//}

	//if (element == App->scene->escButton && ui_event == UI_Event::UNCLICKED)				//If the pointer received is the UI_Button* escbutton pointer of Scene.h and event = clicked.
	//{
	//	escape = false;
	//}

	//if (element == App->scene->draggableButton && ui_event == UI_Event::UNCLICKED)
	//{
	//	App->gui->ui_debug = !App->gui->ui_debug;
	//}

	//if (element == App->scene->interactibleText && ui_event == UI_Event::UNCLICKED)
	//{
	//	App->gui->ui_debug = !App->gui->ui_debug;
	//}
} 

// --- Method to return the foremost element of the UI. (First in inverse order of draw)
UI* Gui::FirstElementUnderMouse() const
{
	UI* firstElement = nullptr;

	std::list<UI*>::const_iterator elem = elements.cbegin();

	for (; elem != elements.cend(); ++elem)
	{
		if (ElementCanBeClicked((*elem)))													//Checks that the element being iterated has the mouse on it.
		{
			firstElement = (*elem);															//The element being iterated is assigned to firstElement.
		}
	}

	if (firstElement != nullptr)
	{
		return firstElement;																//The last element that was checked to have the mouse on it will be returned.
	}
}

bool Gui::ElementCanBeClicked(UI* clickedElement) const
{
	bool ret = false;

	if (clickedElement->CheckMousePos()
		&& clickedElement->isVisible
		&& (clickedElement->isInteractible
			|| clickedElement->isDraggable))
	{
		ret = true;
	}
	
	return ret;
}

//----------------------------------- FOCUS MANAGEMENT METHODS -----------------------------------
// --- Method that will pass the focus from focuseable UI Element to the next.
void Gui::PassFocus()
{
	if (iteratedElement == elements.end())
	{
		iteratedElement = elements.begin();
	}
	
	if (focusedElement == nullptr)
	{
		for (iteratedElement; iteratedElement != elements.end(); ++iteratedElement)			//Loop that is used to find the first interactible element of the elments list.
		{
			if (ElementCanBeFocused((*iteratedElement)))									//If the element being iterated fulfills all focus conditions.
			{
				focusedElement = (*iteratedElement);										//UI* focusedElement is set with the UI* of the element being iterated.
				break;																		//The loop is stopped.
			}
		}

		return;																				//Stops the function here so the focus remains in the first interactible element.
	}

	for (iteratedElement; iteratedElement != elements.end(); ++iteratedElement)				//Loop that is used to find the next interactible element of the elments list.
	{
		if (*next(iteratedElement) != nullptr)												//If the next element of the list is not NULL.
		{
			if (ElementCanBeFocused(*next(iteratedElement)))								//If the next element of the list fulfills all focus conditions.
			{
				focusedElement = *next(iteratedElement);									//UI* focusedElement is set with the UI* of the element next to the element being iterated. 
				++iteratedElement;															//The element being iterated is set to the next element in the list.
				break;																		//The loop is stopped so the focus remains in the interactible element that now has the focus.
			}
		}
		else																				//If the next element of the list is NULL.
		{
			iteratedElement = elements.end();												//The list_item is set to nullptr.
			focusedElement	= nullptr;														//The UI* focused element is set to nullptr, which efectively disables the focus.
			break;																			//The loop is stopped so no element regains the focus.
		}
	}
}

// --- Method that returns true if the passed element is a visible BUTTON, INPUTBOX or a SCROLLBAR
bool Gui::ElementCanBeFocused(UI* focusElement) const
{
	bool ret = false;

	if (focusElement->isVisible 
		/*&& focusElement->isInteractible */
		&& (focusElement->element == UI_Element::BUTTON 
			|| focusElement->element == UI_Element::SCROLLBAR 
			|| focusElement->element == UI_Element::INPUTBOX))
	{
		ret = true;
	}

	return ret;
}

// --------------------------- PARENT/CHILD UI ELEMENTS METHODS --------------------------
// --- 
bool Gui::ElementHasChilds(UI* parentElement) const
{
	bool ret = false;
	
	std::list<UI*>::const_iterator elem = elements.cbegin();

	for (; elem != elements.cend(); ++elem)
	{
		if ((*elem)->parent == parentElement)
		{
			ret = true;
			break;
		}
	}

	return ret;
}

void Gui::UpdateChilds(UI* parentElement)
{
	std::list<UI*>::iterator child = elements.begin();
	
	for (; child != elements.end(); ++child)
	{
		if ((*child)->parent == parentElement)
		{
			(*child)->prevMousePos = (*child)->parent->prevMousePos;				//The prevMousePos of the element being iterated is set with the parent's prev mouse pos.
			(*child)->DragElement();												//The child is also dragged, just as the parent.

			if (ElementHasChilds((*child)))											//If the first child also has child elements, then they are updated the same way.
			{
				UpdateChilds((*child));												//Recursive function, maybe avoid?
			}
		}
	}
}

void Gui::SetElementsVisibility(UI* parentElement, bool state)
{	
	std::list<UI*>::iterator child = elements.begin();
	
	for (; child != elements.end(); ++child)
	{
		if ((*child)->parent == parentElement)										//If the parent of the iterated element is parentElement.
		{
			(*child)->isVisible = state;											//Enables/Disables the iterated child's visibility. Changes isVisible from true to false and viceversa.

			if (ElementHasChilds((*child)))											//If the first child also has child elements, then they are updated the same way.
			{
				SetElementsVisibility((*child), state);								//Recursive function, maybe avoid?
			}
		}
	}

	//parentElement->isVisible = !parentElement->isVisible;							//Enables/Disables the parent element's visibility. Changes isVisible from true to false and viceversa.	
	parentElement->isVisible = state;												//Enables/Disables the parent element's visibility. Changes isVisible from true to false and viceversa.	
}

//----------------------------------- UI DEBUG METHOD -----------------------------------
void Gui::Debug_UI()
{
	if (ui_debug == true)
	{
		for (std::list<UI*>::iterator elem = elements.begin(); elem != elements.end(); ++elem)
		{	
			if ((*elem)->isVisible)
			{
				switch ((*elem)->element)
				{
				case UI_Element::EMPTY:
					App->render->DrawQuad((*elem)->GetHitbox(), 255, 255, 255, 255, false, false);		//UI_Empty will be WHITE.
						break;
				
				case UI_Element::IMAGE:
					App->render->DrawQuad((*elem)->GetHitbox(), 0, 0, 255, 255, false, false);			//UI_Image will be BLUE.

					break;

				case UI_Element::TEXT:
					App->render->DrawQuad((*elem)->GetHitbox(), 0, 255, 0, 255, false, false);			//UI_Text will be GREEN.

					break;

				case UI_Element::BUTTON:
					App->render->DrawQuad((*elem)->GetHitbox(), 255, 0, 0, 255, false, false);			//UI_Button will be RED.

					break;

				case UI_Element::SCROLLBAR:
					App->render->DrawQuad((*elem)->GetHitbox(), 255, 255, 0, 255, false, false);		//UI_Scrollbar will be YELLOW.
					break;

				case UI_Element::INPUTBOX:
					App->render->DrawQuad((*elem)->GetHitbox(), 255, 0, 255, 255, false, false);		//UI_Input Box will be PURPLE.
					break;
				}
			}
		}
	}
}

// class Gui ---------------------------------------------------

