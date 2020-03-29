#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Scene.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	ui_debug = false;
	escape = true;

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
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
		SetElementsVisibility(App->scene->window, !App->scene->window->isVisible);
		SetElementsVisibility(App->scene->scrollWindow, !App->scene->scrollWindow->isVisible);
	}
	
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{	
	//escape = true;
	
	for (p2List_item<UI*>* element_iterator = elements.start; element_iterator != NULL; element_iterator = element_iterator->next)
	{
		switch (element_iterator->data->element)
		{
		case UI_Element::IMAGE:
			if (element_iterator->data->isVisible)
			{
				element_iterator->data->Draw();
			}

			break;

		case UI_Element::TEXT:
			if (element_iterator->data->isVisible)
			{
				element_iterator->data->Draw();
			}

			break;

		case UI_Element::BUTTON:
			if (element_iterator->data->isVisible)
			{
				element_iterator->data->Draw();
			}

			break;

		case UI_Element::SCROLLBAR:
			if (element_iterator->data->isVisible)
			{
				element_iterator->data->Draw();
			}

			break;

		case UI_Element::INPUTBOX:
			if (element_iterator->data->isVisible)
			{
				element_iterator->data->Draw();
			}
			
			break;
		}
	}

	Debug_UI();

	return escape;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	//Iterate the elements list and frees all allocated memory.
	for (p2List_item<UI*>* element_iterator = elements.start; element_iterator != NULL; element_iterator = element_iterator->next)
	{
		element_iterator->data->CleanUp();
		RELEASE(element_iterator->data);
	}

	elements.clear();

	return true;
}

// const getter for atlas
/*const*/ SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

//----------------------------------- UI ELEMENT CREATION METHODS -----------------------------------
UI* j1Gui::CreateImage(UI_Element element, int x, int y, SDL_Rect hitbox, bool isVisible, bool isInteractible, bool isDraggable, UI* parent)
{
	UI* elem = nullptr;

	elem = new UI_Image(element, x, y, hitbox, isVisible, isInteractible, isDraggable, parent);

	if (elem != nullptr)
	{
		elements.add(elem);
	}

	return elem;
}

UI* j1Gui::CreateText(UI_Element element, int x, int y, SDL_Rect hitbox, _TTF_Font* font, SDL_Color fontColour, bool isVisible, bool isInteractible, bool isDraggable,
					UI* parent, p2SString* string, p2SString* hoverString, p2SString* leftClickString, p2SString* rightClickString)
{
	UI* elem = nullptr;

	elem = new UI_Text(element, x, y, hitbox, font, fontColour, isVisible, isInteractible, isDraggable, parent, string, hoverString, leftClickString, rightClickString);

	if (elem != nullptr)
	{
		elements.add(elem);
	}

	return elem;
}

UI* j1Gui::CreateButton(UI_Element element, int x, int y, bool isVisible, bool isInteractible, bool isDraggable, UI* parent, SDL_Rect* idle, SDL_Rect* hover, SDL_Rect* clicked)
{
	UI* elem = nullptr;

	elem = new UI_Button(element, x, y, isVisible, isInteractible, isDraggable, parent, idle, hover, clicked);

	if (elem != nullptr)
	{
		elements.add(elem);
	}

	return elem;
}

UI* j1Gui::CreateUI_Window(UI_Element element, int x, int y, SDL_Rect hitbox, bool isVisible, bool isInteractible, bool isDraggable, UI* parent)
{
	UI* elem = nullptr;

	elem = new UI_Window(element, x, y, hitbox, isVisible, isInteractible, isDraggable, parent);

	if (elem != nullptr)
	{
		elements.add(elem);
	}

	return elem;
}

UI* j1Gui::CreateInputBox(UI_Element element, int x, int y, SDL_Rect hitbox, _TTF_Font* font, SDL_Color fontColour, SDL_Rect cursor, SDL_Color cursorColour, iPoint textOffset, 
					float blinkFrequency, bool isVisible, bool isInteractible, bool isDraggable, UI* parent, p2SString* defaultString)
{
	UI* elem = nullptr;

	elem = new UI_InputBox(element, x, y, hitbox, font, fontColour, cursor, cursorColour, textOffset, blinkFrequency, isVisible, isInteractible, isDraggable, parent, defaultString);

	if (elem != nullptr)
	{
		elements.add(elem);
	}

	return elem;
}

