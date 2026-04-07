#include <pch.h>
#include <stdio.h>

#include <TuiScreen/include.h>

int main()
{
	int width = 112;
	int height = 16;

	struct screen screen;
	screen_init(&screen, width, height);

	screen_clear(&screen, ' ');
	screen_set_pixel(&screen, width / 2, height / 2, ':');
	screen_set_pixel(&screen, width / 2 + 1, height / 2, ')');
	
	screen_print(&screen);

	return 0;
}