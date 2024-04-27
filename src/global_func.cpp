#include "global_func.hpp"
#include <cstddef>
#include <cstdlib>
#include <errhandlingapi.h>
#include <minwindef.h>
#include <string>
#include <winbase.h>
#include <winnt.h>


// This namespace is for terminal Mode changing variables
namespace terminal_mode_change 
{
	
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
