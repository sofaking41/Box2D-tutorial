#pragma once
#ifndef ROTATINGGA_H
#define ROTATINGGA_H
#define DEGTORAD 0.0174532925199432957f

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
		//store last mouse-down position
		clickedPoint = p;

		//do normal behaviour
		Test::MouseDown(p);
	}

	void Step(Settings* settings)
	{
		//run the default physics and rendering
		Test::Step(settings);
		//inside Step()
		glPointSize(4);
		glBegin(GL_POINTS);
		glVertex2f(clickedPoint.x, clickedPoint.y);
		glEnd();

		//in Step() function
		float bodyAngle = body->GetAngle();
		b2Vec2 toTarget = clickedPoint - body->GetPosition();
		float desiredAngle = atan2f(-toTarget.x, toTarget.y);

		//view these in real time
		/*m_debugDraw.DrawString(5, m_textLine, "Body angle %.3f", bodyAngle * RADTODEG);
		m_textLine += 15;
		m_debugDraw.DrawString(5, m_textLine, "Target angle %.3f", desiredAngle * RADTODEG);
		m_textLine += 15;*/

	}

	static Test* Create()
	{
		return new RotatingGA;
	}
};

#endif