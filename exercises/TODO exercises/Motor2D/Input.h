#ifndef __INPUT_H__
#define __INPUT_H__

#include "Module.h"
#include "p2Point.h"

//#define NUM_KEYS 352
#define NUM_MOUSE_BUTTONS 5
//#define LAST_KEYS_PRESSED_BUFFER 50

struct SDL_Rect;

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class Input : public Module
{

public:

	Input();

	// Destructor
	virtual ~Input();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	// Called before quitting
	bool CleanUp();

	// Gather relevant win events
	bool GetWindowEvent(EventWindow ev);

	// Check key states (includes mouse and joy buttons)
	KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	KeyState GetMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}

public:
	// Check if a certain window event happened
	bool GetWindowEvent(int code);

	// Get mouse / axis position
	void GetMousePosition(int &x, int &y);
	void GetMouseMotion(int& x, int& y);
	void GetMousewheelScrolling(int&x, int& y);

	iPoint GetMouseToWorld() const;										// Method that will return a vector with the position of the mouse in relation to the world.

	// Text Input
	void TextInput();
	void EditTextInputs();

	const char* GetInputText();
	int GetInputTextLength();
	int GetCursorIndex();

	void CheckNewTextInput(const char* newTextInput);
	void AddTextInput(const char* origin);
	void InsertTextInput(const char* origin);

	bool CutInputText(unsigned int begin, unsigned int end = 0);
	char* GetCutText(unsigned int begin, unsigned int end = -1, bool returnFirstPart = false, bool returnLastPart = false);

	void ClearTextInput();
	void DeleteTextInput(int positionIndex);
	
private:
	void Allocate(int required_memory);

private:
	bool		windowEvents[WE_COUNT];
	KeyState*	keyboard;
	KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	int			mouse_motion_x;
	int			mouse_motion_y;
	int			mouse_x;
	int			mouse_y;
	int			mouse_scroll_x;
	int			mouse_scroll_y;
	
	char*		input_string;
	int			text_size;
	bool		textInputEnabled;
	int			prevLength;
	int			cursorIndex;
};

#endif // __INPUT_H__