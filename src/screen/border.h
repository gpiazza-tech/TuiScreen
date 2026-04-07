#pragma once

struct border
{
	char edge_top;
	char edge_bottom;
	char edge_left;
	char edge_right;

	char corner_top_left;
	char corner_top_right;
	char corner_bottom_left;
	char corner_bottom_right;
};

void border_init(struct border* border, const char* characters);