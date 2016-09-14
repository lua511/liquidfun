#pragma once

#include <list>

enum ObjectType
{
	eStatic,
	eKinetic,
	eDynamic,
};

struct GameObject
{
	void* p;
	float w;
	float h;
	float startx;
	float starty;
	ObjectType ot;
};

class World
{
private:
	typedef	std::list<GameObject*>	GameObjectList;
	GameObjectList	objs;
public:
	World();
	~World();
public:
	void AddGameObject(void* p, float w, float h,ObjectType ot);
	void AddStaticObject(void* p, float x, float y, float w, float h);
public:
	int	GetGameObjectCount() const;
	GameObject&	GetGameObjectAt(int n);
};