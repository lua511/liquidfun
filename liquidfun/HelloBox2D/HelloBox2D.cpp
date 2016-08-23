// HelloBox2D.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Box2DWrapper/Box2DWorld.h"
#pragma comment(lib,"Box2DWrapper.lib")


int _tmain(int argc, _TCHAR* argv[])
{
	void*	p = Box2DCreateWorld(9, 9);
	Box2DStepWorld(p, 1, 1, 1, 1);
	Box2DReleaseWorld(p);
	return 0;
}

