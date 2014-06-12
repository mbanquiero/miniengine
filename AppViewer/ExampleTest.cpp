#include "stdafx.h"
#include "ExampleTest.h"
#include "InputManager.h"

REGISTER_EXAMPLE(CExampleTest)

const char * _escenas [] = {
	"\\media\\QuakeRoom1\\QuakeMap-TgcScene.flat",
	"\\media\\QuakeRoom2\\q2.flat",
	"\\media\\QuakeRoom3\\city.flat"
};

const int cant_escenas = sizeof(_escenas) / sizeof(char*);
int _escena_sel = 0;

CExampleTest::CExampleTest()
{
}


CExampleTest::~CExampleTest()
{
}

const char * CExampleTest::getName()
{
	return "Escenario de quake";
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

void CExampleTest::loadEscene(const char * path)
{
	//cargo el mesh del escenario del quake
	char mesh_path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, mesh_path);
	strcat(mesh_path, path);

	//por algun motivo no anda usando un path relativo y usando \ en vez de /
	//reemplazo todas las \\ por /
	for (char * p = mesh_path; *p; p++) if (*p == '\\') *p = '/';

	_engine.LoadSceneFromFlat(mesh_path);
}

void CExampleTest::init()
{
	InputManager::Init();

	
	loadEscene(_escenas[_escena_sel]);

	m_camera.m_lookFrom.Set(500, 100, 400);
	m_camera.m_lookAt.Set(500, 100, 500);

	//CompactMeshes(); //el archivo ya esta compactado

}

void CExampleTest::render(float elapsedTime)
{
	InputManager::Update();

	m_camera.UpdateCamera();


	if (InputManager::IsPressed(DInputKey::Key_PageDown))
	{
		_escena_sel = (_escena_sel+1) % cant_escenas;
		loadEscene(_escenas[_escena_sel]);
	}

	if (InputManager::IsPressed(DInputKey::Key_PageUp))
	{
		_escena_sel = (_escena_sel - 1 + cant_escenas) % cant_escenas;
		loadEscene(_escenas[_escena_sel]);
	}


	
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
