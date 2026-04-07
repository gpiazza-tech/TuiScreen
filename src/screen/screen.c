#include <pch.h>
#include "screen.h"

#include <stdio.h>

void screen_init(struct screen* screen, int width, int height)
{
	screen->width = width;
	screen->height = height;

	// + height allows inserting '\n' at the end of every row
	screen->buffer[width * height + height];

	for (int i = 1; i < screen->height; i++)
	{
		screen->buffer[width * i + i - 1] = '\n';
	}
	screen->buffer[width * height + height - 1] = '\0';
}

void screen_print(struct screen* screen)
{
	printf(screen->buffer);
}

void screen_clear(struct screen* screen, char c)
{
	int i = 0;
	for (int y = 0; y < screen->height; y++)
	{
		for (int x = 0; x < screen->width; x++)
		{
			screen->buffer[i] = c;
			i++;
		}
		i++; // skips '\n'
	}
}

void screen_set_pixel(struct screen* screen, int x, int y, char c)
{
	screen->buffer[y * screen->width + x + y] = c; // + y to skip '\n' on every line
}