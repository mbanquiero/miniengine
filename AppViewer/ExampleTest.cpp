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
