class kotak {
private:
	const float m2p = 20; //meter to pixel
	const float p2m = 1 / m2p; //pixel to meter
	const float PI = 3.14;
	b2World* world;
public:
	b2Body* addRectangle(int x, int y, int w, int h, bool dyn = true);
	void drawSquare(b2Vec2* points, b2Vec2 center, float angle);
	kotak(b2World* world2) {
		world = world2;
	};
};
b2Body* kotak::addRectangle(int x, int y, int w, int h, bool dyn) { //add bodydef
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

void kotak::drawSquare(b2Vec2* points, b2Vec2 center, float angle) {
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