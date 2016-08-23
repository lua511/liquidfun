#pragma once

#ifndef BOX2DWORLD_H
#define BOX2DWORLD_H

extern "C"
{
	_declspec(dllexport) void* Box2DCreateWorld(float gx, float gy);

	_declspec(dllexport) void Box2DReleaseWorld(void* ptr);

	_declspec(dllexport) float	Box2DStepWorld(void* ptr, float timestep, int velocitIt, int positionIt, int particleIt);
}

#endif

