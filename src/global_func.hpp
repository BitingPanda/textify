#pragma once
#include <string>
#include <Windows.h>

namespace terminal_mode_change {
	extern HANDLE hInput ; //This stores the terminal 
	extern DWORD original_mode; //This stores the original mode of terminal
	extern DWORD raw_mode; //This stores the raw mode of terminal

	void enableRawMode();
	void disableRawMode();
	void die(const std::string& message);
}

/*
namespace editor {
	//This is just for debugging
	void show_key(char c);

	char read_key();
	void process_key();
	void refresh_screen();
	void draw_rows();
}
*/
