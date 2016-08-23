#include "Box2DWorld.h"
#include "Box2D/Box2D.h"

#pragma comment(lib,"liquidfun.lib")


void* Box2DCreateWorld(float gx, float gy)
{
	b2Vec2 bv(gx, gy);
	b2World* p = new b2World(bv);
	return (void*)p;
}

void Box2DReleaseWorld(void* ptr)
{
	b2World* p = (b2World*)ptr;
	delete p;
}

float Box2DStepWorld(void* ptr, float timestep, int velocitIt, int positionIt, int particleIt)
{
	b2World* p = (b2World*)ptr;
	p->Step(timestep, velocitIt, positionIt,particleIt);
	return timestep;
}
