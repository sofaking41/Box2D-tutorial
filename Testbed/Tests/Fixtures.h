#pragma once
#ifndef FIXTURES_H
#define FIXTURES_H

class Fixtures : public Test
{
public:
	Fixtures() {
		b2BodyDef myBodyDef;
		
		myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		myBodyDef.position.Set(-10, 20); //a little to the left

		b2Body* dynamicBody1 = m_world->CreateBody(&myBodyDef);

		b2CircleShape circleShape;
		circleShape.m_p.Set(0, 0); //position, relative to body position
		circleShape.m_radius = 1; //radius

		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &circleShape; //this is a pointer to the shape above
		dynamicBody1->CreateFixture(&myFixtureDef); //add a fixture to the body
		myFixtureDef.density = 1; //밀도
		//임의의 모형
													//set each vertex of polygon in an array
		b2Vec2 vertices[5]; // 각 꼭지점 좌표
		vertices[0].Set(-1, 2);
		vertices[1].Set(-1, 0);
		vertices[2].Set(0, -3);
		vertices[3].Set(1, 0);
		vertices[4].Set(1, 1);

		b2PolygonShape polygonShape;
		polygonShape.Set(vertices, 5); //pass array to the shape

		myFixtureDef.shape = &polygonShape; //change the shape of the fixture
		myBodyDef.position.Set(0, 20); //in the middle
		b2Body* dynamicBody2 = m_world->CreateBody(&myBodyDef);
		dynamicBody2->CreateFixture(&myFixtureDef); //add a fixture to the body
		myFixtureDef.density = 1; //밀도
		//사각형
		polygonShape.SetAsBox(2, 1); //a 4x2 rectangle 상자 너비, 높이 결정
		myBodyDef.position.Set(10, 20); //a bit to the right

		b2Body* dynamicBody3 = m_world->CreateBody(&myBodyDef);
		dynamicBody3->CreateFixture(&myFixtureDef); //add a fixture to the body
		myFixtureDef.density = 1; //밀도

		//스테틱 바디의 사각형을 직선으로 폈음
		myBodyDef.type = b2_staticBody; //change body type
		myBodyDef.position.Set(0, 0); //middle, bottom

		//setasEdge 함수가 현버전에 없음.... 직선으로 펴주는 역할
		b2EdgeShape edgeShape;
		edgeShape.Set(b2Vec2(-15, 0), b2Vec2(15, 0));
		myFixtureDef.shape = &edgeShape;
		//polygonShape.SetAsEdge(b2Vec2(-15, 0), b2Vec2(15, 0)); //현버전에서 제거된 기능
		b2Body* staticBody = m_world->CreateBody(&myBodyDef);
		staticBody->CreateFixture(&myFixtureDef); //add a fixture to the body


		
		
		
	} //do nothing, no scene yet

	void Step(Settings* settings)
	{
		//run the default physics and rendering
		Test::Step(settings);


	}

	static Test* Create()
	{
		return new Fixtures;
	}
};

#endif