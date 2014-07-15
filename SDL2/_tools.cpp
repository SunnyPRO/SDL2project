#include "_tools.h"
int counter=0;


_tools::_tools()
{
}


_tools::~_tools()
{
	delete this;
}

/////////////////////////////

_tools::t_ostream::t_ostream()
{
	color = 7;
}

_tools::t_ostream::t_ostream(int color)
{
	this->color = color;
}

_tools::t_ostream::~t_ostream()
{
	cout << endl;
}

