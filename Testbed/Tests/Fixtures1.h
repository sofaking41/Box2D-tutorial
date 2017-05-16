#pragma once
#ifndef FIXTURES1_H
#define FIXTURES1_H
#define DEGTORAD 0.0174532925199432957f

class Fixtures1 : public Test
{
public:
	Fixtures1() {
		//set up a dynamic body
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody;
		myBodyDef.position.Set(0, 20); //middle
		b2Body* dynamicBody = m_world->CreateBody(&myBodyDef);

		//prepare a shape definition
		b2PolygonShape polygonShape;
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &polygonShape;
		myFixtureDef.density = 1;
		myFixtureDef.friction = 1; //���� 0
		myFixtureDef.restitution = 1; // 0�϶��� �ٿ���� ����: ����� �ٿ���� �ϸ� ���ݾ� ����������

		//add four square shaped fixtures around the body center
		for (int i = 0; i < 4; i++) {
			
			b2Vec2 pos(sinf(i * 90 * DEGTORAD), cosf(i * 90 * DEGTORAD)); //radial placement
			polygonShape.SetAsBox(1, 1, pos, 0); //a 2x2 rectangle
			dynamicBody->CreateFixture(&myFixtureDef); //add a fixture to the body
			myFixtureDef.friction = i / 4.0; // �̲������� ���� �ӵ� ���������ϰ� �ϴ� ������
		}

		//make a static floor to drop things on
		myBodyDef.type = b2_staticBody;
		myBodyDef.position.Set(0, 0); //middle, bottom
		b2Body* staticBody = m_world->CreateBody(&myBodyDef);

		//SetAsEdge ��ü �ڵ�
		b2EdgeShape edgeShape;
		edgeShape.Set(b2Vec2(-15, 0), b2Vec2(15, 3));

		myFixtureDef.shape = &edgeShape;
		//polygonShape.SetAsEdge(b2Vec2(-15, 0), b2Vec2(15, 3)); //slightly sloped  
		staticBody->CreateFixture(&myFixtureDef); //add a fixture to the body
	
	} //do nothing, no scene yet

	void Step(Settings* settings)
	{
		//run the default physics and rendering
		Test::Step(settings);
		
	}

	static Test* Create()
	{
		return new Fixtures1;
	}
};

#endif