UI* j1Gui::CreateScrollbar(UI_Element element, int x, int y, SDL_Rect hitbox, SDL_Rect thumbSize, iPoint thumbOffset, SDL_Rect dragArea, float dragFactor, bool dragXAxis, bool dragYAxis,
					bool invertedScrolling, bool isVisible, bool isInteractible, bool isDraggable, UI* parent, SDL_Rect* scrollMask, iPoint maskOffset)
{
	UI* elem = nullptr;

	elem = new UI_Scrollbar(element, x, y, hitbox, thumbSize, thumbOffset, dragArea, dragFactor, dragXAxis, dragYAxis, invertedScrolling,
					isVisible, isInteractible, isDraggable, parent, scrollMask, maskOffset);

	if (elem != nullptr)
	{
		elements.add(elem);
	}

	return elem;
}

//--------------------------------- INPUT PROCESSING METHODS ---------------------------------
void j1Gui::OnEventCall(UI* element, UI_Event ui_event)
{
	if (element == App->scene->button && ui_event == UI_Event::UNCLICKED)				//If the pointer received is the UI_Button* button pointer of Scene.h and event = clicked. 
	{
		App->gui->ui_debug = !App->gui->ui_debug;										//Enables / Disables UI Debug Mode.
	}

	if (element == App->scene->escButton && ui_event == UI_Event::UNCLICKED)			//If the pointer received is the UI_Button* escbutton pointer of Scene.h and event = clicked.
	{
		escape = false;
	}

	if (element == App->scene->draggableButton && ui_event == UI_Event::UNCLICKED)
	{
		App->gui->ui_debug = !App->gui->ui_debug;
	}

	if (element == App->scene->interactibleText && ui_event == UI_Event::UNCLICKED)
	{
		App->gui->ui_debug = !App->gui->ui_debug;
	}
} 

// --- Method to return the foremost element of the UI. (First in inverse order of draw)
UI* j1Gui::FirstElementUnderMouse() const
{
	UI* firstElement = nullptr;

	for (p2List_item<UI*>* iterator = elements.start; iterator != NULL; iterator = iterator->next)
	{
		if (ElementCanBeClicked(iterator->data))													//Checks that the element being iterated has the mouse on it.
		{
			firstElement = iterator->data;															//The element being iterated is assigned to firstElement.
		}
	}

	if (firstElement != nullptr)
	{
		return firstElement;																		//The last element that was checked to have the mouse on it will be returned.
	}
}

bool j1Gui::ElementCanBeClicked(UI* clickedElement) const
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
void j1Gui::PassFocus()
{
	if (iteratedElement == nullptr)
	{
		iteratedElement = elements.start;
	}
	
	if (focusedElement == nullptr)
	{
		for (iteratedElement; iteratedElement != NULL; iteratedElement = iteratedElement->next)		//Loop that is used to find the first interactible element of the elments list.
		{
			if (ElementCanBeFocused(iteratedElement->data))											//If the element being iterated fulfills all focus conditions.
			{
				focusedElement = iteratedElement->data;												//UI* focusedElement is set with the UI* of the element being iterated.
				break;																				//The loop is stopped.
			}
		}

		return;																						//Stops the function here so the focus remains in the first interactible element.
	}

	for (iteratedElement; iteratedElement != NULL; iteratedElement = iteratedElement->next)			//Loop that is used to find the next interactible element of the elments list.
	{
		if (iteratedElement->next != NULL)															//If the next element of the list is not NULL.
		{
			if (ElementCanBeFocused(iteratedElement->next->data))									//If the next element of the list fulfills all focus conditions.
			{
				focusedElement = iteratedElement->next->data;										//UI* focusedElement is set with the UI* of the element next to the element being iterated. 
				iteratedElement = iteratedElement->next;											//The element being iterated is set to the next element in the list.
				break;																				//The loop is stopped so the focus remains in the interactible element that now has the focus.
			}
		}
		else																						//If the next element of the list is NULL.
		{
			iteratedElement = nullptr;																//The list_item is set to nullptr.
			focusedElement = nullptr;																//The UI* focused element is set to nullptr, which efectively disables the focus.
			break;																					//The loop is stopped so no element regains the focus.
		}
	}
}

