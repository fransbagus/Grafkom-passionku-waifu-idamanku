// _TugasRancang.cpp : Defines the entry point for the console application.
//

#include "windows.h"
#include "stdlib.h"
#include "glut.h"
#include "Box2D\Box2D.h"
#include <iostream>
#include "vector";

using namespace std;
const float WIDTH = 800.0;
const float HEIGHT = 600.0;

const float m2p = 20; //meter to pixel
const float p2m = 1 / m2p; //pixel to meter
const float PI = 3.14;
bool mouseDown;
char keypress = 'a';

float32 timeStep = 1 / 240.0;
int32 velocityIteration = 8;
int32 positionIteration = 3;

//define physics world
b2Vec2 gravity(0.0f, 9.81f);
b2Vec2 gravity2(0.0f, 0.0f);
bool cek = false;
b2World* world; //pointer, dynamically allocated
b2Body* myrect;
b2Body* myrect2;



b2Body* addRectangle(int x, int y, int w, int h, bool dyn = true) { //add bodydef
	//create dynamic body
	b2BodyDef bodyDef;
	if (dyn == true) {
		bodyDef.type = b2_dynamicBody;
	}
	bodyDef.position.Set(x * p2m, y * p2m);
	b2Body* body = world->CreateBody(&bodyDef);

	//attach polygon using fixture def
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(w * p2m / 2, h * p2m / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.5f;
	fixtureDef.friction = 0.1f;
	fixtureDef.restitution = 0.15f;
	body->CreateFixture(&fixtureDef);

	return body;
}

b2Body* addCircle(int x, int y, int r, bool dyn = true) {
	//create dynamic body
	b2BodyDef bodyDef;
	if (dyn == true) {
		bodyDef.type = b2_dynamicBody;
	}
	bodyDef.position.Set(x * p2m, y * p2m);
	b2Body* body = world->CreateBody(&bodyDef);

	//attach circle using fixture def
	b2CircleShape dynCircle;
	dynCircle.m_radius = 10 * p2m;
	dynCircle.m_p.Set(0, 0);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynCircle;
	fixtureDef.density = 0.5f;
	fixtureDef.friction = 0.1f;
	fixtureDef.restitution = 0.15f;
	body->CreateFixture(&fixtureDef);

	return body;
}


b2Body* add3angle(int x, int y, int w, int h, bool dyn = true) { //add bodydef
	//create dynamic body
	b2BodyDef bodyDef;
	if (dyn == true) {
		bodyDef.type = b2_dynamicBody;
	}
	bodyDef.position.Set(x * p2m, y * p2m);
	b2Body* body = world->CreateBody(&bodyDef);

	//attach polygon using fixture def
	b2Vec2 vertices[3];
	vertices[0].Set(0.0f, 0.0f);
	vertices[1].Set(1.0f, 0.0f);
	vertices[2].Set(0.0f, 1.0f);
	int32 count = 3;

	b2PolygonShape segitiga;
	segitiga.Set(vertices, count);


	b2FixtureDef fixtureDef;
	fixtureDef.shape = &segitiga;
	fixtureDef.density = 0.5f;
	fixtureDef.friction = 0.1f;
	fixtureDef.restitution = 0.15f;
	body->CreateFixture(&fixtureDef);

	return body;
}

void drawSquare(b2Vec2 * points, b2Vec2 center, float angle) {
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(center.x * m2p, center.y * m2p, 0);
	glRotatef(angle * 180.0 / PI, 0, 0, 1);
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++) {
		glVertex2f(points[i].x * m2p, points[i].y * m2p);
	}
	glEnd();
	glPopMatrix();
	glFlush();
}

void drawCircle(b2Vec2 center, float r, float angle) {
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(center.x * m2p, center.y * m2p, 0);
	glRotatef(angle * 180.0 / PI, 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0); //center point
	for (float i = 0; i < 360; i++) {
		glVertex2f((cos(i) * r) * m2p, (sin(i) * r) * m2p);
	}
	glEnd();
	glPopMatrix();
	glFlush();
}

