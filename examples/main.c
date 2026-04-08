#include <pch.h>
#include <stdio.h>

#include <TuiScreen/include.h>

#include <stdbool.h>

int main()
{
	int width = 118;
	int height = 26;

	struct screen screen;
	screen_init(&screen, width, height);

	screen_set_border(&screen,
		"+++"
		"| |"
		"+++"
	);

	screen.screen_origin = TUI_SCREEN_ORIGIN_CENTER;
	screen.sprite_origin = TUI_SPRITE_ORIGIN_CENTER;

	const char* logo =
		"=======  |     |  =======                                        \n"
		"   |     |     |     |          |===   ===  |==  |==  |== |=|  | \n"
		"   |     |     |     |          |==|   |    |==  |==  |== | || | \n"
		"   |     |     |     |          ===|   ===  | |  |==  |== |  |=| \n"
		"   |     |=====|  =======                                        \n";

	screen.wrap_mode = TUI_WRAP_MODE_LOOP; 

	float x_pos = 0.0f;
	float y_pos = height / 2.0f;

	while(true)
	{
		screen_clear(&screen, ' ');

		//screen_draw_sprite(&screen, logo, x_pos, y_pos);
		screen_draw_sprite(&screen, logo, 0, 0);

		screen_print(&screen);

		x_pos += 0.01f;
		y_pos += 0.001f;
	}

	return 0;
}