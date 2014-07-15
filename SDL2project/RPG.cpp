#include "Main.h"

int main(int argc, char * argv[])
{
	CMain* cmain = new CMain(600,400);
	cmain->GameLoop();

	delete cmain;

	return 0;
}
