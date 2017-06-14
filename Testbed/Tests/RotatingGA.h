#include <iostream>
#pragma once
#ifndef ROTATINGGA_H
#define ROTATINGGA_H
#define DEGTORAD 0.0174532925199432957f
using namespace std;

class RotatingGA : public Test
{
public:
	//class member variable
	b2Body* body;
	//class member variable
	b2Vec2 clickedPoint;


	RotatingGA() { 
	
		//body definition
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody;

		//hexagonal shape definition
		b2PolygonShape polygonShape;
		b2Vec2 vertices[6];
		for (int i = 0; i < 6; i++) {
			float angle = -i / 6.0 * 360 * DEGTORAD;
			vertices[i].Set(sinf(angle), cosf(angle));
		}
		vertices[0].Set(0, 4); //change one vertex to be pointy
		polygonShape.Set(vertices, 6);

		//fixture definition
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &polygonShape;
		myFixtureDef.density = 1;

		//create dynamic body
		myBodyDef.position.Set(0, 10);
		body = m_world->CreateBody(&myBodyDef);
		body->CreateFixture(&myFixtureDef);

		//zero gravity
		m_world->SetGravity(b2Vec2(0, 0));
		
		//in class constructor
		clickedPoint = b2Vec2(0, 20);//initial starting point


	} //do nothing, no scene yet

	  //override parent class
	void MouseDown(const b2Vec2& p)
	{
		cout << "asdf" << endl;

		//store last mouse-down position
		clickedPoint = p;

		//do normal behaviour
		Test::MouseDown(p);
	}

	void Step(Settings* settings)
	{
		//run the default physics and rendering
		//inside Step()
		/*glPointSize(4);
		glBegin(GL_POINTS);
		glVertex2f(clickedPoint.x, clickedPoint.y);
		glEnd();*/

		////in Step() function
		float bodyAngle = body->GetAngle();
		b2Vec2 toTarget = clickedPoint - body->GetPosition();
		float desiredAngle = atan2f(-toTarget.x, toTarget.y);

		//body->SetTransform(body->GetPosition(), desiredAngle);

		//body->SetAngularVelocity(0);

		//float totalRotation = desiredAngle - bodyAngle;
		//float change = 1 * DEGTORAD; //allow 1 degree rotation per time step
		//float newAngle = bodyAngle + min(change, max(-change, totalRotation));
		//body->SetTransform(body->GetPosition(), newAngle);

		float nextAngle = bodyAngle + body->GetAngularVelocity() / 3.0;
		float totalRotation = desiredAngle - nextAngle;//use angle in next time step
		body->ApplyTorque(totalRotation < 0 ? -10 : 10, true);

#define RADTODEG 57.295779513082320876f


		//view these in real time
		g_debugDraw.DrawString(5, m_textLine, "Body angle %.3f", bodyAngle * RADTODEG);
		m_textLine += 15;
		g_debugDraw.DrawString(5, m_textLine, "Target angle %.3f", desiredAngle * RADTODEG);
		m_textLine += 15;

		Test::Step(settings);

	}

	static Test* Create()
	{
		return new RotatingGA;
	}
};

#endif