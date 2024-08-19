#pragma once

#include "curses.h"
#include <Windows.h>

class Editor {

	//Variable
	public:
		
	

	private:
		int max_y_terminal, max_x_terminal; //For having the the size of the Terminal

		//Gui Parts
		WINDOW* Top_bar; //Top Bar
		WINDOW* Mid_area; //Mid Area
		WINDOW* Bot_bar; //Bottom Bar


	//Methods
	public:
		Editor();
		~Editor();

		void run(); //For all the things necessary to run;

	private:
		//Setters
		void set_Std_in();
		void set_Std_out();
		void set_console_info();

		//Gui
		void draw_top_bar();
		void draw_mid_area();
		void draw_bot_bar();

		//Processes
		void process_input();
		void show_key(char c);
		char read_key();

};
