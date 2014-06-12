#include "stdafx.h"
#include "Example3.h"


CZombie::CZombie(char *mesh_name)
{
	// Cargo el escenario del 4to piso
	char mesh_path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, mesh_path);
	for (char * p = mesh_path; *p; p++) if (*p == '\\') *p = '/';
	char fname[MAX_PATH];
	strcpy(fname,mesh_path);
	strcat(fname,mesh_name);
	p_mesh = new CSkeletalMesh;
	if(!p_mesh->LoadFromXMLFile(&_engine,fname))
	{
		SAFE_DELETE(p_mesh);			// y p_mesh queda en NULL
	}
	else
	{
		p_mesh->initAnimation(8,true,10);
		pos = Vector3(0,0,0);
		size = p_mesh->m_size;
		ang = 0;
		vel = 35;
		rtime = 1;
	}

}

CZombie::~CZombie()
{
	SAFE_DELETE(p_mesh);			// y p_mesh queda en NULL
}


void CZombie::Update(float elapsedTime)
{
	rtime-=elapsedTime;
	if(rtime<0)
	{
		rtime+=1;
		// cambio de direccion
		if(rand()>RAND_MAX/2)
			ang+=0.3;
		else
			ang-=0.3;
	}

	Vector3 dir = Vector3(-sin(ang),0,-cos(ang));
	pos += dir * (vel * elapsedTime);

	if(p_mesh)
		p_mesh->updateAnimation();
}

void CZombie::Render()
{
	if(p_mesh)
		p_mesh->Render(pos+size*0.5f,size,D3DXVECTOR3(0,ang,0));
}

CPersonaje::CPersonaje(char *mesh_name):CZombie(mesh_name)
{
	dir_cam = Vector3(0,1,2);
	dir_cam.Normalize();
	fps_cam = true;
}

void CPersonaje::Update(float elapsedTime)
{
	if (InputManager::IsDown(DInputKey::Key_LeftArrow))
	{
		ang-=1*elapsedTime;
	}
	if (InputManager::IsDown(DInputKey::Key_RightArrow))
	{
		ang+=1*elapsedTime;
	}
	if (InputManager::IsPressed(DInputKey::Key_Space))
	{
		fps_cam = !fps_cam;
	}


	Vector3 dir = Vector3(-sin(ang),0,-cos(ang));
	pos += dir * (vel * elapsedTime);

	if(fps_cam)
	{
		lookAt = pos;
		lookFrom = pos + dir_cam*150;
		float ant_Y = dir_cam.Y;
		dir_cam = (dir_cam - dir) * 0.5;
		dir_cam.Y = ant_Y;
	}
	else
	{
		lookFrom = pos + dir*3;
		lookAt = pos + dir*100;
		lookAt.Y = lookFrom.Y = pos.Y + size.Y*0.75;
	}


	if(p_mesh)
		p_mesh->updateAnimation();
}


REGISTER_EXAMPLE(Example3)

Example3::Example3()
{
}


Example3::~Example3()
{
}

const char * Example3::getName()
{
	return "0-Muchos enemigos";
}

const char * Example3::getDescription()
{
	return "Escenario con muchos enemigos";
}

void Example3::init()
{
	InputManager::Init();

	_engine.lighting_enabled = false;

	// Cargo el escenario del 4to piso
	char mesh_path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, mesh_path);
	//por algun motivo no anda usando un path relativo y usando \ en vez de /
	//reemplazo todas las \\ por /
	for (char * p = mesh_path; *p; p++) if (*p == '\\') *p = '/';

	char fname[MAX_PATH];
	strcpy(fname,mesh_path);
	strcat(fname,"/media/4toPiso/4toPiso.flat");
	_engine.LoadSceneFromFlat(fname);

	Vector3 escena_p0 = _engine.m_mesh[0]->m_pos;
	Vector3 escena_p1 = _engine.m_mesh[0]->m_pos + _engine.m_mesh[0]->m_size;
	for(int i=1;i<_engine.cant_mesh ; ++i)
	{

		Vector3 p0 = _engine.m_mesh[i]->m_pos;
		Vector3 p1 = _engine.m_mesh[i]->m_pos + _engine.m_mesh[i]->m_size;
		if(p0.X < escena_p0.X)
			escena_p0.X = p0.X;
		if(p0.Y < escena_p0.Y)
			escena_p0.Y = p0.Y;
		if(p0.Z < escena_p0.Z)
			escena_p0.Z = p0.Z;

		if(p1.X > escena_p1.X)
			escena_p1.X = p1.X;
		if(p1.Y > escena_p1.Y)
			escena_p1.Y = p1.Y;
		if(p1.Z > escena_p1.Z)
			escena_p1.Z = p1.Z;

	}

	Vector3 escena_size = escena_p1 - escena_p0;

	// Creo al personaje
	p_personaje = new CPersonaje("/media/SkeletalAnimations/BasicHuman/CombineSoldier-TgcSkeletalMesh.xml");
	// Creo los zombies
	for(int i=0;i<MAX_ZOMBIES;++i)
	{
		p_zombies[i] = new CZombie("/media/SkeletalAnimations/BasicHuman/WomanJeans-TgcSkeletalMesh.xml");
		p_zombies[i]->pos.X = escena_p0.X + (float)rand()/(float)RAND_MAX*escena_size.X*0.25;
		p_zombies[i]->pos.Z = escena_p0.Z + (float)rand()/(float)RAND_MAX*escena_size.Z*0.25;
		p_zombies[i]->ang = (float)rand()/(float)RAND_MAX * 2 * 3.1415f;
	}

	m_camera.m_lookFrom.Set(181.8, 54.2, 200.8);
	m_camera.m_lookAt.Set(171.3, 54.1, 199.9);
}

void Example3::render(float elapsedTime)
{
	InputManager::Update();

	m_camera.UpdateCamera();
//	_engine.lookAt = m_camera.m_lookAt;
//	_engine.lookFrom = m_camera.m_lookFrom;

	// sigo al personaje
	_engine.lookAt = p_personaje->lookAt;
	_engine.lookFrom = p_personaje->lookFrom;

	for (int i = 0; i < _engine.cant_mesh; i++)
		_engine.m_mesh[i]->Render();

	p_personaje->Update(elapsedTime);
	p_personaje->Render();

	for (int i = 0; i < MAX_ZOMBIES; i++)
	{
		p_zombies[i]->Update(elapsedTime);
		p_zombies[i]->Render();
	}
}

void Example3::close()
{

	// libero el personaje
	delete p_personaje;
	// libero los zombies
	for(int i=0;i<MAX_ZOMBIES;++i)
		delete p_zombies[i];

}

