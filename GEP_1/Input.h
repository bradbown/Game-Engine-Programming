#pragma once

#include <SDL.h>
#include "ref.h"


class Application;

class Input
{

	friend class Application;

public:
	Input();
	~Input();


	void update();

	bool Quit;

	int mouse_x, mouse_y;
	bool cmd_mouseleft, cmd_mouseleftUp, cmd_mouseright, cmd_mouserightUp;
	bool cmd_s, cmd_a, cmd_d, cmd_w, cmd_z, cmd_x, cmd_c;
	bool cmd_1, cmd_2, cmd_space, cmd_q;
	bool once;

private:

	SDL_Event eventQueue;

	static bool getKey(int keyCode);
	static bool getKeyDown(int keyCode); // Was the key pressed this frame?
	static bool getKeyUp(int keyCode);

	static std::vector<int> keys;
	static std::vector<int> upKeys;
	static std::vector<int> downKeys;

	bool keyDown;

	void keyboard(unsigned char key);
	void keyboardUp(unsigned char key);

	void _keyboard(int key);
	void _keyboardUp(int key);

};