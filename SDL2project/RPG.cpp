#include "cMain.h"


int main(int argc, char * argv[])
{
	cMain* cmain = new cMain(SCREEN_WIDTH, SCREEN_HEIGHT);
	cmain->GameLoop();

	delete cmain;

	return 0;
}