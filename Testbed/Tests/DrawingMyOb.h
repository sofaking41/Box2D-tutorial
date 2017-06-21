#pragma once

#ifndef DRAWINGMYOB_H
#define DRAWINGMYOB_H
#include <vector>

class Ball {
public:
	//class member variables
	b2Body* m_body;
	float m_radius;

public:
	Ball(b2World* world, float radius) {
		m_body = NULL;
		m_radius = radius;
	}
	~Ball() {}
	//Ball::render
	void render() {
		glColor3f(1, 1, 1);//white

						   //nose and eyes
		glPointSize(4);
		glBegin(GL_POINTS);
		glVertex2f(0, 0);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glEnd();

		//mouth
		glBegin(GL_LINES);
		glVertex2f(-0.5, -0.5);
		glVertex2f(-0.16, -0.6);
		glVertex2f(0.16, -0.6);
		glVertex2f(0.5, -0.5);
		glEnd();

		//circle outline
		glBegin(GL_LINE_LOOP);
		for (float a = 0; a < 360 * DEGTORAD; a += 30 * DEGTORAD)
			glVertex2f(sinf(a), cosf(a));
		glEnd();
	}
};

class DrawingMyOb : public Test
{
public:
	std::vector<Ball*> balls;
	DrawingMyOb() { 
		//a static body
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_staticBody;
		myBodyDef.position.Set(0, 0);
		b2Body* staticBody = m_world->CreateBody(&myBodyDef);

		//shape definition
		b2PolygonShape polygonShape;

		//fixture definition
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &polygonShape;

		//add four walls to the static body
		polygonShape.SetAsBox(20, 1, b2Vec2(0, 0), 0);//ground
		staticBody->CreateFixture(&myFixtureDef);
		polygonShape.SetAsBox(20, 1, b2Vec2(0, 40), 0);//ceiling
		staticBody->CreateFixture(&myFixtureDef);
		polygonShape.SetAsBox(1, 20, b2Vec2(-20, 20), 0);//left wall
		staticBody->CreateFixture(&myFixtureDef);
		polygonShape.SetAsBox(1, 20, b2Vec2(20, 20), 0);//right wall
		staticBody->CreateFixture(&myFixtureDef);
	} //do nothing, no scene yet

	

	void Step(Settings* settings)
	{
		//run the default physics and rendering
		Test::Step(settings);

		//in Step() function, after Test::Step()
		for (int i = 0; i < balls.size(); i++)
			balls[i]->render();

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Now we have a foo test");
		m_textLine += 15;
	}


	static Test* Create()
	{
		return new DrawingMyOb;
	}
};

#endif