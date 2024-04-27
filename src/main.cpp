//All the includes
#include "global_func.hpp"
#include<Windows.h>
#include <cstdio>
#include <synchapi.h>


int main() 
{

	// 
	try {
		terminal_mode_change::enableRawMode();
		//char c;

		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

		while(true)
		{
			char c = '\0';
			DWORD timeout_result = WaitForSingleObject(hStdin,1000);

			if(timeout_result==WAIT_TIMEOUT)
			{
				printf("%d",0);
				break;
			}

			else if(timeout_result== WAIT_OBJECT_0)
			{

				DWORD bytesRead;

				if(!ReadFile(hStdin,&c,1,&bytesRead,nullptr))
				{
					terminal_mode_change::die("Error Reading input");
				}
				
				if (iscntrl(c)) 
				{
					printf("%d\r\n", c);
				}
				else 
				{
					printf("%d ('%c')\r\n", c, c);
				}

				ResetEvent(hStdin);
			}

			if(c==17)
			{
				break;
			}
		}
	}

	catch(const std::system_error& e)
	{
		std::cerr <<"Error: "<< e.what() <<std::endl;
	}


	return 0;
}
