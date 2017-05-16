#pragma once
#ifndef CUSTOMG_H
#define CUSTOMG_H

class CustomG : public Test
{
public:
	//class member variable to keep track of three bodies
	b2Body* bodies[3];
	CustomG() { 
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

			//create identical bodies in different positions
			for (int i = 0; i < 3; i++) {
				myBodyDef.position.Set(-10 + i * 10, 20);
				bodies[i] = m_world->CreateBody(&myBodyDef);
				bodies[i]->CreateFixture(&myFixtureDef);
			}

			//a static floor to drop things on
			myBodyDef.type = b2_staticBody;
			myBodyDef.position.Set(0, 0);
			
			//SetAsEdge 대체 코드
			b2EdgeShape edgeShape;
			edgeShape.Set(b2Vec2(-15, 0), b2Vec2(15, 0));

			myFixtureDef.shape = &edgeShape;

			//polygonShape.SetAsEdge(b2Vec2(-15, 0), b2Vec2(15, 0));
			m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

			//in the Step() function
			//cancel gravity for body 1 only
			//bodies[1]->ApplyForce(bodies[1]->GetMass() * -m_world->GetGravity(), bodies[1]->GetWorldCenter());
			//작동불가
	} //do nothing, no scene yet

	void Step(Settings* settings)
	{
		//run the default physics and rendering
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new CustomG;
	}
};

#endif