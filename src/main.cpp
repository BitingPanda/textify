#include<Windows.h>
#include "editor.hpp"

int main() {
	//Using a Editor Object
	Editor ex;
	
	//Application Loop
	while(true) {
		ex.run();
	}
	return 0;
}
