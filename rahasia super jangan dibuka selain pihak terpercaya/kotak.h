




class kotak {
private:
	const float m2p = 20; //meter to pixel
	const float p2m = 1 / m2p; //pixel to meter
	const float PI = 3.14;
public:
	b2Body* addRectangle(int x, int y, int w, int h, bool dyn = true);
	void drawSquare(b2Vec2* points, b2Vec2 center, float angle, GLuint id);
	b2World* world;
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

void kotak::drawSquare(b2Vec2* points, b2Vec2 center, float angle, GLuint id) {
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(center.x * m2p, center.y * m2p, 0);
	glRotatef(angle * 180.0 / PI, 0, 0, 1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(points[0].x* m2p, points[0].y* m2p);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(points[1].x * m2p, points[1].y * m2p);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(points[2].x * m2p, points[2].y * m2p);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(points[3].x * m2p, points[3].y * m2p);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glFlush();
}