#include "Main.h"

Uint16 SCREEN_WIDTH = 600;
Uint16 SCREEN_HEIGHT = 400;

int main(int argc, char * argv[])
{
	CMain* cmain = new CMain(SCREEN_WIDTH,SCREEN_HEIGHT);
	cmain->GameLoop();

	delete cmain;

	return 0;
}
