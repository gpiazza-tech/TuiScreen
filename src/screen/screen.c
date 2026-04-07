#include <pch.h>
#include "screen.h"

#include <screen/border.h>

#include <stdio.h>

void screen_init(struct screen* screen, int width, int height)
{
	screen->width = width;
	screen->height = height;

	border_init(&screen->border,
		"***"
		"* *"
		"***"
	);

	int buffer_width = width + 3;	// + 2 for edges, + 1 for '\n'
	int buffer_height = height + 2; // + 2 for edges

	screen->buffer_size = buffer_width * buffer_height;
	screen->buffer[screen->buffer_size];

	screen_set_border(screen, &screen->border);

	// NEW LINES
	for (int i = 0; i < buffer_height - 1; i++)
	{
		screen->buffer[buffer_width + buffer_width * i - 1] = '\n';
	}

	// NULL TERMINATOR
	screen->buffer[screen->buffer_size - 1] = '\0';
}

void screen_print(struct screen* screen)
{
	printf(screen->buffer);
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

void screen_set_pixel(struct screen* screen, int x, int y, char c)
{
	int buffer_width = screen->width + 3;	// + 2 for edges, + 1 for '\n'
	int buffer_height = screen->height + 2; // + 2 for edges

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