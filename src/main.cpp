#include<Windows.h>
#include "editor.hpp"

int main() {
	//editor::refresh_screen();
	//editor::draw_rows();
	Editor ex;
	//ex.refresh_screen();
	//ex.draw_rows();
	
	//Application Loop
	while(true) {
		//editor::process_key();
		ex.process_input();
	}
	return 0;
}
