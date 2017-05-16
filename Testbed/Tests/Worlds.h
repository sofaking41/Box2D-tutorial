#pragma once
#ifndef	WORLDS_H
#define WORLDS_H

class Worlds : public Test
{
public: 
	Worlds() {
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody; //���̳��� �ٵ� ����
		myBodyDef.position.Set(0, 20); 
		myBodyDef.angle = 0; 
		b2Body* dynamicBody = m_world->CreateBody(&myBodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(1, 1);

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.density = 1;
		dynamicBody->CreateFixture(&boxFixtureDef);
		// ���̳��� �ٵ�

		//�߷º��� �Լ��� ����� �Ұ�...
		b2Vec2 gravity(0, -9.8); // �߷�
		bool doSleep = true;
		
		//b2World* myWorld = new b2World(gravity, doSleep);
		//myWorld->SetGravity(b2Vec2(0, 0));
		//float32 timeStep = 1 / 20.0;      //the length of time passed to simulate (seconds)
		//int32 velocityIterations = 8;   //how strongly to correct velocity
		//int32 positionIterations = 3;   //how strongly to correct position

		//myWorld->Step(timeStep, velocityIterations, positionIterations);
		
	} //do nothing, no scene yet

	void Step(Settings* settings)
	{
		//run the default physics and rendering
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new Worlds;
	}
};

#endif