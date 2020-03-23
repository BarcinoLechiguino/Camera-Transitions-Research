#include "p2Defs.h"
#include "p2Log.h"
#include "Application.h"
#include "Input.h"
#include "Fonts.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "Gui.h"
#include "FirstScene.h"

FirstScene::FirstScene() : Module()
{
	name.create("scene");
}

// Destructor
FirstScene::~FirstScene()
{}

// Called before render is available
bool FirstScene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool FirstScene::Start()
{
	App->map->Load("iso_walk.tmx");

	// TODO 3: Create the banner (rect {485, 829, 328, 103}) as a UI element
	SDL_Rect rect{ 485, 829, 328, 103 };
	SDL_Rect winRect{ 0, 512, 483, 512 };

	window = (UI_Image*)App->gui->CreateImage(UI_Element::IMAGE, 225, 25, winRect, true, false, true, NULL);		//OnCallEvent Overlap
	banner = (UI_Image*)App->gui->CreateImage(UI_Element::IMAGE, 300, 100, rect, true, false, false, window);

	// TODO 4: Create the text "Hello World" as a UI element
	SDL_Rect textHitbox{ 432, 75, 65, 20};
	SDL_Rect interactibleTextHitbox{ 432, 75, 134, 20};
	p2SString bufferString = "Hello World";
	p2SString interactibleString = "This string is interactible.";
	_TTF_Font* font = App->font->Load("fonts/open_sans/OpenSans-SemiboldItalic.ttf");
	SDL_Color fontRgb = { 255, 255, 255, 255 };

	interactibleText = (UI_Text*)App->gui->CreateText(UI_Element::TEXT, 280, 75, interactibleTextHitbox, font, fontRgb, true, true, false, window, &interactibleString);
	text = (UI_Text*)App->gui->CreateText(UI_Element::TEXT, 432, 75, textHitbox, font, fontRgb, true, false, false, window, &bufferString);

	
	//Creating a button:
	SDL_Rect buttonHitbox	= { 642,169,229,69 };
	SDL_Rect idle			= { 642,169,229,69 };
	SDL_Rect hover			= { 0,113,229,69 };
	SDL_Rect clicked		= { 411,169,229,69 };

	SDL_Rect buttonLabelHitbox{ 432, 75, 45, 18 };
	p2SString buttonString = "BUTTON";

	button = (UI_Button*)App->gui->CreateButton(UI_Element::BUTTON, 350, 205, true, true, false, window, &idle, &hover, &clicked);
	escButton = (UI_Button*)App->gui->CreateButton(UI_Element::BUTTON, 350, 280, true, true, false, window, &idle, &hover, &clicked);
	
	draggableButton = (UI_Button*)App->gui->CreateButton(UI_Element::BUTTON, 350, 425, true, true, true, window, &idle, &hover, &clicked);
	buttonLabel = (UI_Text*)App->gui->CreateText(UI_Element::TEXT, 442, 450, buttonLabelHitbox, font, fontRgb, true, false, false, draggableButton, &buttonString);

	//draggableButton2 = (UI_Button*)App->gui->CreateButton(UI_Element::BUTTON, 350, 425, true, true, true, window, &idle, &hover, &clicked);

	//Creating a text box:
	SDL_Rect inputBoxBg		= { 488, 569, 344, 61 };
	SDL_Rect inputBoxTxt	= { 0, 0, 325, 30 };
	SDL_Rect textCursor		= {0, 0, 3, 40};

	SDL_Color fontColour	= { 255, 255, 255, 255 };
	SDL_Color cursorColour	= { 255, 255, 255, 255 };
	float blinkFrequency	= 0.5f;

	p2SString defaultTxt	= "Input Text Here";
	_TTF_Font* inputFont	= App->font->Load("fonts/open_sans/OpenSans-SemiboldItalic.ttf", 30);
	iPoint textOffset		= { 10, 9 };

	inputBox = (UI_InputBox*)App->gui->CreateInputBox(UI_Element::INPUTBOX, 295, 355, inputBoxBg, inputFont, fontColour, textCursor, cursorColour, textOffset,
												blinkFrequency, true, true, false, window, &defaultTxt);

	//Creating a Scrollbar:
	SDL_Rect scrollbarBar		= { 973, 786, 11, 158 };
	//SDL_Rect scrollbarThumb		= { 843, 330, 15, 10 };
	SDL_Rect scrollbarThumb		= { 1004, 439, 15, 10 };
	iPoint thumbOffset			= { -2, 0 };
	SDL_Rect scrollMask			= { 0, 0, 350, 158 };
	iPoint maskOffset			= { -360, 0 };
	SDL_Rect dragArea			= { 0, 0, 11, 158 };
	float dragFactor			= 0.2f;

	char* txt = "Lorem ipsum dolor sit amet,\n consectetur adipiscing elit.\n Integer blandit arcu turpis,\n vitae blandit lacus \n malesuada commodo.";
	p2SString scrollTxt = "Lorem ipsum dolor sit amet";
	_TTF_Font* scrollFont = App->font->Load("fonts/open_sans/OpenSans-Regular.ttf", 24);
	SDL_Color scrollFontColour = { 255, 255, 255, 255 };

	scrollWindow = (UI_Image*)App->gui->CreateImage(UI_Element::IMAGE, 225, 25, winRect, false, false, false, NULL);
	scrollText = (UI_Text*)App->gui->CreateText(UI_Element::TEXT, 290, 325, textHitbox, scrollFont, scrollFontColour, false, false, false, scrollWindow, &scrollTxt);
	scrollInputBox = (UI_InputBox*)App->gui->CreateInputBox(UI_Element::INPUTBOX, 295, 155, inputBoxBg, inputFont, fontColour, textCursor, cursorColour, textOffset,
													blinkFrequency, false, true, false, scrollWindow, &defaultTxt);

	scrollbar = (UI_Scrollbar*)App->gui->CreateScrollbar(UI_Element::SCROLLBAR, 650, 325, scrollbarBar, scrollbarThumb, thumbOffset, dragArea, dragFactor, false, true, true,
													false, false, false, scrollWindow, &scrollMask, maskOffset);
	
	scrollbar->LinkScroll(scrollText);
	//thumbo = (UI_Image*)App->gui->CreateImage(UI_Element::IMAGE, 650 + thumbOffset.x, 300 + thumbOffset.y, scrollbarThumb, true, true, true, NULL);

	return true;
}

// Called each loop iteration
bool FirstScene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool FirstScene::Update(float dt)
{
	// Gui ---
	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
	{
		if (App->gui->ui_debug == false)
		{
			App->gui->ui_debug = true;
		}
		else
		{
			App->gui->ui_debug = false;
		}
	}
	// -------
	
	//if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	//	App->LoadGame("save_game.xml");

	//if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
	//	App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= floor(200.0f * dt);

	App->map->Draw();

	return true;
}

// Called each loop iteration
bool FirstScene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool FirstScene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
