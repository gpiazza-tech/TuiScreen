#pragma once

#include <screen/settings.h>

#define _TUI_MAX_SCREEN_WIDTH 200
#define _TUI_MAX_SCREEN_HEIGHT 200

struct screen
{
	int width;
	int height;

	char buffer[_TUI_MAX_SCREEN_WIDTH * _TUI_MAX_SCREEN_HEIGHT + _TUI_MAX_SCREEN_HEIGHT];
	int buffer_size;

	// SETTINGS
	enum wrap_mode wrap_mode;
	enum screen_origin screen_origin;
	enum sprite_origin sprite_origin;
};

void screen_init(struct screen* screen, int width, int height);
void screen_print(struct screen* screen);

void screen_clear(struct screen* screen, char c);
void screen_set_pixel(struct screen* screen, char c, int x, int y);

void screen_set_border(struct screen* screen, const char* border);

void screen_draw_sprite(struct screen* screen, const char* sprite, int x, int y);