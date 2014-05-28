#include "stdafx.h"
#include "ExampleTest.h"
#include "InputManager.h"

REGISTER_EXAMPLE(CExampleTest)

CExampleTest::CExampleTest()
{
}


CExampleTest::~CExampleTest()
{
}

const char * CExampleTest::getName()
{
	return " Escenario de Prueba";
}

const char * CExampleTest::getDescription()
{
	return "Descripcion de ejemplo de prueba";
}

void CompactMeshes()
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

void CExampleTest::init()
{
	InputManager::Init();

	//cargo el mesh del escenario del quake
	char mesh_path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, mesh_path);
	strcat(mesh_path, "\\media\\QuakeRoom1\\QuakeMap-TgcScene.flat");

	//por algun motivo no anda usando un path relativo y usando \ en vez de /
	//reemplazo todas las \\ por /
	for (char * p = mesh_path; *p; p++) if (*p == '\\') *p = '/';

	_engine.LoadSceneFromFlat(mesh_path);

	m_camera.m_lookFrom.Set(500, 100, 400);
	m_camera.m_lookAt.Set(500, 100, 500);

	CompactMeshes();

}

void CExampleTest::render(float elapsedTime)
{
	InputManager::Update();

	m_camera.UpdateCamera();
	
	_engine.lookAt = m_camera.m_lookAt;
	_engine.lookFrom = m_camera.m_lookFrom;


	for (int i = 0; i < _engine.cant_mesh; i++)
	{
		_engine.m_mesh[i]->Render();
	}

}

void CExampleTest::close()
{

}
