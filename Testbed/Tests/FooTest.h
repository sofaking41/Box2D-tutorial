#pragma once
#ifndef FOOTEST_H
#define FOOTEST_H

class FooTest : public Test
{
public:
	FooTest() { } //do nothing, no scene yet

	void Step(Settings* settings)
	{
		//run the default physics and rendering
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new FooTest;
	}
};

#endif