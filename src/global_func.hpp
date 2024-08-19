#pragma once
#include <string>
#include <Windows.h>

namespace terminal_mode_change {
	void enableRawMode();
	void die(const std::string& message);
}
