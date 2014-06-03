#pragma once
#include "Example.h"
#include "FpsCamera.h"

class CExampleTest :
	public IExample
{

protected:
	CFpsCamera m_camera;

public:
	CExampleTest();
	~CExampleTest();
	virtual const char * getName();
	virtual const char * getDescription();
	virtual void init();
	virtual void render(float elapsedTime);
	virtual void close();
	virtual void loadEscene(const char * path);
};

