#pragma once

#include <screen/settings.h>

struct screen
{
	int width;
	int height;

	char* _buffer;
	int _buffer_size;
	int _buffer_start_offset; // "\033[999A" will be inserted at the beginning

	// SETTINGS
	enum wrap_mode wrap_mode;
	enum screen_origin screen_origin;
	enum sprite_origin sprite_origin;
};

void screen_init(struct screen* screen, int width, int height);
void screen_print(struct screen* screen);

void screen_clear(struct screen* screen, char c);
void screen_set_value(struct screen* screen, float value, int x, int y);
void screen_set_pixel(struct screen* screen, char c, int x, int y);

void screen_set_border(struct screen* screen, const char* border);

void screen_draw_sprite(struct screen* screen, const char* sprite, int x, int y);