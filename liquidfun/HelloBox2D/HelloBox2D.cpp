// HelloBox2D.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <gl/glut.h>

#include "Box2DWrapper/Box2DWorld.h"
#pragma comment(lib,"Box2DWrapper.lib")
#pragma comment(lib,"glut32.lib")

#include "World.h"

World g_world;
void* g_box2dWorld;
void* g_particle;
float	halfx = 11;
float	halfy = 11;
float	wrate = (11 * 2) / 10.0f;


void diplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	//glBegin(GL_LINES);
	//glVertex2i(180, 15);
	//glVertex2i(10, 145);
	//glEnd();
	//glRectf(-200.0f, -200.0f, 0.0f, 0.0f);

	Box2DStepWorld(g_box2dWorld, 1.0f / 20.0f, 6, 2, 1);

	int n = g_world.GetGameObjectCount();
	for (int i = 0; i < n; ++i)
	{
		GameObject& go = g_world.GetGameObjectAt(i);
		if (go.ot == eDynamic)
		{

			float x;
			float y;
			float a;
			Box2DGetBodyTrans(go.p, x, y, a);
			
			glRectf(x - 0.1, y - 0.1, x + 0.1, y + 0.1);
		}
		else if (go.ot == eStatic)
		{
			float x1 = go.startx - go.w / 2;
			float y1 = go.starty - go.h / 2;
			float x2 = go.startx + go.w / 2;
			float y2 = go.starty + go.h / 2;
			glRectf(x1 * wrate, y1 * wrate, x2 * wrate, y2 * wrate);
		}
	}
	//glColor3f(0.0, 1.0, 0.0);

	int nc = Box2DGetParticleCount(g_particle);
	float* v = new float[nc * 2];
	Box2DGetPositionBuffer(g_particle, v, n * 2);
	for (int i = 0; i < nc; ++i)
	{
		float v1 = v[2 * i];
		float v2 = v[2 * i + 1];
		
		glRectf(v1, v2, v1 + 0.5f, v2 + 0.5f);
	}
	delete[] v;
	glFlush();
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-halfx, halfx, -halfy, halfy);

	g_box2dWorld = Box2DCreateWorld(0, -9.0f);

	void*	pbodyLeft = Box2DCreateBody(g_box2dWorld, 0, -10, 0);
	Box2DCreateFixture(pbodyLeft, 1, 10, 0, 0.0f);
	g_world.AddStaticObject(pbodyLeft, -5,0,1, 10);

	void*	pbodyRight = Box2DCreateBody(g_box2dWorld, 0, 10, 0);
	Box2DCreateFixture(pbodyRight, 1, 10, 0, 0.0f);
	g_world.AddStaticObject(pbodyRight, 5,0,1, 10);

	void*	pbodyBottom = Box2DCreateBody(g_box2dWorld, 0, 0, -10);
	Box2DCreateFixture(pbodyBottom, 10, 1, 0, 0.0f);
	g_world.AddStaticObject(pbodyBottom, 0,-5,10, 1);

	void*	pbodyUp = Box2DCreateBody(g_box2dWorld, 0, 0, 10);
	Box2DCreateFixture(pbodyUp, 10, 1, 0, 0.0f);
	g_world.AddStaticObject(pbodyUp, 0,5,10, 1);

	void* pball = Box2DCreateBody(g_box2dWorld, 2, 0, 0);
	Box2DCreateFixture(pball, 1, 1, 0, 0.99f);
	g_world.AddGameObject(pball, 1, 1, eDynamic);

	g_particle = Box2DCreateParticleSystem(g_box2dWorld, 0.5, 0, 1, 100);

	Box2DCreateParticleGroup(g_particle, 10, 10);
}

void cleanup()
{
	Box2DDestroyParticleSystem(g_box2dWorld,g_particle);
	Box2DReleaseWorld(g_box2dWorld);
}

void OnTimer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, OnTimer, 1);
}

int _tmain(int argc, char* argv[])
{
	atexit(cleanup);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 480);
	glutCreateWindow("Particle");
	init();
	glutDisplayFunc(&diplay);
	glutTimerFunc(100, OnTimer, 1);
	glutMainLoop();
	if (0)
	{

	}
	return 0;
}

