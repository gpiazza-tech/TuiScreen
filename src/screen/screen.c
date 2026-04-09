#include <pch.h>
#include "screen.h"

#include <screen/settings.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void _buffer_set_from_start(struct screen* screen, int i, char c)
{
	screen->buffer[screen->buffer_start_offset + i] = c;
}

void _buffer_set_from_end(struct screen* screen, int i, char c)
{
	screen->buffer[screen->buffer_size - 1 - i] = c;
}

void screen_init(struct screen* screen, int width, int height)
{
	screen->width = width;
	screen->height = height;

	screen->wrap_mode = TUI_WRAP_MODE_IGNORE;
	screen->screen_origin = TUI_SCREEN_ORIGIN_TOP_LEFT;
	screen->sprite_origin = TUI_SPRITE_ORIGIN_TOP_LEFT;

	int buffer_width = width + 3;	// + 2 for edges, + 1 for '\n'
	int buffer_height = height + 2; // + 2 for edges

	screen->buffer_start_offset = 6; // "\033[999A" is 6 characters
	screen->buffer[0] = '\033';
	screen->buffer[1] = '[';
	screen->buffer[2] = '9';
	screen->buffer[3] = '9';
	screen->buffer[4] = '9';
	screen->buffer[5] = 'A';

	screen->buffer_size = screen->buffer_start_offset + buffer_width * buffer_height;

	screen_set_border(screen,
		"   "
		"   "
		"   "
	);

	// NEW LINES
	for (int i = 0; i < buffer_height - 1; i++)
	{
		_buffer_set_from_start(screen, buffer_width - 1 + buffer_width * i, '\n');
	}
	
	// NULL TERMINATOR
	_buffer_set_from_end(screen, 0, '\0');

	screen_clear(screen, ' ');
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
			_buffer_set_from_start(screen, i, c);
			i++;
		}
		i += 3; // skips '\n' and the left and right edges
	}
}

static void _screen_transform_position(struct screen* screen, int* x, int* y)
{
	switch (screen->screen_origin)
	{
	case TUI_SCREEN_ORIGIN_TOP_LEFT:
		break;
	case TUI_SCREEN_ORIGIN_BOTTOM_LEFT:
		*y = screen->height - 1 - *y;
		break;
	case TUI_SCREEN_ORIGIN_TOP_RIGHT:
		*x = screen->width - 1 - *x;
		break;
	case TUI_SCREEN_ORIGIN_BOTTOM_RIGHT:
		*x = screen->width - 1 - *x;
		*y = screen->height - 1 - *y;
		break;
	case TUI_SCREEN_ORIGIN_CENTER:
		*x = screen->width / 2 - 1 + *x;
		*y = screen->height / 2 - 1 - *y;
		break;
	default:
		break;
	}
}

static void _screen_set_pixel_no_transform(struct screen* screen, char c, int x, int y)
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

	if (x < 0)
		x = screen->width - abs(x);
	if (y < 0)
		y = screen->height - abs(y);

	_buffer_set_from_start(screen, buffer_width + y * buffer_width + x + 1, c); // + y to skip '\n' on every line
}

void screen_set_pixel(struct screen* screen, char c, int x, int y)
{
	_screen_transform_position(screen, &x, &y);
	_screen_set_pixel_no_transform(screen, c, x, y);
}

void screen_set_border(struct screen* screen, const char* characters)
{
	int corner_top_left			= characters[0];
	int edge_top				= characters[1];
	int corner_top_right		= characters[2];
	int edge_left				= characters[3];
	int edge_right				= characters[5];
	int corner_bottom_left		= characters[6];
	int edge_bottom				= characters[7];
	int corner_bottom_right		= characters[8];

	int buffer_width = screen->width + 3;	// + 2 for edges, + 1 for '\n'
	int buffer_height = screen->height + 2; // + 2 for edges

	// TOP AND BOTTOM EDGES
	for (int i = 0; i < screen->width; i++)
	{
		_buffer_set_from_start(screen, i + 1, edge_top);
		_buffer_set_from_end(screen, 2 + i, edge_bottom);
	}

	// LEFT AND RIGHT EDGES
	for (int i = 0; i < screen->height; i++)
	{
		_buffer_set_from_start(screen, buffer_width + i * buffer_width, edge_left);
		_buffer_set_from_start(screen, buffer_width + (i + 1) * buffer_width - 2, edge_right);
	}

	// CORNERS
	_buffer_set_from_start(screen, 0, corner_top_left);
	_buffer_set_from_start(screen, buffer_width - 2, corner_top_right);

	_buffer_set_from_start(screen, buffer_height * buffer_width - buffer_width, corner_bottom_left);
	_buffer_set_from_start(screen, buffer_height * buffer_width - 2, corner_bottom_right);
}

static void _screen_transform_sprite_position(struct screen* screen, const char* sprite, int* x, int* y)
{
	if (screen->sprite_origin == TUI_SPRITE_ORIGIN_TOP_LEFT)
		return;

	int len = strlen(sprite);

	int height = 0;
	for (int i = 0; i < len; i++)
	{
		if (sprite[i] == '\n')
			height++;
	}

	int width = 0;
	for (int i = 0; i < len; i++)
	{
		if (sprite[i] == '\n')
			break;
		width++;
	}

	switch (screen->sprite_origin)
	{
	// case TUI_SPRITE_ORIGIN_TOP_LEFT already handled
	case TUI_SPRITE_ORIGIN_BOTTOM_LEFT:
		*y -= height - 1;
		break;
	case TUI_SPRITE_ORIGIN_TOP_RIGHT:
		*x -= width - 1;
		break;
	case TUI_SPRITE_ORIGIN_BOTTOM_RIGHT:
		*x -= width - 1;
		*y -= height - 1;
		break;
	case TUI_SPRITE_ORIGIN_CENTER:
		*x -= width / 2 - 1;
		*y -= height / 2 - 1;
		break;
	default:
		break;
	}
}

void screen_draw_sprite(struct screen* screen, const char* sprite, int x, int y)
{
	_screen_transform_position(screen, &x, &y);
	_screen_transform_sprite_position(screen, sprite, &x, &y);

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

		_screen_set_pixel_no_transform(screen, sprite[i], current_x, current_y);
		current_x++;
	}
}

void screen_print(struct screen* screen)
{
	puts(screen->buffer);
}
