#include <windows.h>
#include <gl/GL.h>
#include <glut.h>
#include <iostream>
#include <random>

using namespace std;
int status1 = 0;
int status2 = 0;
float kapalbawah = 100 - 150;
float kapalbawahkiri = 200 - 250;
float kapalbawahkanan = 300 - 250;
float kapalatas = 150 - 150;
float kapalataskiri = 150 - 250;
float kapalataskanan = 350 - 250;
float tiangx = (kapalbawahkiri + kapalbawahkanan) / 2;
float tiangbawah = 150 - 150;
float tiangatas = 200 - 150;
float benderakiribawahy = 160 - 150;
float benderakananx = tiangx + 20;
float benderakanany = 180 - 150;
float aer1 = kapalbawah - 5;
float aer2 = kapalbawah - 10;
float aer2kiri = kapalataskiri + 75;
float aer2kanan = kapalataskanan - 75;
float aer3 = kapalbawah - 15;


float posx = 0;
float krng1 = 1, krng2 = 0, krng3 = 0;
float brng1 = 1, brng2 = 1, brng3 = 1;

int arah = 0;
void summonbentuk() {
	glClearColor(brng1, brng2, brng3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	for (int i = 0; i < 5; i++) {
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_POLYGON);
		glColor3f(krng1, krng2, krng3);
		glVertex2i(kapalbawahkiri, kapalbawah);
		glColor3f(krng3, krng2, krng1);
		glVertex2i(kapalataskiri, kapalatas);
		glColor3f(krng2, krng3, krng1);
		glVertex2i(kapalataskanan, kapalatas);
		glColor3f(krng1, krng3, krng2);
		glVertex2i(kapalbawahkanan, kapalbawah);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(krng1, krng2, krng3);
		glVertex2i(tiangx, tiangbawah);
		glColor3f(krng1, krng3, krng2);
		glVertex2i(tiangx, tiangatas);
		glEnd();

		if (arah == 1) {
			if (i % 3 == 0) {
				glBegin(GL_POLYGON);
				glColor3f(krng1, krng2, krng3);
				glVertex2i(tiangx, tiangatas);
				glColor3f(krng3, krng2, krng1);
				glVertex2i(benderakananx - 5, benderakanany);
				glColor3f(krng2, krng3, krng1);
				glVertex2i(tiangx, benderakiribawahy);
				glEnd();
			}
			else if (i % 3 == 1) {
				glBegin(GL_POLYGON);
				glColor3f(krng1, krng2, krng3);
				glVertex2i(tiangx, tiangatas);
				glColor3f(krng3, krng2, krng1);
				glVertex2i(benderakananx, benderakanany);
				glColor3f(krng2, krng3, krng1);
				glVertex2i(tiangx, benderakiribawahy);
				glEnd();
			}
			else {
				glBegin(GL_POLYGON);
				glColor3f(krng1, krng2, krng3);
				glVertex2i(tiangx, tiangatas);
				glColor3f(krng3, krng2, krng1);
				glVertex2i(benderakananx + 5, benderakanany);
				glColor3f(krng2, krng3, krng1);
				glVertex2i(tiangx, benderakiribawahy);
				glEnd();
			}
		}
		else {
			if (i % 3 == 0) {
				glBegin(GL_POLYGON);
				glColor3f(krng1, krng2, krng3);
				glVertex2i(tiangx, tiangatas);
				glColor3f(krng3, krng2, krng1);
				glVertex2i(-benderakananx - 5, benderakanany);
				glColor3f(krng2, krng3, krng1);
				glVertex2i(tiangx, benderakiribawahy);
				glEnd();
			}
			else if (i % 3 == 1) {
				glBegin(GL_POLYGON);
				glColor3f(krng1, krng2, krng3);
				glVertex2i(tiangx, tiangatas);
				glColor3f(krng3, krng2, krng1);
				glVertex2i(-benderakananx, benderakanany);
				glColor3f(krng2, krng3, krng1);
				glVertex2i(tiangx, benderakiribawahy);
				glEnd();
			}
			else {
				glBegin(GL_POLYGON);
				glColor3f(krng1, krng2, krng3);
				glVertex2i(tiangx, tiangatas);
				glColor3f(krng3, krng2, krng1);
				glVertex2i(-benderakananx + 5, benderakanany);
				glColor3f(krng2, krng3, krng1);
				glVertex2i(tiangx, benderakiribawahy);
				glEnd();
			}
		}

		glBegin(GL_LINE_STRIP);
		glColor3f(krng1, krng2, krng3);
		glVertex2i((kapalbawahkanan - 45) + i * 10, aer1);
		glColor3f(krng3, krng2, krng1);
		glVertex2i((kapalbawahkanan)+i * 10, aer1);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(krng1, krng2, krng3);
		glVertex2i((kapalbawahkiri + 45) - i * 10, aer1);
		glColor3f(krng3, krng2, krng1);
		glVertex2i((kapalbawahkiri)-i * 10, aer1);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(krng3, krng2, krng1);
		glVertex2i((kapalataskiri + 75) - i * 10, aer2);
		glColor3f(krng2, krng3, krng1);
		glVertex2i(kapalataskiri - i * 10, aer2);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(krng2, krng3, krng1);
		glVertex2i((kapalataskanan - 75) + i * 10, aer2);
		glColor3f(krng1, krng2, krng3);
		glVertex2i(kapalataskanan + i * 10, aer2);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(krng1, krng2, krng3);
		glVertex2i((kapalbawahkanan - 45) + i * 10, aer3);
		glColor3f(krng3, krng2, krng1);
		glVertex2i((kapalbawahkanan)+i * 10, aer3);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(krng1, krng2, krng3);
		glVertex2i((kapalbawahkiri + 45) - i * 10, aer3);
		glColor3f(krng3, krng2, krng1);
		glVertex2i((kapalbawahkiri)-i * 10, aer3);
		glEnd();

		if (status1 == 0) {
			glBegin(GL_POLYGON);
			glColor3f(0, 0, 1);
			glVertex2i(-600, -80);
			glVertex2i(-600 + i * 2, -80);
			glVertex2i(-245 - 100 + i * 2, -70);
			glVertex2i(-243 - 100 + i * 2, -60);
			glVertex2i(-241 - 100 + i * 2, -50);
			glVertex2i(-238 - 100 + i * 2, -40);
			glVertex2i(-234 - 100 + i * 2, -30);
			glVertex2i(-231 - 100 + i * 2, -20);
			glVertex2i(-227 - 100 + i * 2, -10);
			glVertex2i(-225 - 100 + i * 2, 0);
			glVertex2i(-222 - 100 + i * 2, 10);
			glVertex2i(-220 - 100 + i * 2, 20);
			glVertex2i(-218 - 100 + i * 2, 30);
			glVertex2i(-215 - 100 + i * 2, 40);
			glVertex2i(-212 - 100 + i * 2, 50);
			glVertex2i(-208 - 100 + i * 2, 60);
			glVertex2i(-203 - 100 + i * 2, 70);
			glVertex2i(-195 - 100 + i * 2, 80);
			glVertex2i(-190 - 100 + i * 2, 90);
			glVertex2i(-600 + i * 2, 60);
			glEnd();
		}

		if (status2 == 0) {
			glBegin(GL_POLYGON);
			glColor3f(0, 0, 1);
			glVertex2i(600, -80);
			glVertex2i(600 - i * 2, -80);
			glVertex2i(245 + 100 - i * 2, -70);
			glVertex2i(243 + 100 - i * 2, -60);
			glVertex2i(241 + 100 - i * 2, -50);
			glVertex2i(238 + 100 - i * 2, -40);
			glVertex2i(234 + 100 - i * 2, -30);
			glVertex2i(231 + 100 - i * 2, -20);
			glVertex2i(227 + 100 - i * 2, -10);
			glVertex2i(225 + 100 - i * 2, 0);
			glVertex2i(222 + 100 - i * 2, 10);
			glVertex2i(220 + 100 - i * 2, 20);
			glVertex2i(218 + 100 - i * 2, 30);
			glVertex2i(215 + 100 - i * 2, 40);
			glVertex2i(212 + 100 - i * 2, 50);
			glVertex2i(208 + 100 - i * 2, 60);
			glVertex2i(203 + 100 - i * 2, 70);
			glVertex2i(195 + 100 - i * 2, 80);
			glVertex2i(190 + 100 - i * 2, 90);
			glVertex2i(600 - i * 2, 60);
			glEnd();
		}

		glFlush();
		Sleep(100);
	}
}

