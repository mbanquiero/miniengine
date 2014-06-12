#include "stdafx.h"
#include "Example2.h"


//nota: 
// lo que empezo siendo el enemigo ahora es el personaje pp dicho....

CEnemigo::CEnemigo()
{
	// Cargo el escenario del 4to piso
	char mesh_path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, mesh_path);
	for (char * p = mesh_path; *p; p++) if (*p == '\\') *p = '/';
	char fname[MAX_PATH];
	strcpy(fname,mesh_path);
	strcat(fname,"/media/SkeletalAnimations/BasicHuman/WomanJeans-TgcSkeletalMesh.xml");
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
		dir_cam = Vector3(0,1,2);
		dir_cam.Normalize();
		fps_cam = true;
	}

}

CEnemigo::~CEnemigo()
{
	SAFE_DELETE(p_mesh);			// y p_mesh queda en NULL
}


void CEnemigo::Update(float elapsedTime)
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

void CEnemigo::Render()
{

	if(p_mesh)
		p_mesh->Render(pos+size*0.5f,size,D3DXVECTOR3(0,ang,0));
}


REGISTER_EXAMPLE(Example2)

Example2::Example2()
{
}


Example2::~Example2()
{
}

const char * Example2::getName()
{
	return "Ejemplo 4to piso";
}

const char * Example2::getDescription()
{
	return "Descripcion de ejemplo de prueba2";
}

void CompactMeshes2()
{
	int cant_vertices = 0;
	int cant_indices = 0;
	int cant_faces = 0;
	int cant_layers = _engine.cant_texturas;

	CMesh * m = new CMesh;
	for (int i = 0; i < _engine.cant_mesh; i++)
	{
		cant_vertices += _engine.m_mesh[i]->cant_vertices;
		cant_indices += _engine.m_mesh[i]->cant_indices;
		cant_faces += _engine.m_mesh[i]->cant_faces;
	}

	m->pVertices = new MESH_VERTEX[cant_vertices];
	m->pIndices = new DWORD[cant_indices];
	m->pAttributes = new DWORD[cant_faces];
	m->cant_layers = cant_layers;

	for (int i = 0; i < _engine.cant_mesh; i++)
	{
		CMesh * t = _engine.m_mesh[i];

		memcpy(m->pVertices + m->cant_vertices, t->pVertices, t->cant_vertices*sizeof(MESH_VERTEX));

		for (int j = 0; j < t->cant_indices; j++)
		{
			m->pIndices[m->cant_indices + j] = t->pIndices[j] + m->cant_vertices;
		}

		for (int j = 0; j < t->cant_faces; j++)
		{
			m->pAttributes[m->cant_faces + j] = t->layers[t->pAttributes[j]].nro_material;
		}

		for (int j = 0; j < t->cant_layers; j++)
		{
			m->layers[t->layers[j].nro_material] = t->layers[j];
		}

		m->cant_vertices += t->cant_vertices;
		m->cant_indices += t->cant_indices;
		m->cant_faces += t->cant_faces;
	}

	_engine.ReleaseMeshes();

	m->engine = &_engine;
	m->CreateMeshFromData(&_engine);


	_engine.m_mesh[0] = m;
	_engine.cant_mesh = 1;


}



void Example2::init()
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

	// Creo al enemeigo
	p_enemigo = new CEnemigo();

	m_camera.m_lookFrom.Set(181.8, 54.2, 200.8);
	m_camera.m_lookAt.Set(171.3, 54.1, 199.9);
}

void Example2::render(float elapsedTime)
{
	InputManager::Update();

	m_camera.UpdateCamera();
	//_engine.lookAt = m_camera.m_lookAt;
	//_engine.lookFrom = m_camera.m_lookFrom;

	// sigo al enemigo
	_engine.lookAt = p_enemigo->lookAt;
	_engine.lookFrom = p_enemigo->lookFrom;

	for (int i = 0; i < _engine.cant_mesh; i++)
		_engine.m_mesh[i]->Render();

	p_enemigo->Update(elapsedTime);
	p_enemigo->Render();
}

void Example2::close()
{

}

