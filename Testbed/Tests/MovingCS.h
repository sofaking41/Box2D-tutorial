#pragma once
#include <iostream>
#ifndef MOVINGCS_H
#define MOVINGCS_H

class MovingCS : public Test
{
public:
	//enumeration of possible input states
	enum _moveState {
		MS_STOP,
		MS_LEFT,
		MS_RIGHT,
	};

	//class member variables
	b2Body* body;
	_moveState moveState;

	MovingCS() { 
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

	//작동을 안함...
	void Keyboard(int key)
	{
		using namespace std;
		cout << "asdf" << endl;
		switch (key)
		{
		case 'q': //move left
			moveState = MS_LEFT;
			break;
		case 'w': //stop
			moveState = MS_STOP;
			break;
		case 'e': //move right
			moveState = MS_RIGHT;
			break;
		default:
			//run default behaviour
			Test::Keyboard(key);
		}
	}

	void Step(Settings* settings)
	{
		//run the default physics and rendering
		Test::Step(settings);
		b2Vec2 vel = body->GetLinearVelocity();
		switch (moveState)
		{
		case MS_LEFT:  vel.x = -5; break;
		case MS_STOP:  vel.x = 0; break;
		case MS_RIGHT: vel.x = 5; break;
		}
		body->SetLinearVelocity(vel);
		
		// 점진적 가속... 하지만 구현이 아직 안됨...
		/*switch (moveState)
		{
		case MS_LEFT:  vel.x = b2Max(vel.x - 0.1f, -5.0f); break;
		case MS_STOP:  vel.x *= 0.98; break;
		case MS_RIGHT: vel.x = b2Min(vel.x + 0.1f, 5.0f); break;
		}*/
		//0.1만큼 이동방향으로 최대 5까지 증가: 정지할때는 이전 프레임속도의 98%로 감소

		//힘에 의한 가속
		/*b2Vec2 vel = body->GetLinearVelocity();
		float force = 0;
		switch (moveState)
		{
		case MS_LEFT:  if (vel.x > -5) force = -50;  break;
		case MS_STOP:  force = vel.x * -10; break;
		case MS_RIGHT: if (vel.x <  5) force = 50; break;
		}
		body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter());*/
		//
		//b2Vec2 vel = body->GetLinearVelocity();
		//float desiredVel = 0;
		//switch (moveState)
		//{
		//case MS_LEFT:  desiredVel = -5; break;
		//case MS_STOP:  desiredVel = 0; break;
		//case MS_RIGHT: desiredVel = 5; break;
		//}
		//float velChange = desiredVel - vel.x;
		//float force = body->GetMass() * velChange / (1 / 60.0); //f = mv/t
		//body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter());

		//충동
		//b2Vec2 vel = body->GetLinearVelocity();
		//float desiredVel = 0;
		//switch (moveState)
		//{
		//case MS_LEFT:  desiredVel = -5; break;
		//case MS_STOP:  desiredVel = 0; break;
		//case MS_RIGHT: desiredVel = 5; break;
		
		//점진적 가속
		/* case MS_LEFT:  desiredVel = b2Max(vel.x - 0.1f, -5.0f); break;
		 case MS_STOP:  desiredVel = vel.x * 0.98f; break;
		 case MS_RIGHT: desiredVel = b2Min(vel.x + 0.1f, 5.0f); break;*/
		//}
		//float velChange = desiredVel - vel.x;
		//float impulse = body->GetMass() * velChange; //disregard time factor
		//body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter());
	}

	static Test* Create()
	{
		return new MovingCS;
	}
};

#endif