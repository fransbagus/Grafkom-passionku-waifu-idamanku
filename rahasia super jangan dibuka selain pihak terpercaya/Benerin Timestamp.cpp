#include <windows.h>
#include <stdlib.h>
#include <glut.h>
#include <Box2D/Box2D.h>
#include <iostream>
#include <kotak.h>
#include <lingkaran.h>
#include <segitiga.h>
#include <imageloader.h>

using namespace std;
const float WIDTH = 800.0;
const float HEIGHT = 600.0;

const float m2p = 20; //meter to pixel
const float p2m = 1 / m2p; //pixel to meter
const float PI = 3.14;

GLuint id;
bool mouseDown;
char keypress = 'a';
float32 timeStep = 1 / 60.0;
int32 velocityIteration = 8;
int32 positionIteration = 3;

//define physics world
b2Vec2 gravity(0.0f, 0.0f);
b2Vec2 gravity2(0.0f, 9.81f);
b2World* world = new b2World(gravity); //pointer, dynamically allocated

lingkaran lingkar(world);
segitiga segitigaa(world);
kotak kotakk(world);

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}

void initRendering() {
	Image* image = loadBMP("spongebob.bmp");
	id = loadTexture(image);
	delete image;
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	//menyesuaikan sistem koordinat opengl
	glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
	//gluOrtho2D(0, WIDTH, HEIGHT, 0);
	glViewport(0, WIDTH, 0, HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	kotakk.addRectangle(400, 600, 800, 20, false);
	kotakk.addRectangle(400, 0, 800, 20, false);
	kotakk.addRectangle(0, 300, 20, 600, false);
	kotakk.addRectangle(800, 300, 20, 600, false);
	glutPostRedisplay();
}


void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
	case 'A':
		glColor3f(1, 1, 1);
		kotakk.addRectangle(x, y, 20, 20, true);
		
		glutSwapBuffers();
		glutPostRedisplay();
		break;
	case's':
	case'S':
		glColor3f(1, 1, 1);
		lingkar.addCircle(x, y, 2000, true);

	
		glutSwapBuffers();
		glutPostRedisplay();
		break;
	case'd':
	case 'D':
		glColor3f(1, 1, 1);
		segitigaa.add3angle(x, y, 20, 20, true);

		

		glutSwapBuffers();
		glutPostRedisplay();
		break;
	case'z':
	case'Z':
		world->SetGravity(gravity2);
		b2Body* tmp = world->GetBodyList();
		while (tmp) {
			tmp->ApplyForceToCenter(b2Vec2(0, 1), true);
			tmp = tmp->GetNext();
		}
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseDown = true;
	}
	else {
		mouseDown = false;
	}

	printf("%d %d %d \n", state, x, y);
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
			lingkar.drawCircle(tmp->GetWorldCenter(), c->m_radius, tmp->GetAngle());
		}
		else {
			for (int i = 0; i < ((b2PolygonShape*)tmp->GetFixtureList()->GetShape())->GetVertexCount(); i++)
			{
				points[i] = ((b2PolygonShape*)tmp->GetFixtureList()->GetShape())->GetVertex(i);
			}
			if (((b2PolygonShape*)tmp->GetFixtureList()->GetShape())->GetVertexCount() == 4) {
				kotakk.drawSquare(points, tmp->GetWorldCenter(), tmp->GetAngle(), id);
			}
			else {
				segitigaa.draw3angle(points, tmp->GetWorldCenter(), tmp->GetAngle());
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
	glutCreateWindow("Tugas Rancang Anti Pedofil pedofil club");
	initRendering();
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(handleKeypress);
	world->Step(timeStep, velocityIteration, positionIteration);
	glutSwapBuffers();
	/*
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);*/

	glutMainLoop();
	return 0;
}
