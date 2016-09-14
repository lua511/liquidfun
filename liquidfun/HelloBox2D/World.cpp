#include "stdafx.h"
#include "World.h"


World::World()
{

}

World::~World()
{
	for (GameObjectList::iterator it = objs.begin(); it != objs.end(); ++it)
	{
		delete *it;
	}
}

void World::AddGameObject(void* p, float w, float h, ObjectType ot)
{
	GameObject* g = new GameObject();
	g->p = p;
	g->w = w;
	g->h = h;
	g->ot = ot;
	objs.push_back(g);
}

void World::AddStaticObject(void* p, float x, float y, float w, float h)
{
	GameObject*	g = new GameObject();
	g->p = p;
	g->w = w;
	g->h = h;
	g->startx = x;
	g->starty = y;
	g->ot = eStatic;
	objs.push_back(g);
}

int World::GetGameObjectCount() const
{
	return objs.size();
}

GameObject& World::GetGameObjectAt(int n)
{
	GameObjectList::iterator iter = objs.begin();
	std::advance(iter, n);
	return *(*iter);
}
