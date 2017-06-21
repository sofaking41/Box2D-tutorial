#pragma once
#pragma once

#ifndef UDD_H
#define UDD_H
#include <iostream>
using namespace std;

class UDD : public Test
{
public:
	enum _moveState {
		MS_STOP,
		MS_LEFT,
		MS_RIGHT,
	};

	b2Body* body;
	_moveState moveState;
	UDD() { 
		//body definition
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody;

		//shape definition
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(1, 1); //a 2x2 rectangle

									 //fixture definition
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &polygonShape;
		myFixtureDef.density = 1;

		//create dynamic body
		myBodyDef.position.Set(0, 10);
		body = m_world->CreateBody(&myBodyDef);
		body->CreateFixture(&myFixtureDef);

		//a static body
		myBodyDef.type = b2_staticBody;
		myBodyDef.position.Set(0, 0);
		b2Body* staticBody = m_world->CreateBody(&myBodyDef);

		//add four walls to the static body
		polygonShape.SetAsBox(20, 1, b2Vec2(0, 0), 0);//ground
		staticBody->CreateFixture(&myFixtureDef);
		polygonShape.SetAsBox(20, 1, b2Vec2(0, 40), 0);//ceiling
		staticBody->CreateFixture(&myFixtureDef);
		polygonShape.SetAsBox(1, 20, b2Vec2(-20, 20), 0);//left wall
		staticBody->CreateFixture(&myFixtureDef);
		polygonShape.SetAsBox(1, 20, b2Vec2(20, 20), 0);//right wall
		staticBody->CreateFixture(&myFixtureDef);

		moveState = MS_STOP;
	} //do nothing, no scene yet

	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		//set up vertex array
		GLfloat glverts[16]; //allow for polygons up to 8 vertices
		glVertexPointer(2, GL_FLOAT, 0, glverts); //tell OpenGL where to find vertices
		glEnableClientState(GL_VERTEX_ARRAY); //use vertices in subsequent calls to glDrawArrays

											  //fill in vertex positions as directed by Box2D
		for (int i = 0; i < vertexCount; i++) {
			glverts[i * 2] = vertices[i].x;
			glverts[i * 2 + 1] = vertices[i].y;
		}

		//draw solid area
		glColor4f(color.r, color.g, color.b, 1);
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

		//draw lines
		glLineWidth(3); //fat lines
		glColor4f(1, 0, 1, 1); //purple
		glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

		cout << "aaa" << endl;
	}

	void Step(Settings* settings)
	{
		//run the default physics and rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Now we have a foo test");
		m_textLine += 15;
	}

	static Test* Create()
	{
		return new UDD;
	}
};

#endif