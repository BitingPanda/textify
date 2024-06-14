#include "editor.hpp"
#include "global_func.hpp"


Editor::Editor() {
	//Setting everything up for other operations
	set_Std_in();
	set_Std_out();
	set_console_info();

	refresh_screen();
	draw_rows();
}


void Editor::set_Std_in() {
	//Geting the handle for the input handle
	std_input = GetStdHandle(STD_INPUT_HANDLE);
	if(std_input == INVALID_HANDLE_VALUE) return;
}
void Editor::set_Std_out() {
	//Geting the handle for the output handle
	std_output = GetStdHandle(STD_OUTPUT_HANDLE);
	//Checks for error in retrieving the handle
	if(std_output == INVALID_HANDLE_VALUE) return;
}
void Editor::set_console_info() {
	//Checks error in retrival of console_info
	if(!GetConsoleScreenBufferInfo(std_output, &console_info)) return;
}


void Editor::show_key(char c) {
	if (iscntrl(c)) {
		printf("%d\r\n", c);
	}
	else {
		printf("%d ('%c')\r\n", c, c);
	}
}



char Editor::read_key() {

	terminal_mode_change::enableRawMode();

	DWORD bytesRead;

	char c;

	if(!ReadFile(std_input,&c,1,&bytesRead,nullptr))
	{
		terminal_mode_change::die("Error Reading input");
	}

	return c;

}


void Editor::process_input() {

	char c = read_key();
	show_key(c);

	switch (c) {
	
		case 17:
			refresh_screen();
			exit(0);
			break;
	}

}





void Editor::refresh_screen() {


	//DWORD is a type used in unsigned integer of 32 bit
	DWORD count;
	//The cell count is calculated by multiplying number of columns and number of rows
	DWORD cellCount = console_info.dwSize.X * console_info.dwSize.Y;
	// COORD is another struct that defines the coordinates of the buffer
	COORD homeCoordinates = {0,0};


	//Filling the whole buffer with spaces//
	//hstd out is the handle to console screen
	//(TCHAR) ' ' is the thing which will fill the screen with
	//cellcount is how many cells that have to be filled
	//homeCoordinates is the starting Coordinates
	//count receives the number of characters actually written
	if(!FillConsoleOutputCharacter(std_output, (TCHAR) ' ', cellCount, homeCoordinates, &count)) return;

	//Move the cursor to the top left corner//
	//homeCoordinates is the coordinate where the cursor should be
	SetConsoleCursorPosition(std_output,homeCoordinates);
}


void Editor::draw_rows() {
	COORD coordinates = {0,0};
	DWORD count;


	for(int i = 0; i<console_info.dwSize.Y;i++) {
		//coordinates.X = 0;
		coordinates.Y = i;

		if(!FillConsoleOutputCharacter(std_output,(TCHAR) '~',1,coordinates, &count)) return;
	}

}

void Editor::tbuffer_state() {
	HANDLE std_output = GetStdHandle(STD_OUTPUT_HANDLE);
	if(std_output == INVALID_HANDLE_VALUE) return;

	CONSOLE_SCREEN_BUFFER_INFO console_info;
	if(!GetConsoleScreenBufferInfo(std_output,&console_info)) return;
}
