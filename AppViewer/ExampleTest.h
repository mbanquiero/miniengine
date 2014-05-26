#pragma once
#include "Example.h"

class CExampleTest :
	public IExample
{
public:
	CExampleTest();
	~CExampleTest();
	virtual const char * getName();
	virtual const char * getDescription();
	virtual void init();
	virtual void render(float elapsedTime);
	virtual void close();
};

