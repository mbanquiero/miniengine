#pragma once

#include "FpsCamera.h"
#include <graphics\RenderEngine.h>
#include <graphics\SkeletalMesh.h>



class CEnemigo
{
public:
	Vector3 pos;
	Vector3 size;
	float ang;
	float vel;
	Vector3 lookFrom;
	Vector3 lookAt;
	Vector3 dir_cam;
	bool fps_cam;

	CSkeletalMesh *p_mesh;
	CEnemigo();
	~CEnemigo();
	void Update(float elapsedTime);
	void Render();


};


class Example2: public IExample
{
public:
	CFpsCamera m_camera;

public:
	Example2();
	~Example2();

	CEnemigo *p_enemigo;
	virtual const char * getName();
	virtual const char * getDescription();
	virtual void init();
	virtual void render(float elapsedTime);
	virtual void close();

};

