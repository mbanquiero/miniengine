#pragma once

#include "FpsCamera.h"
#include <graphics\RenderEngine.h>
#include <graphics\SkeletalMesh.h>

#define  MAX_ZOMBIES	50
class CZombie
{
public:
	Vector3 pos;
	Vector3 size;
	float ang;
	float vel;
	float rtime;					// remaining time hasta que cambia de direccion
	CSkeletalMesh *p_mesh;
	CZombie(char *mesh_name);
	~CZombie();
	virtual void Update(float elapsedTime);
	virtual void Render();
};


class CPersonaje : public CZombie
{
public:
	Vector3 lookFrom;
	Vector3 lookAt;
	Vector3 dir_cam;
	bool fps_cam;
	CPersonaje(char *mesh_name);
	virtual void Update(float elapsedTime);
};


class Example3: public IExample
{
public:
	CFpsCamera m_camera;
	CZombie *p_zombies[MAX_ZOMBIES];
	CPersonaje *p_personaje;

	Example3();
	~Example3();
	virtual const char * getName();
	virtual const char * getDescription();
	virtual void init();
	virtual void render(float elapsedTime);
	virtual void close();

};



