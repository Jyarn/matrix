#include "ui.h"

#include <string.h>
#include <assert.h>
#include <curses.h>
#include <unistd.h>

WINDOW *uiwindow = NULL;

int colour_map[MAX_INTENSITY+1] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 3, 6};

void set_colours();

bool init_ui () {
	// init curses
	uiwindow = initscr();
	if (!uiwindow) return false;

	start_color();
	if (!has_colors() || !can_change_color() || COLOR_PAIRS < 6) {
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
			color_set(colour_map[intensity], NULL);
			mvaddch(y, x, matrix[x][y].char_value);
		}
	}

	refresh();
}

void set_colours () {
	for (int i = 0; i < 8; i++) {
		init_pair(i+1, i, COLOR_BLACK);
	}

	// set shades of green
	for (int i = 0; i <= 5; i++) {
		init_color(i, 0, i*200, 0);
	}

	init_color(6, 800, 1000, 800);
}
