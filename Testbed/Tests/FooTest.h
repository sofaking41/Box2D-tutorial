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

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Now we have a foo test");
		m_textLine += 15;
	}

	static Test* Create()
	{
		return new FooTest;
	}
};

#endif