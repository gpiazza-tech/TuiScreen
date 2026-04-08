#include <pch.h>
#include <stdio.h>
#include <threads.h>
#include <math.h>

#include <TuiScreen/include.h>

#include <stdbool.h>

bool pressed_enter = false;

int get_input()
{
	while (true)
	{
		char* out;
		scanf("%s", &out);
		pressed_enter = true;
	}
}

int main()
{
	// THREADS

	thrd_t input_thrd;
	thrd_create(&input_thrd, &get_input, NULL);

	// INIT SCREEN
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
	screen.wrap_mode = TUI_WRAP_MODE_IGNORE;

	const char* logo =
		" =======  |     |  =======                                        \n"
		"    |     |     |     |          |===   ===  |==  |==  |== |=|  | \n"
		"    |     |     |     |          |==|   |    |==  |==  |== | || | \n"
		"    |     |     |     |          ===|   ===  | |  |==  |== |  |=| \n"
		"    |     |=====|  =======                                        \n";

	const char* bird =
		"    _--  \n"
		"   /  -| \n"
		"  |/-/_ >\n";

	float logo_x_pos = 0.0f;
	float bird_y_pos = 0.0f;
	float bird_y_vel = 0.0f;
	float bird_jump_force = 0.005f;

	while(true)
	{
		screen_clear(&screen, ' ');

		screen_draw_sprite(&screen, logo, logo_x_pos, 10);
		screen_draw_sprite(&screen, "Press any key + ENTER to jump!", logo_x_pos, 6);
		screen_draw_sprite(&screen, bird, 0, bird_y_pos);

		screen_print(&screen);

		if (pressed_enter)
		{
			bird_y_vel = bird_jump_force;
			pressed_enter = false;
		}

		bird_y_vel -= 0.000001f;
		bird_y_pos += bird_y_vel;
		bird_y_pos = fmaxf(-11, bird_y_pos);
	}

	return 0;
}