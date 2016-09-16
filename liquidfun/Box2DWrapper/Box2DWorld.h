#pragma once

#ifndef BOX2DWORLD_H
#define BOX2DWORLD_H

extern "C"
{
	_declspec(dllexport) void* Box2DCreateWorld(float gx, float gy);

	_declspec(dllexport) void Box2DReleaseWorld(void* ptr);

	_declspec(dllexport) float	Box2DStepWorld(void* ptr, float timestep, int velocitIt, int positionIt, int particleIt);

	_declspec(dllexport) void*	Box2DCreateBody(void* world,int tp, float xc, float yc,float radians);

	_declspec(dllexport) void Box2DCreateFixture(void* ptr, float x, float y, float density, float restitution);

	_declspec(dllexport) void* Box2DCreateParticleSystem(void* ptr, float radius, float damping, float graviityScale, int number);

	_declspec(dllexport) void Box2DDestroyParticleSystem(void* pworld,void* particlesys);

	_declspec(dllexport) int Box2DCreateParticle(void* ptr, float x, float y,float r);

	_declspec(dllexport) int Box2DCreateParticleInRect(void* ptr, float x, float y, float w, float h, int count);

	_declspec(dllexport) void Box2DDestroyParticle(void* ptr, int pid);

	_declspec(dllexport) void Box2DDestroyParticlesInShape(void* ptr, float x, float y, float w, float h);

	_declspec(dllexport) void Box2DCreateParticleGroup(void* particleSys, float x,float y,float w, float h);

	_declspec(dllexport) void Box2DSetMaxParticle(void* ptr, int count);

	_declspec(dllexport) void Box2DGetPositionBuffer(void* particleSys,float* pBuffer,int len);

	_declspec(dllexport) int Box2DGetParticleCount(void* particleSys);

	_declspec(dllexport) void Box2DSetBodyTrans(void* ptr, float x,float y,float fv);

	_declspec(dllexport) void Box2DGetBodyTrans(void* ptr, float& x, float& y,float& a);
}

#endif

