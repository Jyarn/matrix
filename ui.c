#include "ui.h"

#include <string.h>
#include <assert.h>
#include <curses.h>
#include <unistd.h>

WINDOW *uiwindow = NULL;

int colour_map[MAX_INTENSITY+1] = {1. 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 3, 6};

bool init_ui () {
	// set the matrix all to black
	// move this late to matrix
	
	for (int x = 0; x < MAXX; x++) {
		for (int y = 0; y < MAXY; y++) {
			matrix[x][y].char_value = 0;
			matrix[x][y].intensity = 0;
		}
	}

	// init curses
	uiwindow = initscr();
	if (!uiwindow) return false;

	start_color();
	if (i!has_colors() || !can_change_color() || COLOR_PAIRS < 6) {
		printf("WARNING: SKILL ISSUE\n");
		return false;
	}

	set_colours();
	return true;
}

void cleanup_ui () {
	delwin(uiwindow);
	endwin();
	refresh();
}

void show_matrix () {
	for (int x = 0; x < MAXX; x++) {
		for (int y = 0; y < MAXY; y++) {
			int intensity = matrix[x][y].intensity;
			color_set(colour_map[intensity, NULL]);
			mvaddch(y, x, matrix[x][y].char_value);
		}
	}

	refresh();
}

void set_colours () {

}
