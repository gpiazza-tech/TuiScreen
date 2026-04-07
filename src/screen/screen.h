#pragma once

#define TUI_MAX_WIDTH 100
#define TUI_MAX_HEIGHT 100

struct screen
{
	int width;
	int height;

	char buffer[TUI_MAX_WIDTH * TUI_MAX_HEIGHT + TUI_MAX_HEIGHT];
};

void screen_init(struct screen* screen, int width, int height);
void screen_print(struct screen* screen);

void screen_clear(struct screen* screen, char c);
void screen_set_pixel(struct screen* screen, int x, int y, char c);