# TuiScreen

TuiScreen is a tiny and efficient C framework for turning the console window into a 2D canvas thats simple to use. 
Great for making small UI console applications or games without all the boilerplate.

![TuiScreen Screenshot](https://github.com/gpiazza-tech/TuiScreen/blob/master/TuiScreen.png)

## How to build

Windows
 * Install git and Visual Studio 2026
 * Clone the repository: `git clone https://github.com/gpiazza-tech/TuiScreen`
 * Run scripts/Setup-Windows.bat to build as a static library or scripts/Setup-Examples-Windows.bat to build an example application.
 * Open the generated .sln file in Visual Studio and build
	
Linux
 * Install git, gcc, and make: `sudo apt install build-essential git`
 * Clone the repository: `git clone https://github.com/gpiazza-tech/TuiScreen`
 * Run `scripts/Setup-Linux.sh` to build as a static library or `scripts/Setup-Examples-Linux.sh` to build the included example application.
	(You may need to enable execution permissions first with `sudo chmod +x scripts/Setup-Linux.sh`)
 * Run `make` to build the project

## How to use

Once you have TuiScreen built, you'll need to include it in your project. 
Add TuiScreen/include to your project's include paths.

You should now be able to include it in your C/C++ source file:

'''c
#include <TuiScreen/include.h>
'''

Drawing a basic screen is very simple. First, you'll need to create a screen instance and initialize it:

'''c
struct screen screen;
screen_init(&screen, 118, 26);
'''

To draw the screen to the console window, you can call

'''c
screen_print(&screen);
getchar(); // so the program doesn't terminate immediately
'''

Now you won't see anything printed because we haven't added anything to the screen,
so let's add a basic border:

'''c
// ... init screen ...

screen_set_border(&screen,
		"+++"
		"| |"
		"+++"
	);

screen_print(&screen);
getchar();
'''

And this is what we get:

![TuiScreen Screenshot](https://github.com/gpiazza-tech/TuiScreen/blob/master/docs/screen_1.png)

TuiScreen gives you the ability to set any character within this border:

'''c
// ... init screen ...

screen_set_pixel(&screen, ':', 0, 0);
screen_set_pixel(&screen, ')', 1, 0);
screen_print(&screen);
getchar();
'''

![TuiScreen Screenshot](https://github.com/gpiazza-tech/TuiScreen/blob/master/docs/screen_2.png)

By default, the x and y position that you specify will be relative to the top-left corner of the screen.
If you would like to set the origin of the screen to be at the center for example, you can so with:

'''c
// ... init screen ...

screen.screen_origin = TUI_SCREEN_ORIGIN_CENTER;

// ... print screen ...
'''

![TuiScreen Screenshot](https://github.com/gpiazza-tech/TuiScreen/blob/master/docs/screen_3.png)

But maybe you would like to draw a group of chars at once, rather than individually.
You can do that using the screen_draw_sprite utility:

'''c
// ... init screen ...

screen_draw_sprite(&screen, "Hello World!", 0, 0);

screen_print(&screen);
getchar();
'''

![TuiScreen Screenshot](https://github.com/gpiazza-tech/TuiScreen/blob/master/docs/screen_4.png)

Why is it called draw sprite and not draw string you ask? Because this function can
be used to draw more complex multi-line designs like this:

'''c
// ... init screen ...

screen_draw_sprite(&screen, 
	"|   | ==== |    |    |===| | \n"
	"|===| |=== |    |    |   | | \n"
	"|   | ==== |=== |=== |===| . \n",
	0, 0);

screen_print(&screen);
getchar();
'''

![TuiScreen Screenshot](https://github.com/gpiazza-tech/TuiScreen/blob/master/docs/screen_5.png)

Just like for the screen origin, the default sprite origin point is at the top-left,
To change it to the center use

'''c
// ... init screen ...

screen.sprite_origin = TUI_SPRITE_ORIGIN_CENTER;

// ... print screen ...
'''

![TuiScreen Screenshot](https://github.com/gpiazza-tech/TuiScreen/blob/master/docs/screen_6.png)

And that's pretty much it! For a more detailed example in practice, as well as
examples of more features, you can look at the demo application included 
in the repository at examples/main.c