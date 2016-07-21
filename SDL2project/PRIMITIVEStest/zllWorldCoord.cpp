#include"zllWorldCoord.h"

World::World()
{
	windowXmin = 0;
	windowYmin = 0;
	windowXmax = 800;
	windowYmax = 800;
	vp = 0x0;
}

void World::SetWindowRect(float xmin,float xmax, float ymin,float ymax)
{
	windowXmin = xmin;
	windowXmax = xmax;
	windowYmin = ymin;
	windowYmax = ymax;
}

SDL_Point World::WorldToViewport(float x,float y)
{
	SDL_Point vpPoint;
	float Sx,Sy;
	Sx = (this->vp->xMax - this->vp->xMin)/(this->windowXmax - this->windowXmin);
	Sy = (this->vp->yMax - this->vp->yMin)/(this->windowYmax - this->windowYmin);
	vpPoint.x = this->vp->xMin + (x - this->windowXmin) * Sx;
	vpPoint.y = this->vp->yMin + (y - this->windowYmin) * Sy;
	return vpPoint;
}