// --- Method that returns true if the passed element is a visible BUTTON, INPUTBOX or a SCROLLBAR
bool j1Gui::ElementCanBeFocused(UI* focusElement) const
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
bool j1Gui::ElementHasChilds(UI* parentElement) const
{
	bool ret = false;
	
	for (p2List_item<UI*>* iterator = elements.start; iterator != NULL; iterator = iterator->next)
	{
		if (iterator->data->parent == parentElement)
		{
			ret = true;
			break;
		}
	}

	return ret;
}

void j1Gui::UpdateChilds(UI* parentElement)
{
	//Check ElementHasChilds() here instead than in the elements?
	for (p2List_item<UI*>* child = elements.start; child != NULL; child = child->next)
	{
		if (child->data->parent == parentElement)
		{
			child->data->prevMousePos = child->data->parent->prevMousePos;			//The prevMousePos of the element being iterated is set with the parent's prev mouse pos.
			child->data->DragElement();												//The child is also dragged, just as the parent.

			if (ElementHasChilds(child->data))										//If the first child also has child elements, then they are updated the same way.
			{
				UpdateChilds(child->data);											//Recursive function, maybe avoid?
			}

			/*child->data->SetScreenPos(child->data->GetLocalPos() + child->data->parent->GetScreenPos());
			child->data->SetHitbox({ child->data->GetScreenPos().x, child->data->GetScreenPos().y , child->data->GetHitbox().w, child->data->GetHitbox().h});*/
		}
	}
}

void j1Gui::SetElementsVisibility(UI* parentElement, bool state)
{	
	for (p2List_item<UI*>* child = elements.start; child != NULL; child = child->next)
	{
		if (child->data->parent == parentElement)									//If the parent of the iterated element is parentElement.
		{
			child->data->isVisible = state;											//Enables/Disables the iterated child's visibility. Changes isVisible from true to false and viceversa.

			if (ElementHasChilds(child->data))										//If the first child also has child elements, then they are updated the same way.
			{
				SetElementsVisibility(child->data, state);							//Recursive function, maybe avoid?
			}
		}
	}

	//parentElement->isVisible = !parentElement->isVisible;							//Enables/Disables the parent element's visibility. Changes isVisible from true to false and viceversa.	
	parentElement->isVisible = state;												//Enables/Disables the parent element's visibility. Changes isVisible from true to false and viceversa.	
}

//----------------------------------- UI DEBUG METHOD -----------------------------------
void j1Gui::Debug_UI()
{
	if (ui_debug == true)
	{
		for (p2List_item<UI*>* element_iterator = elements.start; element_iterator != NULL; element_iterator = element_iterator->next)
		{	
			if (element_iterator->data->isVisible)
			{
				switch (element_iterator->data->element)
				{
				case UI_Element::EMPTY:
					App->render->DrawQuad(element_iterator->data->GetHitbox(), 255, 255, 255, 255, false, false);		//UI_Empty will be WHITE.
						break;
				
				case UI_Element::IMAGE:
					App->render->DrawQuad(element_iterator->data->GetHitbox(), 0, 0, 255, 255, false, false);			//UI_Image will be BLUE.

					break;

				case UI_Element::TEXT:
					App->render->DrawQuad(element_iterator->data->GetHitbox(), 0, 255, 0, 255, false, false);			//UI_Text will be GREEN.

					break;

				case UI_Element::BUTTON:
					App->render->DrawQuad(element_iterator->data->GetHitbox(), 255, 0, 0, 255, false, false);			//UI_Button will be RED.

					break;

				case UI_Element::SCROLLBAR:
					App->render->DrawQuad(element_iterator->data->GetHitbox(), 255, 255, 0, 255, false, false);			//UI_Scrollbar will be YELLOW.
					break;

				case UI_Element::INPUTBOX:
					App->render->DrawQuad(element_iterator->data->GetHitbox(), 255, 0, 255, 255, false, false);			//UI_Input Box will be PURPLE.
					break;
				}
			}
		}
	}
}

// class Gui ---------------------------------------------------

