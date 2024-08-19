#include "global_func.hpp"
#include "curses.h"
#include <system_error>
#include <cstdlib>
#include <string>

// This namespace is for terminal Mode changing variables
namespace terminal_mode_change {


	// This functions enables the raw mode of the console
	void enableRawMode() {
		raw();
		noecho();
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
