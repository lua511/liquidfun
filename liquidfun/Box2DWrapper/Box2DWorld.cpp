#include "Box2DWorld.h"
#include "Box2D/Box2D.h"

#pragma comment(lib,"liquidfun.lib")

static b2World*	g_lastWorld = NULL;
static b2ParticleSystem* g_lastParticleSystem = NULL;

void* Box2DCreateWorld(float gx, float gy)
{
	if (g_lastParticleSystem != NULL && g_lastWorld != NULL)
	{
		g_lastWorld->DestroyParticleSystem(g_lastParticleSystem);
		g_lastParticleSystem = NULL;
	}
	if (g_lastWorld != NULL)
	{
		delete g_lastWorld;
		g_lastWorld = NULL;
	}
	b2Vec2 bv(gx, gy);
	b2World* p = new b2World(bv);
	g_lastWorld = p;
	return (void*)p;
}

void Box2DReleaseWorld(void* ptr)
{
	b2World* p = (b2World*)ptr;
	g_lastWorld = NULL;
	delete p;
}

float Box2DStepWorld(void* ptr, float timestep, int velocitIt, int positionIt, int particleIt)
{
	b2World* p = (b2World*)ptr;
	p->Step(timestep, velocitIt, positionIt,particleIt);
	return timestep;
}

void* Box2DCreateBody(void* world, int tp, float xc, float yc)
{
	b2World* p = (b2World*)world;

	b2BodyDef	def;
	if (tp != b2_staticBody && tp != b2_kinematicBody && tp != b2_dynamicBody)
	{
		tp = b2_staticBody;
	}
	def.type = (b2BodyType)tp;
	def.position.Set(xc, yc);
	
	b2Body* body = p->CreateBody(&def);
	return (void*)body;
}

void Box2DCreateFixture(void* ptr, float x, float y, float density,float restitution)
{
	b2Body* p = (b2Body*)ptr;
	
	b2PolygonShape box;
	box.SetAsBox(x/2, y/2);

	b2FixtureDef def;
	def.shape = &box;
	def.density = density;
	def.restitution = restitution;
	
	p->CreateFixture(&def);
}

void* Box2DCreateParticleSystem(void* ptr, float radius, float damping, float graviityScale, int number)
{
	b2ParticleSystemDef def;
	def.radius = radius;
	def.dampingStrength = damping;
	def.gravityScale = graviityScale;
	def.maxCount = number;	
	b2World* p = (b2World*)ptr;
	if (g_lastParticleSystem != NULL)
	{
		p->DestroyParticleSystem(g_lastParticleSystem);
	}
	b2ParticleSystem* pPart = p->CreateParticleSystem(&def);
	g_lastParticleSystem = pPart;
	return (void*)pPart;
}

void Box2DDestroyParticleSystem(void* pworld, void* particlesys)
{
	b2World* pw = (b2World*)pworld;
	b2ParticleSystem* pp = (b2ParticleSystem*)particlesys;
	pw->DestroyParticleSystem(pp);
}

int Box2DCreateParticle(void* ptr, float x, float y)
{
	b2ParticleDef	pd;
	pd.flags = b2_waterParticle;
	pd.color.Set(0, 0, 255, 255);
	pd.position.Set(x, y);
	b2ParticleSystem* p = (b2ParticleSystem*)ptr;
	return p->CreateParticle(pd);
}

int Box2DCreateParticleInRect(void* ptr, float x, float y, float w, float h, int count)
{
	for (int i = 0; i < count; ++i)
	{
		b2ParticleDef	pd;
		pd.flags = b2_waterParticle;
		pd.color.Set(0, 0, 255, 255);
		pd.position.Set(x, y);
		pd.velocity.y = -5;
		b2ParticleSystem* p = (b2ParticleSystem*)ptr;
		p->CreateParticle(pd);
	}
	return 0;
}

void Box2DDestroyParticle(void* ptr, int pid)
{
	b2ParticleSystem* p = (b2ParticleSystem*)ptr;
	return p->DestroyParticle(pid);
}

void Box2DDestroyParticlesInShape(void* ptr, float x, float y, float w, float h)
{
	b2ParticleSystem* p = (b2ParticleSystem*)ptr;
	b2Transform tr;
	b2PolygonShape sp;
	b2Vec2 center;
	center.x = x;
	center.y = y;
	tr.Set(center, 0);
	sp.SetAsBox(w/2, h/2);
	p->DestroyParticlesInShape(sp,tr);
}

void Box2DCreateParticleGroup(void* particleSys, float x, float y, float w, float h)
{
	b2ParticleGroupDef	pd;
	pd.flags = b2_waterParticle;
	b2PolygonShape shape2;
	shape2.SetAsBox(w/2, h/2, b2Vec2(x, y), 0.0);
	pd.shape = &shape2;
	pd.group = NULL;
	b2ParticleSystem* p = (b2ParticleSystem*)particleSys;
	b2ParticleGroup* pg = p->CreateParticleGroup(pd);
}

void Box2DSetMaxParticle(void* ptr, int count)
{
	b2ParticleSystem* p = (b2ParticleSystem*)ptr;
	p->SetMaxParticleCount(count);
}

void Box2DSetBodyTrans(void* ptr, float x, float y, float fv)
{
	b2Body* p = (b2Body*)ptr;
	const b2Transform& tr = p->GetTransform();
	p->SetTransform(tr.p, fv);
}

void Box2DGetBodyTrans(void* ptr, float& x, float& y, float& a)
{
	b2Body* p = (b2Body*)ptr;
	const b2Vec2& pv = p->GetPosition();
	x = pv.x;
	y = pv.y;
	a = p->GetAngle();
}

void Box2DGetPositionBuffer(void* particleSys, float* pBuffer, int len)
{
	b2ParticleSystem* p = (b2ParticleSystem*)particleSys;
	int cnt = p->GetParticleCount();
	b2Vec2* buffer = p->GetPositionBuffer();
	for (int i = 0; i < cnt; ++i)
	{
		if (i*2 < len)
		{
			pBuffer[i * 2] = buffer[i].x;
			pBuffer[i * 2 + 1] = buffer[i].y;
		}
	}
	for (int i = cnt * 2; i < len; ++i)
	{
		pBuffer[i] = 0;
	}
}

int Box2DGetParticleCount(void* particleSys)
{
	b2ParticleSystem* p = (b2ParticleSystem*)particleSys;
	return p->GetParticleCount();
}
