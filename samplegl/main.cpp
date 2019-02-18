#include "EngineCore.h"
#include <conio.h>
int main()
{
	EngineCore engine(800, 600, "Title", new Game);
	_getch();
	return 0;
}	