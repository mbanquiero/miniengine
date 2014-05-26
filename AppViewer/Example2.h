#pragma once

class Example2: public IExample
{
public:
	Example2();
	~Example2();

	virtual const char * getName();
	virtual const char * getDescription();
	virtual void init();
	virtual void render(float elapsedTime);
	virtual void close();

};

