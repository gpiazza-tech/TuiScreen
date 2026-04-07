#include <pch.h>
#include "border.h"

void border_init(struct border* border, const char* characters)
{
	/*
	Example input:

	"|-|"
	"| |"
	"|-|"

	*/

	border->corner_top_left		= characters[0];
	border->edge_top			= characters[1];
	border->corner_top_right	= characters[2];
	border->edge_left			= characters[3];
	border->edge_right			= characters[5];
	border->corner_bottom_left	= characters[6];
	border->edge_bottom			= characters[7];
	border->corner_bottom_right	= characters[8];
}