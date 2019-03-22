#include <Windows.h>
#include <iostream>

int main()
{
	using namespace std;

	// Settings of console window
	SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 85, 500, 900, 0);
	SetConsoleTitle("The Legend of Zelda: Ocarina of Time");

	getchar();

	return 0;
}