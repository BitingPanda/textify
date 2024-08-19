#include "editor.hpp"
#include "curses.h"
#include "global_func.hpp"



Editor::Editor() {
	//Initialising the Libraries
	initscr();

	//Setting Things
	set_console_info();

	//Drawing the GUI
	draw_top_bar();
	draw_bot_bar();
	draw_mid_area();
}


Editor::~Editor() {
	// Clean up
	delwin(Top_bar);
	delwin(Mid_area);
	delwin(Bot_bar);
	endwin();  // End ncurses mode
}


void Editor::set_console_info() {
	getmaxyx(stdscr, max_y_terminal , max_x_terminal);
}


void Editor::draw_top_bar() {
	//Creates the Top Bar
	Top_bar = newwin(1, max_x_terminal, 0, 0);
	refresh();

	//Creates the writing
	int max_y_Top_bar, max_x_Top_bar;
	getmaxyx(Top_bar, max_y_Top_bar , max_x_Top_bar);
	wattron(Top_bar,A_REVERSE);
	mvwhline(Top_bar, 0, 0, ' ', ((max_x_terminal/2)-7));
	mvwprintw(Top_bar, 0, ((max_x_terminal/2)-7), "Textify");
	mvwhline(Top_bar, 0, ((max_x_terminal/2)), ' ', max_x_terminal);
	wattroff(Top_bar,A_REVERSE);
	wrefresh(Top_bar);
}


void Editor::draw_mid_area() {
	Mid_area = newwin(max_y_terminal-2, max_x_terminal, 1, 0 );
	//refresh();

	// Enable keypad and scrolling for Mid_area
	keypad(Mid_area, TRUE);
	scrollok(Mid_area, TRUE);

	// Move the cursor to the top-left corner of Mid_area
	wmove(Mid_area, 0, 0);
	wrefresh(Mid_area);
}



void Editor::draw_bot_bar() {
	Bot_bar = newwin(1, max_x_terminal,max_y_terminal-1, 0);
	refresh();

	// Fill the bottom bar with spaces in reverse video mode
	wattron(Bot_bar, A_REVERSE);
	mvwhline(Bot_bar, 0, 0, ' ', max_x_terminal);
	wattroff(Bot_bar, A_REVERSE);
	wrefresh(Bot_bar);
}


char Editor::read_key() {
	terminal_mode_change::enableRawMode();

	int c;
	char ch;

	c = getch();
	ch = static_cast<char>(c);

	return ch;
}


void Editor::show_key(char c) {
	wprintw(Mid_area,"%c ",c);
	wprintw(Mid_area,"%d \n", c);
	wrefresh(Mid_area);
}


void Editor::process_input() {

	char c = read_key();
	show_key(c);

	switch (c) {
		case 17:
			refresh();
			exit(0);
			break;
	}
}


void Editor::run() {
	process_input();
}
