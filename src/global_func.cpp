#include "global_func.hpp"
#include <cstdlib>
#include <string>

// This namespace is for terminal Mode changing variables
namespace terminal_mode_change {
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE); //This handle gets the state
	DWORD original_mode; //This variable stores the original console mode for restoring
	DWORD raw_mode; //This variable stores the changed raw mode


	// This functions enables the raw mode of the console
	void enableRawMode()
	{
		if(!GetConsoleMode(hInput, &original_mode)){
			die("Failed to get the console mode");
		}
		std::atexit(disableRawMode);
		raw_mode = original_mode;
		raw_mode &= ~(ENABLE_PROCESSED_INPUT | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT |ENABLE_PROCESSED_OUTPUT);
		raw_mode |= 0;
		raw_mode |= ENABLE_WINDOW_INPUT;

		if(!SetConsoleMode(hInput,raw_mode)) {
			die("Failed to restore console mode");
		}

	}

	// This function disables the raw_mode function
	void disableRawMode() {
		if (!SetConsoleMode(hInput, original_mode)) {
			die("Failed to restore console mode");
		}
	}


	void die(const std::string& message) {
		DWORD errorCode = GetLastError();
		LPSTR messageBuffer = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		std::string fullMessage = message;
		if (size == 0) {
			fullMessage += ": Unknown error";
		} else {
			fullMessage += ": " + std::string(messageBuffer);
			LocalFree(messageBuffer);
		}

		throw std::system_error(errorCode, std::system_category(), fullMessage);
	}

} //namespace terminal_mode_change
  //

/*
namespace editor {

	//This is for debugging
	void show_key(char c) {
		
		if (iscntrl(c)) 
		{
			printf("%d\r\n", c);
		}
		else 
		{
			printf("%d ('%c')\r\n", c, c);
		}
	}



	char read_key() {
		
		terminal_mode_change::enableRawMode();

		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD bytesRead;

		char c;

		if(!ReadFile(hStdin,&c,1,&bytesRead,nullptr))
		{
			terminal_mode_change::die("Error Reading input");
		}

		return c;

	}


	void process_key() {

		char c = read_key();
		show_key(c);

		switch (c) {
		
			case 17:
				refresh_screen();
				exit(0);
				break;
		}

	}


	void refresh_screen() {
		//Geting the handle for the console screen buffer
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		//Checks for error in retrieving the handle
		if(hstdout == INVALID_HANDLE_VALUE) return;

		//it is a struct that holds information about console screen buffer like size and cursor position
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		//Checks error in retrival of csbi
		if(!GetConsoleScreenBufferInfo(hstdout, &csbi)) return;

		//DWORD is a type used in unsigned integer of 32 bit
		DWORD count;
		//The cell count is calculated by multiplying number of columns and number of rows
		DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
		// COORD is another struct that defines the coordinates of the buffer
		COORD homeCoordinates = {0,0};


		//Filling the whole buffer with spaces//
		//hstd out is the handle to console screen
		//(TCHAR) ' ' is the thing which will fill the screen with
		//cellcount is how many cells that have to be filled
		//homeCoordinates is the starting Coordinates
		//count receives the number of characters actually written
		if(!FillConsoleOutputCharacter(hstdout, (TCHAR) ' ', cellCount, homeCoordinates, &count)) return;

		//Move the cursor to the top left corner//
		//homeCoordinates is the coordinate where the cursor should be
		SetConsoleCursorPosition(hstdout,homeCoordinates);
	}


	void draw_rows() {

		//Geting the handle for the console screen buffer
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		//Checks for error in retrieving the handle
		if(hstdout == INVALID_HANDLE_VALUE) return;

		//it is a struct that holds information about console screen buffer like size and cursor position
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		//Checks error in retrival of csbi
		if(!GetConsoleScreenBufferInfo(hstdout, &csbi)) return;


		COORD coordinates = {0,0};
		DWORD count;


		for(int i = 0; i<csbi.dwSize.Y;i++) {
			//coordinates.X = 0;
			coordinates.Y = i;

			if(!FillConsoleOutputCharacter(hstdout,(TCHAR) '~',1,coordinates, &count)) return;
		}

	}

	void tbuffer_state() {
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		if(hstdout == INVALID_HANDLE_VALUE) return;

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if(!GetConsoleScreenBufferInfo(hstdout,&csbi)) return;
	}




}
*/