void draw3angle(b2Vec2 * points, b2Vec2 center, float angle) {
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(center.x * m2p, center.y * m2p, 0);
	glRotatef(angle * 180.0 / PI, 0, 0, 1);
	glBegin(GL_POLYGON);

	glVertex2f(points[0].x * m2p - 6.75, points[0].y * m2p - 6.75);
	glVertex2f(points[1].x * m2p - 6.75, points[1].y * m2p - 6.75);
	glVertex2f(points[2].x * m2p - 6.75, points[2].y * m2p - 6.75);


	glEnd();
	glPopMatrix();
	glFlush();
}



void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
	case 'A':
		glColor3f(1, 1, 1);
		addRectangle(x, y, 20, 20, true);

		world->Step(timeStep, velocityIteration, positionIteration);

		glutSwapBuffers();
		glutPostRedisplay();
		break;
	case's':
	case'S':
		glColor3f(1, 1, 1);
		addCircle(x, y, 2000, true);

		world->Step(timeStep, velocityIteration, positionIteration);

		glutSwapBuffers();
		glutPostRedisplay();
		break;
	case'd':
	case 'D':
		glColor3f(1, 1, 1);
		add3angle(x, y, 20, 20, true);


		world->Step(timeStep, velocityIteration, positionIteration);
		glutSwapBuffers();
		glutPostRedisplay();
		break;
	case'z':
	case'Z':
		world->SetGravity(gravity);
		break;
	}
}
void bind() {
	b2MouseJointDef jointDef;
	b2BodyDef bodyDef;
	jointDef.bodyA = myrect;
	jointDef.bodyB = myrect2;
	jointDef.collideConnected = true;
	jointDef.maxForce = 500;
	jointDef.frequencyHz = 5;
    jointDef.dampingRatio = 0.9;
	b2MouseJoint* joint = (b2MouseJoint*)world->CreateJoint(&jointDef);

	

}

void update(float x, float y) {
	
	
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseDown = true;
		b2Vec2 mouse2(x, y);
		mouse2 -= (myrect2->GetWorldCenter());
		myrect2->ApplyForce(mouse2, myrect2->GetWorldCenter());
		//bind();
		glutSwapBuffers();
		glutPostRedisplay();
	}
	else {
		mouseDown = false;
	}


	printf("%d %d %d \n", state, x, y);
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
	glViewport(0, WIDTH, 0, HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	world = new b2World(gravity2);
	myrect = addRectangle(0, 600, 1600, 20, false);
	myrect2 = addRectangle(100, 200, 50, 50);
	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//untuk gambar semua bentuk
	b2Body* tmp = world->GetBodyList();
	b2Vec2 points[4];
	while (tmp) {
		if (tmp->GetFixtureList()->GetShape()->GetType() == 0) {
			b2CircleShape* c = ((b2CircleShape*)tmp->GetFixtureList()->GetShape());
			drawCircle(tmp->GetWorldCenter(), c->m_radius, tmp->GetAngle());
		}
		else {
			for (int i = 0; i < ((b2PolygonShape*)tmp->GetFixtureList()->GetShape())->GetVertexCount(); i++)
			{
				points[i] = ((b2PolygonShape*)tmp->GetFixtureList()->GetShape())->GetVertex(i);
			}
			if (((b2PolygonShape*)tmp->GetFixtureList()->GetShape())->GetVertexCount() == 4) {
				drawSquare(points, tmp->GetWorldCenter(), tmp->GetAngle());
			}
			else {
				draw3angle(points, tmp->GetWorldCenter(), tmp->GetAngle());
			}
		}
		tmp = tmp->GetNext();
	}


	world->Step(timeStep, velocityIteration, positionIteration);

	glutSwapBuffers();
	glutPostRedisplay();
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Tugas Rancang");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(handleKeypress);
	world->Step(timeStep, velocityIteration, positionIteration);
	glutSwapBuffers();
	glutMainLoop();
	return 0;
}
