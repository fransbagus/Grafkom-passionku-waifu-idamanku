class lingkaran {
private:
	const float m2p = 20; //meter to pixel
	const float p2m = 1 / m2p; //pixel to meter
	const float PI = 3.14;
	b2World* world;
public:
	b2Body* addCircle(int x, int y, int r, bool dyn = true);
	void drawCircle(b2Vec2 center, float r, float angle);
	lingkaran(b2World* world2) {
		world = world2;
	};
};


b2Body* lingkaran::addCircle(int x, int y, int r, bool dyn) {
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

void lingkaran::drawCircle(b2Vec2 center, float r, float angle) {
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