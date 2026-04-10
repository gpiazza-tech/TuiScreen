#pragma once

#include <windows.h>
#include <winuser.h>

#define TUI_KEY_UP VK_UP
#define TUI_KEY_DOWN VK_DOWN
#define TUI_KEY_LEFT VK_LEFT
#define TUI_KEY_RIGHT VK_RIGHT

short input_key_down(int keycode)
{
	return GetKeyState(keycode) < 0;
}