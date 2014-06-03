#include "stdafx.h"
#include "Example2.h"


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
			m->pAttributes[m->cant_faces + j] = t->layers[t->pAttributes[j]].nro_textura;
		}

		for (int j = 0; j < t->cant_layers; j++)
		{
			m->layers[t->layers[j].nro_textura] = t->layers[j];
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

	char mesh_path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, mesh_path);
	strcat(mesh_path, "\\media\\4toPiso\\4toPiso.flat");

	//por algun motivo no anda usando un path relativo y usando \ en vez de /
	//reemplazo todas las \\ por /
	for (char * p = mesh_path; *p; p++) if (*p == '\\') *p = '/';

	_engine.LoadSceneFromFlat(mesh_path);

	m_camera.m_lookFrom.Set(500, 100, 400);
	m_camera.m_lookAt.Set(500, 100, 500);
}

void Example2::render(float elapsedTime)
{
	InputManager::Update();

	m_camera.UpdateCamera();

	_engine.lookAt = m_camera.m_lookAt;
	_engine.lookFrom = m_camera.m_lookFrom;

	for (int i = 0; i < _engine.cant_mesh; i++)
		_engine.m_mesh[i]->Render();

}

void Example2::close()
{

}

