#include <pch.h>
#include "screen.h"

#include <screen/border.h>
#include <screen/settings.h>
#include <screen/sprite.h>

#include <stdio.h>
#include <string.h>

void screen_init(struct screen* screen, int width, int height)
{
	screen->width = width;
	screen->height = height;

	screen->wrap_mode = TUI_WRAP_MODE_IGNORE;

	border_init(&screen->border,
		"***"
		"* *"
		"***"
	);

	int buffer_width = width + 3;	// + 2 for edges, + 1 for '\n'
	int buffer_height = height + 2; // + 2 for edges

	screen->buffer_size = buffer_width * buffer_height + 1;
	screen->buffer[screen->buffer_size];

	screen_set_border(screen, &screen->border);

	// NEW LINES
	for (int i = 0; i < buffer_height; i++)
	{
		screen->buffer[buffer_width + buffer_width * i - 1] = '\n';
	}

	// NULL TERMINATOR
	screen->buffer[screen->buffer_size - 1] = '\0';
}

void screen_print(struct screen* screen)
{
	char new_lines[] = 
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	printf("%s%s", new_lines, screen->buffer);
}

void screen_clear(struct screen* screen, char c)
{
	int buffer_width = screen->width + 3;	// + 2 for edges, + 1 for '\n'
	int buffer_height = screen->height + 2; // + 2 for edges

	int i = buffer_width + 1;
	for (int y = 0; y < screen->height; y++)
	{
		for (int x = 0; x < screen->width; x++)
		{
			screen->buffer[i] = c;
			i++;
		}
		i += 3; // skips '\n' and the left and right edges
	}
}

void screen_set_pixel(struct screen* screen, char c, int x, int y)
{
	int buffer_width = screen->width + 3;	// + 2 for edges, + 1 for '\n'
	int buffer_height = screen->height + 2; // + 2 for edges

	// check for out of bounds
	if (x < 0 || y < 0 || x >= screen->width || y >= screen->height)
	{
		switch (screen->wrap_mode)
		{
		case TUI_WRAP_MODE_IGNORE:
			return;
		case TUI_WRAP_MODE_LOOP:
			x %= screen->width;
			y %= screen->height;
			break;
		default:
			break;
		}
	}

	screen->buffer[buffer_width + y * buffer_width + x + 1] = c; // + y to skip '\n' on every line
}

void screen_set_border(struct screen* screen, struct border* border)
{
	int buffer_width = screen->width + 3;	// + 2 for edges, + 1 for '\n'
	int buffer_height = screen->height + 2; // + 2 for edges

	screen->border = *border;

	// TOP AND BOTTOM EDGES
	for (int i = 0; i < screen->width; i++)
	{
		screen->buffer[i + 1] = screen->border.edge_top;
		screen->buffer[screen->buffer_size - 3 - i] = screen->border.edge_bottom;
	}

	// LEFT AND RIGHT EDGES
	for (int i = 0; i < screen->height; i++)
	{
		screen->buffer[buffer_width + i * buffer_width] = screen->border.edge_left;
		screen->buffer[buffer_width + (i + 1) * buffer_width - 2] = screen->border.edge_right;
	}

	// CORNERS
	screen->buffer[0] = screen->border.corner_top_left;
	screen->buffer[buffer_width - 2] = screen->border.corner_top_right;
	screen->buffer[buffer_height * buffer_width - buffer_width] = screen->border.corner_bottom_left;
	screen->buffer[buffer_height * buffer_width - 2] = screen->border.corner_bottom_right;
}

void screen_draw_sprite(struct screen* screen, sprite sprite, int x, int y)
{
	int sprite_len = strlen(sprite);

	int current_x = x;
	int current_y = y;

	for (int i = 0; i < sprite_len; i++)
	{
		if (sprite[i] == ' ')
		{
			current_x++;
			continue;
		}

		if (sprite[i] == '\n')
		{
			current_x = x;
			current_y++;
			continue;
		}

		screen_set_pixel(screen, sprite[i], current_x, current_y);
		current_x++;
	}
}