void cek() {
	if (posx < -250) {
		glTranslatef(490, 0, 0);
		posx += 500;
		status1 = 1;
	}
	if (posx > 250) {
		glTranslatef(-490, 0, 0);
		posx -= 500;
		status2 = 1;
	}
	if (posx == 130 || posx == -130) {
		status1 = 0;
		status2 = 0;
	}
	cout << status1 << " " << status2 << '\n';
}
int gede = 0;
void Keyboard(unsigned char huruf, int x, int y)
{
	huruf = tolower(huruf);
	switch (huruf)
	{
	case 'r':
		brng1 = (float)(rand() % 1000) / 1000;
		brng2 = (float)(rand() % 1000) / 1000;
		brng3 = (float)(rand() % 1000) / 1000;
		summonbentuk();
		glFlush();
		cout << "Henshin" << '\n';
		break;

	case 'b':
		krng1 = (float)(rand() % 1000) / 1000;
		krng2 = (float)(rand() % 1000) / 1000;
		krng3 = (float)(rand() % 1000) / 1000;
		summonbentuk();
		glFlush();

		cout << "Henshin" << '\n';
		break;
	case 'a':
		posx -= 10;
		arah = 1;
		cek();

		glTranslatef(-10, 0, 0);
		summonbentuk();
		glFlush();



		cout << posx << '\n';
		glFlush();
		break;
	case 'd':
		posx += 10;
		arah = 2;
		cek();

		glTranslatef(10, 0, 0);
		summonbentuk();
		glFlush();


		cout << posx << '\n';
		glFlush();
		break;
	case 'w':
		gede++;
		glScalef(1.1, 1.1, 0);
		summonbentuk();
		glFlush();
		cout << gede << '\n';
		break;
	case 's':
		gede--;
		glScalef(0.9, 0.9, 0);
		summonbentuk();
		glFlush();
		cout << gede << '\n';
		break;
	}
}
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(brng1, brng2, brng3, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(100 - 250, 400.0 - 250, 50 - 150, 250.0 - 150);
	summonbentuk();
	glFlush();

}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(8.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(100, 400.0, 50, 250.0);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); //toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("ashiyap");
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(Keyboard);
	myInit();
	glutMainLoop();
}